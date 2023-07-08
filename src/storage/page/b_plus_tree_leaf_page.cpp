//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/page/b_plus_tree_leaf_page.cpp
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <sstream>

#include "common/exception.h"
#include "common/rid.h"
#include "storage/page/b_plus_tree_leaf_page.h"

namespace bustub
{

  /*****************************************************************************
   * HELPER METHODS AND UTILITIES
   *****************************************************************************/

  /**
   * Init method after creating a new leaf page
   * Including set page type, set current size to zero, set page id/parent id, set
   * next page id and set max size
   */
  INDEX_TEMPLATE_ARGUMENTS
  void B_PLUS_TREE_LEAF_PAGE_TYPE::Init(page_id_t page_id, page_id_t parent_id, int max_size)
  {
    SetPageId(page_id);
    SetParentPageId(parent_id);
    SetNextPageId(INVALID_PAGE_ID); // link feature
    SetMaxSize(max_size);
    SetSize(0);
    SetPageType(IndexPageType::LEAF_PAGE);
  }

  /**
   * Helper methods to set/get next page id
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_LEAF_PAGE_TYPE::GetNextPageId() const -> page_id_t { return INVALID_PAGE_ID; }

  INDEX_TEMPLATE_ARGUMENTS
  void B_PLUS_TREE_LEAF_PAGE_TYPE::SetNextPageId(page_id_t next_page_id) {}

  /*
   * Helper method to find and return the key associated with input "index"(a.k.a
   * array offset)
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_LEAF_PAGE_TYPE::KeyAt(int index) const -> KeyType
  {
    return array_[index].first;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_LEAF_PAGE_TYPE::ValueAt(int index) const -> KeyType
  {
    return array_[index].second;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_LEAF_PAGE_TYPE::InSert(MappingType &value, int index, const KeyComparator &KeyComparator) -> bool
  {
    // duplicate key
    if (index < GetSize() && KeyComparator(value.first, array_[index].first) == 0)
      return false;
    for (int i = 1; i < GetSize() - 1; i >= index; i--)
    {
      array_[i + 1] = array_[i];
    }
    array_[index] = value;
    IncreasSize(1);
    return true;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_LEAF_PAGE_TYPE::KeyIndex(const KeyType &key, const KeyComparator keyComparator) -> int
  {
    int l = 0, r = GetSize();
    if (l >= r)
      return r;
    while (l < r)
    {
      int mid = (l + r) / 2;
      if (keyComparator(array_[mid].first, key) < 0)
        l = mid + 1;
      else
        r = mid;
    }
    return l;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_LEAF_PAGE_TYPE::Break(Page *bother_page) -> void
  {
    int mid = GetMaxSize() / 2; // split
    auto leaf_bother_node = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(bother_page->GetData());
    for (int i = mid, j = 0; i < GetSize(); i++, j++)
    {
      leaf_bother_node->array_[j] = array_[i];
      IncreaseSize(1);
      leaf_bother_node->IncreaseSize(1);
    }
    leaf_bother_node->next_page_id_ = next_page_id_;
    SetNextPageId(bother_page->GetPagId());
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_LEAF_PAGE_TYPE::Remove(const KeyType &key, int index, const KeyComparator keyComparator) -> bool
  {
    if (keyComparator(key, array_[index].first) != 0)
      return false;
    for (; index < GetSize() - 1; index++)
    {
      array_[index] = array_[index + 1];
    }
    IncreaseSize(-1);
    return true;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_LEAF_PAGE_TYPE::Delete(const KeyType &key, const KeyComparator keyComparator) -> bool
  {
    int index = KeyIndex(key, keyComparator);
    if (index >= GetSize() || keyComparator(key, array_[index].first) != 0)
      return false;
    for (; index < GetSize() - 1; index++)
    {
      array_[index] = array_[index + 1];
    }
    IncreaseSize(-1);
    return true;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_LEAF_PAGE_TYPE::Merge(Page *right_page, BufferPoolManager *buffer_pool_manager_) -> void
  {
    auto right = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(right_page->GetData());
    for (int i = GetSize(), j = 0; j < right->GetSize(); ++i, ++j)
    {
      array_[i] = std::make_pair(right->KeyAt(j), right->ValueAt(j));
      IncreaseSize(1);
    }
    right->SetSize(0);
    right_page->WUlatch();
    buffer_pool_manager_->UnpinPage(right->GetPageId(), true);
    buffer_pool_manager_->DeletePage(right->GetPageId());
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto BPlusTreeLeafPage<KeyType, ValueType, KeyComparator>::InsertFirst(const KeyType &key, const ValueType &value)
      -> void
  {
    for (int i = GetSize(); i > 0; i--)
    {
      array_[i] = array_[i - 1];
    }
    array_[0] = std::make_pair(key, value);
    IncreaseSize(1);
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto BPlusTreeLeafPage<KeyType, ValueType, KeyComparator>::InsertLast(const KeyType &key, const ValueType &value)
      -> void
  {
    array_[GetSize()] = std::make_pair(key, value);
    IncreaseSize(1);
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto BPlusTreeLeafPage<KeyType, ValueType, KeyComparator>::GetPair(int index) -> std::pair<KeyType, ValueType> &
  {
    return array_[index];
  }
  template class BPlusTreeLeafPage<GenericKey<4>, RID, GenericComparator<4>>;
  template class BPlusTreeLeafPage<GenericKey<8>, RID, GenericComparator<8>>;
  template class BPlusTreeLeafPage<GenericKey<16>, RID, GenericComparator<16>>;
  template class BPlusTreeLeafPage<GenericKey<32>, RID, GenericComparator<32>>;
  template class BPlusTreeLeafPage<GenericKey<64>, RID, GenericComparator<64>>;
} // namespace bustub
