#include <string>

#include "common/exception.h"
#include "common/logger.h"
#include "common/rid.h"
#include "storage/index/b_plus_tree.h"
#include "storage/page/header_page.h"

namespace bustub
{
  INDEX_TEMPLATE_ARGUMENTS
  BPLUSTREE_TYPE::BPlusTree(std::string name, BufferPoolManager *buffer_pool_manager, const KeyComparator &comparator,
                            int leaf_max_size, int internal_max_size)
      : index_name_(std::move(name)),
        root_page_id_(INVALID_PAGE_ID),
        buffer_pool_manager_(buffer_pool_manager),
        comparator_(comparator),
        leaf_max_size_(leaf_max_size),
        internal_max_size_(internal_max_size) {}

  /*
   * Helper function to decide whether current b+tree is empty
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::IsEmpty() const -> bool { return root_page_id_ == INVALID_PAGE_ID; }
  /*****************************************************************************
   * SEARCH
   *****************************************************************************/
  /*
   * Return the only value that associated with input key
   * This method is used for point query
   * @return : true means key exists
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::GetValue(const KeyType &key, std::vector<ValueType> *result, Transaction *transaction) -> bool
  {
    if (IsEmpty())
      return false;
    Page *page = FindLeafPage(key, transaction, READ);
    if (page == nullptr)
      return false;
    auto leaf_node = reinterpret_cast<LeafPage *>(page->GetData());
    int index = leaf_node->KeyIndex(key, comparator_); // 可能的数组位置，因为可能出现范围查询结果导致不是精确的key
    if (index < leaf_node->GetSize() && comparator_(leaf_node->KeyAt(index), key) == 0)
    {
      result->push_back(leaf_node->ValueAt(index));

      if (transaction != nullptr)
        UnLockAndUnpin(transaction, READ);
      else
      {
        page->RUnlatch();
        buffer_pool_manager_->UnpinPage(leaf_node->GetPageId(), false);
      }
      return true;
    }
    if (transaction != nullptr)
      UnLockAndUnpin(transaction, READ);
    else
    {
      page->RUnlatch();
      buffer_pool_manager_->UnpinPage(leaf_node->GetPageId(), false);
    }
    return false;
  }

  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::FindLeafPage(const KeyType &key, Transaction *transaction, Operation op) -> Page *
  {
    if (IsEmpty())
      return nullptr;
    Page *cur_page = buffer_pool_manager_->FetchPage(root_page_id_);
    while (true)
    {
      if (cur_page == nullptr)
        return nullptr;
      if (op == READ)
        cur_page->RLatch();
      else
        cur_page->WLatch();
      // transaction 包含所有操纵b+tree的线程，addintopageset方法用来跟踪所有的page 锁
      if (transaction != nullptr)
        transaction->AddIntoPageSet(cur_page);
      if (root_page_id_ == cur_page->GetPageId()) // 找到，加了锁，break
        break;
      if (op == READ)
      {
        if (transaction != nullptr)
          UnLockAndUnpin(transaction, op);
        else
        {
          cur_page->RUnlatch();
          buffer_pool_manager_->UnpinPage(cur_page->GetPageId(), false);
        }
      }
      else
      {
        UnLockAndUnpin(transaction, op);
      }
      cur_page = buffer_pool_manager_->FetchPage(root_page_id_);
    }

    auto cur_page_internal = reinterpret_cast<InternalPage *>(cur_page->GetData());
    while (!cur_page_internal->IsLeafPage())
    {
      // 此时root已经上锁了，迭代下来此时cur_page也是上锁的，这一不是为了简化所得粒度
      Page *next_page = buffer_pool_manager_->FetchPage(cur_page_internal->LookUp(key, comparator_));
      // lookup 返回page id
      if (op == READ)
      {
        // 读操作不会修改数组，因此可以尝试把所有的latch都unlock，如果碰到之前的写latch，则没有权限无法进行unlatch，因此是安全的
        next_page->RLatch();
        if (transaction != nullptr)
          UnLockAndUnpin(transaction, op);
        else
        {
          cur_page->RUnLatch();
          buffer_pool_manager_->UnpinPage(cur_page->GetPageId(), false);
        }
      }
      else
      {
        // 写操作需要判断下一个节点是否安全（修改是否影响当前节点），安全之后才可以进行解锁
        next_page->WLatch();
        if (IsSafe(next_page, op))
          UnLockAndUnpin(transaction, op);
      }
      if (transaction != nullptr)
        transaction->AddIntoPageSet(next_page);
      cur_page = next_page;
      cur_page_internal = reinterpret_cast<InternalPage *>(next_page->GetData());
    }
    return curr_page;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::IsSafe(Page *page, Operation op) -> bool
  {
    auto node = reinterpret_cast<BPlusTreePage *>(page);
    if (op == INSERT)
      return node->GetSize() < node->GetMaxSize();
    // 删除时
    // 父节点是root
    if (node->GetParentPageId() == INVALID_PAGE_ID)
    {
      if (node->IsLeafPage())
        return true;
      // 中间节点最左边的index无意义
      return node->GetSize() > 2;
    }
    return node->GetSize() > node->GetMinSize();
  }
  // 集中处理事物中的所有page和buffer poll中的所有page
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::UnLockAndUnpin(Transaction *transaction, Operation op) -> void
  {
    if (transaction == nullptr)
      return;
    for (auto page : *transaction->GetPageSet)
    {
      if (op == READ)
      {
        page->RUnlatch();
        buffer_pool_manager_->UnpinPage(page->GetPageId(), false);
      }
      else
      {
        page->WUnlatch();
        buffer_pool_manager_->UnpinPage(page->GetPageId(), false);
      }
    }
    transaction->GetPageSet()->clear();
    for (auto page : *transaction->GetDeletedPageSet())
      buffer_pool_manager_->DeletePage(page);
    transaction->GetDeletedPageSet()->clear();
  }

  /*****************************************************************************
   * INSERTION
   *****************************************************************************/
  /*
   * Insert constant key & value pair into b+ tree
   * if current tree is empty, start new tree, update root page id and insert
   * entry, otherwise insert into leaf page.
   * @return: since we only support unique key, if user try to insert duplicate
   * keys return false, otherwise return true.
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::Insert(const KeyType &key, const ValueType &value, Transaction *transaction) -> bool
  {
    Page *page_leaf = FindLeafPage(key, transaction, INSERT);
    if (page_leaf == nullptr)
    {
      latch_.lock();
      if (IsEmpty())
      {
        page_id_t *page_id;
        Page *page = buffer_pool_manager_->NewPage(&page_id);
        auto leaf_node = reinterpret_cast<LeafPage *>(page->GetData());
        leaf_node->Init(page_id, INVALID_PAGE_ID, leaf_max_size_);
        root_page_id_ = page_id;
        buffer_pool_manager_->UnpinPage(page_id, false);
      }
      latch_.unlock();
      page_leaf = FindLeafPage(key, transaction, INSERT)
    }
    auto leaf_node = reinterpret_cast<LeafPage *>(page_leaf);
    int index = leaf_node->KeyIndex(key, comparator_);
    bool retcode = leaf_node->Insert(std::make_pair(key, value), index, comparator_);
    if (!retcode)
    {
      UnLockAndUnpin(transaction, INSERT);
      returna false;
    }
    // 判断是否安全
    if (leaf_node->GetSize() == leaf_max_size_)
    {
      // split node
      page_id_t page_bother_id;
      Page *page_bother = buffer_pool_manager_->NewPage(page_bother_id);
      auto leaf_bother_node = reinterpret_cast<LeafPage *>(page_bother->GetData());
      leaf_bother_node->Init(page_bother_id, INVALID_PAGE_ID, leaf_max_size_);
      // 一半的数据放入page bother中, leaf_bother_node还是孤儿
      leaf_node->Break(page_bother);
      // 插入父亲
      InsertInParent(page_leaf, leaf_bother_node->KeyAt(0), page_bother, transaction)
          buffer_pool_manager_->UnpinPage(page_bother->GetPageId(), true);
      UnLockAndUnpin(transaction, INSERT);
    }
    UnLockAndUnpin(transaction, INSERT);
    return false;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::InsertInParent(Page *page_leaf, const KeyType &key, Page *page_bother, Transaction *transaction) -> void
  {
    auto tree_page = reinterpret_cast<BPlusTreePage *>(page_leaf->GetData());
    // 根节点，需要增加树高
    if (tree_page->GetParentPageId() == INVALID_PAGE_ID)
    {
      page_id_t new_page_id;
      Page *new_page = buffer_pool_manager_->NewPage(&new_page_id);
      auto new_root = reinterpret_cast<InternalPage *>(new_page->GetData());
      new_root->Init(new_page_id, INVALID_PAGE_ID, internal_max_size_);
      new_root->SetValueAt(0, page_leaf->GetPageId());
      new_root->SetKeyAt(1, key);
      new_root->SetValueAt(1, page_bother->GetPageId());
      new_root->IncreaseSize(2);
      auto page_leaf_node = reinterpret_cast<BPlusTreePage *>(page_leaf->GetData());
      auto page_bother_node = reinterpret_cast<BPlusTreePage *>(page_bother->GetData());
      page_leaf_node->SetParentPageId(new_page_id);
      page_bother_node->SetParentPageId(new_page_id);
      root_page_id_ = new_page_id;
      buffer_pool_manager_->UnpinPage(new_page_id, true);
      return;
    }
    page_id_t parent_page_id = tree_page->GetParentPageId();
    Page *parent_page = buffer_pool_manager_->FetchPage(parent_page_id);
    auto parent_node = reinterpret_cast<InternalPage *>(parent_page->GetData());
    auto page_bother_node = reinterpret_cast<InternalPage *>(page_bother->GetData());
    // 插入并且父节点数目为达到上限
    if (parent_node->GetSize() < parent_node->GetMaxSize())
    {
      parent_node->Insert(std::make_pair(key, page_bother->GetPageId()), comparator_);
      page_bother_node->SetParentPageId(parent_page_id);
      buffer_pool_manager_->UnpinPage(parent_page_id, true);
      return;
    }
    // 插入父节点数目达到上限，需要分裂父节点，递归进行
    page_id_t parent_bother_page_id;
    Page *parent_bother_page = buffer_pool_manager_->NewPage(&parent_bother_page_id);
    auto parent_bother_node = reinterpret_cast<InternalPage *>(parent_bother_page);
    parent_bother_node->Init(parent_bother_page_id, INVALID_PAGE_ID, internal_max_size_);
    parent_node->Break(key, page_bother, parent_bother_page, comparator_, buffer_pool_manager_);
    InsertInParent(parent_page, parent_bother_node->KeyAt(0), parent_bother_pagem transaction);
    buffer_pool_manager_->UnpinPage(parent_bother_page_id, true);
    buffer_pool_manager_->UnpinPage(parent_page_id, true);
  }
  /*****************************************************************************
   * REMOVE
   *****************************************************************************/
  /*
   * Delete key & value pair associated with input key
   * If current tree is empty, return immdiately.
   * If not, User needs to first find the right leaf page as deletion target, then
   * delete entry from leaf page. Remember to deal with redistribute or merge if
   * necessary.
   */
  INDEX_TEMPLATE_ARGUMENTS
  void BPLUSTREE_TYPE::Remove(const KeyType &key, Transaction *transaction) {}

  /*****************************************************************************
   * INDEX ITERATOR
   *****************************************************************************/
  /*
   * Input parameter is void, find the leaftmost leaf page first, then construct
   * index iterator
   * @return : index iterator
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::Begin() -> INDEXITERATOR_TYPE { return INDEXITERATOR_TYPE(); }

  /*
   * Input parameter is low key, find the leaf page that contains the input key
   * first, then construct index iterator
   * @return : index iterator
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::Begin(const KeyType &key) -> INDEXITERATOR_TYPE { return INDEXITERATOR_TYPE(); }

  /*
   * Input parameter is void, construct an index iterator representing the end
   * of the key/value pair in the leaf node
   * @return : index iterator
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::End() -> INDEXITERATOR_TYPE { return INDEXITERATOR_TYPE(); }

  /**
   * @return Page id of the root of this tree
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto BPLUSTREE_TYPE::GetRootPageId() -> page_id_t { return 0; }

  /*****************************************************************************
   * UTILITIES AND DEBUG
   *****************************************************************************/
  /*
   * Update/Insert root page id in header page(where page_id = 0, header_page is
   * defined under include/page/header_page.h)
   * Call this method everytime root page id is changed.
   * @parameter: insert_record      defualt value is false. When set to true,
   * insert a record <index_name, root_page_id> into header page instead of
   * updating it.
   */
  INDEX_TEMPLATE_ARGUMENTS
  void BPLUSTREE_TYPE::UpdateRootPageId(int insert_record)
  {
    auto *header_page = static_cast<HeaderPage *>(buffer_pool_manager_->FetchPage(HEADER_PAGE_ID));
    if (insert_record != 0)
    {
      // create a new record<index_name + root_page_id> in header_page
      header_page->InsertRecord(index_name_, root_page_id_);
    }
    else
    {
      // update root_page_id in header_page
      header_page->UpdateRecord(index_name_, root_page_id_);
    }
    buffer_pool_manager_->UnpinPage(HEADER_PAGE_ID, true);
  }

  /*
   * This method is used for test only
   * Read data from file and insert one by one
   */
  INDEX_TEMPLATE_ARGUMENTS
  void BPLUSTREE_TYPE::InsertFromFile(const std::string &file_name, Transaction *transaction)
  {
    int64_t key;
    std::ifstream input(file_name);
    while (input)
    {
      input >> key;

      KeyType index_key;
      index_key.SetFromInteger(key);
      RID rid(key);
      Insert(index_key, rid, transaction);
    }
  }
  /*
   * This method is used for test only
   * Read data from file and remove one by one
   */
  INDEX_TEMPLATE_ARGUMENTS
  void BPLUSTREE_TYPE::RemoveFromFile(const std::string &file_name, Transaction *transaction)
  {
    int64_t key;
    std::ifstream input(file_name);
    while (input)
    {
      input >> key;
      KeyType index_key;
      index_key.SetFromInteger(key);
      Remove(index_key, transaction);
    }
  }

  /**
   * This method is used for debug only, You don't need to modify
   */
  INDEX_TEMPLATE_ARGUMENTS
  void BPLUSTREE_TYPE::Draw(BufferPoolManager *bpm, const std::string &outf)
  {
    if (IsEmpty())
    {
      LOG_WARN("Draw an empty tree");
      return;
    }
    std::ofstream out(outf);
    out << "digraph G {" << std::endl;
    ToGraph(reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(root_page_id_)->GetData()), bpm, out);
    out << "}" << std::endl;
    out.flush();
    out.close();
  }

  /**
   * This method is used for debug only, You don't need to modify
   */
  INDEX_TEMPLATE_ARGUMENTS
  void BPLUSTREE_TYPE::Print(BufferPoolManager *bpm)
  {
    if (IsEmpty())
    {
      LOG_WARN("Print an empty tree");
      return;
    }
    ToString(reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(root_page_id_)->GetData()), bpm);
  }

  /**
   * This method is used for debug only, You don't need to modify
   * @tparam KeyType
   * @tparam ValueType
   * @tparam KeyComparator
   * @param page
   * @param bpm
   * @param out
   */
  INDEX_TEMPLATE_ARGUMENTS
  void BPLUSTREE_TYPE::ToGraph(BPlusTreePage *page, BufferPoolManager *bpm, std::ofstream &out) const
  {
    std::string leaf_prefix("LEAF_");
    std::string internal_prefix("INT_");
    if (page->IsLeafPage())
    {
      auto *leaf = reinterpret_cast<LeafPage *>(page);
      // Print node name
      out << leaf_prefix << leaf->GetPageId();
      // Print node properties
      out << "[shape=plain color=green ";
      // Print data of the node
      out << "label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
      // Print data
      out << "<TR><TD COLSPAN=\"" << leaf->GetSize() << "\">P=" << leaf->GetPageId() << "</TD></TR>\n";
      out << "<TR><TD COLSPAN=\"" << leaf->GetSize() << "\">"
          << "max_size=" << leaf->GetMaxSize() << ",min_size=" << leaf->GetMinSize() << ",size=" << leaf->GetSize()
          << "</TD></TR>\n";
      out << "<TR>";
      for (int i = 0; i < leaf->GetSize(); i++)
      {
        out << "<TD>" << leaf->KeyAt(i) << "</TD>\n";
      }
      out << "</TR>";
      // Print table end
      out << "</TABLE>>];\n";
      // Print Leaf node link if there is a next page
      if (leaf->GetNextPageId() != INVALID_PAGE_ID)
      {
        out << leaf_prefix << leaf->GetPageId() << " -> " << leaf_prefix << leaf->GetNextPageId() << ";\n";
        out << "{rank=same " << leaf_prefix << leaf->GetPageId() << " " << leaf_prefix << leaf->GetNextPageId() << "};\n";
      }

      // Print parent links if there is a parent
      if (leaf->GetParentPageId() != INVALID_PAGE_ID)
      {
        out << internal_prefix << leaf->GetParentPageId() << ":p" << leaf->GetPageId() << " -> " << leaf_prefix
            << leaf->GetPageId() << ";\n";
      }
    }
    else
    {
      auto *inner = reinterpret_cast<InternalPage *>(page);
      // Print node name
      out << internal_prefix << inner->GetPageId();
      // Print node properties
      out << "[shape=plain color=pink "; // why not?
      // Print data of the node
      out << "label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
      // Print data
      out << "<TR><TD COLSPAN=\"" << inner->GetSize() << "\">P=" << inner->GetPageId() << "</TD></TR>\n";
      out << "<TR><TD COLSPAN=\"" << inner->GetSize() << "\">"
          << "max_size=" << inner->GetMaxSize() << ",min_size=" << inner->GetMinSize() << ",size=" << inner->GetSize()
          << "</TD></TR>\n";
      out << "<TR>";
      for (int i = 0; i < inner->GetSize(); i++)
      {
        out << "<TD PORT=\"p" << inner->ValueAt(i) << "\">";
        if (i > 0)
        {
          out << inner->KeyAt(i);
        }
        else
        {
          out << " ";
        }
        out << "</TD>\n";
      }
      out << "</TR>";
      // Print table end
      out << "</TABLE>>];\n";
      // Print Parent link
      if (inner->GetParentPageId() != INVALID_PAGE_ID)
      {
        out << internal_prefix << inner->GetParentPageId() << ":p" << inner->GetPageId() << " -> " << internal_prefix
            << inner->GetPageId() << ";\n";
      }
      // Print leaves
      for (int i = 0; i < inner->GetSize(); i++)
      {
        auto child_page = reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(inner->ValueAt(i))->GetData());
        ToGraph(child_page, bpm, out);
        if (i > 0)
        {
          auto sibling_page = reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(inner->ValueAt(i - 1))->GetData());
          if (!sibling_page->IsLeafPage() && !child_page->IsLeafPage())
          {
            out << "{rank=same " << internal_prefix << sibling_page->GetPageId() << " " << internal_prefix
                << child_page->GetPageId() << "};\n";
          }
          bpm->UnpinPage(sibling_page->GetPageId(), false);
        }
      }
    }
    bpm->UnpinPage(page->GetPageId(), false);
  }

  /**
   * This function is for debug only, you don't need to modify
   * @tparam KeyType
   * @tparam ValueType
   * @tparam KeyComparator
   * @param page
   * @param bpm
   */
  INDEX_TEMPLATE_ARGUMENTS
  void BPLUSTREE_TYPE::ToString(BPlusTreePage *page, BufferPoolManager *bpm) const
  {
    if (page->IsLeafPage())
    {
      auto *leaf = reinterpret_cast<LeafPage *>(page);
      std::cout << "Leaf Page: " << leaf->GetPageId() << " parent: " << leaf->GetParentPageId()
                << " next: " << leaf->GetNextPageId() << std::endl;
      for (int i = 0; i < leaf->GetSize(); i++)
      {
        std::cout << leaf->KeyAt(i) << ",";
      }
      std::cout << std::endl;
      std::cout << std::endl;
    }
    else
    {
      auto *internal = reinterpret_cast<InternalPage *>(page);
      std::cout << "Internal Page: " << internal->GetPageId() << " parent: " << internal->GetParentPageId() << std::endl;
      for (int i = 0; i < internal->GetSize(); i++)
      {
        std::cout << internal->KeyAt(i) << ": " << internal->ValueAt(i) << ",";
      }
      std::cout << std::endl;
      std::cout << std::endl;
      for (int i = 0; i < internal->GetSize(); i++)
      {
        ToString(reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(internal->ValueAt(i))->GetData()), bpm);
      }
    }
    bpm->UnpinPage(page->GetPageId(), false);
  }

  template class BPlusTree<GenericKey<4>, RID, GenericComparator<4>>;
  template class BPlusTree<GenericKey<8>, RID, GenericComparator<8>>;
  template class BPlusTree<GenericKey<16>, RID, GenericComparator<16>>;
  template class BPlusTree<GenericKey<32>, RID, GenericComparator<32>>;
  template class BPlusTree<GenericKey<64>, RID, GenericComparator<64>>;

} // namespace bustub
