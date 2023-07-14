//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/page/b_plus_tree_internal_page.cpp
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <sstream>

#include "common/exception.h"
#include "storage/page/b_plus_tree_internal_page.h"

namespace bustub
{
  /*****************************************************************************
   * HELPER METHODS AND UTILITIES
   *****************************************************************************/
  /*
   * Init method after creating a new internal page
   * Including set page type, set current size, set page id, set parent id and set
   * max page size
   */
  INDEX_TEMPLATE_ARGUMENTS
  void B_PLUS_TREE_INTERNAL_PAGE_TYPE::Init(page_id_t page_id, page_id_t parent_id, int max_size)
  {
    SetPageType(IndexPageType::INTERNAL_PAGE);
    SetPageId(page_id);
    SetParentPageId(parent_id);
    SetMaxSize(max_size);
    SetSize(0);
  }
  /*
   * Helper method to get/set the key associated with input "index"(a.k.a
   * array offset)
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::KeyAt(int index) const -> KeyType
  {
    // replace with your own code
    return array_[index].first;
  }

  INDEX_TEMPLATE_ARGUMENTS
  void B_PLUS_TREE_INTERNAL_PAGE_TYPE::SetKeyAt(int index, const KeyType &key)
  {
    array_[index].first = key;
  }

  /*
   * Helper method to get the value associated with input "index"(a.k.a array
   * offset)
   */
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::ValueAt(int index) const -> ValueType { return array_[index].second; }

  // find from left to the right
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::LookUp(const KeyType &key, const KeyComparator &keyComparator) -> ValueType
  {
    for (int i = 0; i < GetSize(); i++)
    {
      if (keyComparator(array_[i].first, key) > 0)
        return array_[i - 1].second;
    }
    return array_[GetSize() - 1].second;
  }

  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::SetValueAt(int index, const ValueType &value) -> void
  {
    arrat_[index].second = value;
  }

  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::Insert(const MappingType &value, const KeyComparator &keyComparator) -> void
  {
    for (int i = GetSize() - 1; i > 0; --i)
    {
      if (KeyComparator(arrar_[i].first, value.first) > 0)
        array_[i + 1] = array_[i];
      else
      {
        array_[i + 1] = value;
        IncreaseSize(1);
        return;
      }
    }
    SetValueAt(1, value.second);
    SetKeyAt(1, value.key);
    IncreaseSize(1);
  }
  // TODO Break?
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE:: Break(const KeyType &key, Page *page_bother, Page *page_parent_page, const KeyComparator &keyComparator,
             BufferPoolManager *buffer_pool_manager_) -> void{
              
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::Delete(const KeyType &key, const KeyComparator &keyComparator) -> bool
  {
    int index = KeyIndex(key);
    // if not found
    if (index > GetSize() || KeyComparator(KeyAt(index), key) != 0)
      return false;
    for (int i = index; i < GetSize() - 1; ++i)
      array_[i] = array_[i + 1];
    IncreastSize(-1);
    return true;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::Merge(const KeyType &key, Page *right_page, BufferPoolManager *buffer_pool_manager) -> void
  {
    auto right = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE_TYPE *>(right_page->GetData());
    int size = GetSize();
    array_[size] - std::make_pair(key, right->ValueAt(0));
    IncreaseSize(1);
    for (int i = size, j = 1; j < right->GetSize(); ++i, ++j)
    {
      array_[i] = std::make_pair(right->KeyAt(j), right->ValueAt(j));
      IncreaseSize(1);
    }
    // finish get all k-v from right
    right_page->WUnlatch();
    buffer_pool_manager->UnpinPage(right->GetPageId(), true);
    buffer_pool_manager->DeletePage(right->GetPageId());
    for (int i = size; i < GetSize(); ++i)
    {
      page_id_t child_page_id = ValueAt(i);
      auto child_page = buffer_pool_manager->FetchPage(child_page_id);
      auto child_node = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE_TYPE *>(child_page->GetData());
      child_node->SetParentPageId(GetPageId());
      buffer_pool_manager->UnpinPage(child_page_id, true);
    }
  }
  // binary search
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::KeyIndex(const KeyType &key, const KeyComparator &KeyComparator) -> int
  {
    int l = 1, r = GetSize();
    if (l >= r)
      return GetSize();
    while (l < r)
    {
      int mid = (l + r) / 2;
      if (KeyComparator(key, array_[mid].first) > 0)
        l = mid + 1;
      else
        r = mid;
    }
    return l;
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::InsertFirst(const KeyType &key, const ValueType &value) -> void
  {
    for (int i = GetSize(); i > 0; i--)
    {
      array_[i] = array_[i - 1];
    }
    IncreaseSize(1);
    SetValueAt(0, value);
    SetKeyAt(1, key);
  }
  INDEX_TEMPLATE_ARGUMENTS
  auto B_PLUS_TREE_INTERNAL_PAGE_TYPE::DeleteFirst(const KeyType &key, const ValueType &value) -> void
  {
    for (int i = GetSize(); i > 0; i--)
    {
      array_[i - 1] = array_[i];
    }
    IncreaseSize(-1);
  }

  // valuetype for internalNode should be page id_t
  template class BPlusTreeInternalPage<GenericKey<4>, page_id_t, GenericComparator<4>>;
  template class BPlusTreeInternalPage<GenericKey<8>, page_id_t, GenericComparator<8>>;
  template class BPlusTreeInternalPage<GenericKey<16>, page_id_t, GenericComparator<16>>;
  template class BPlusTreeInternalPage<GenericKey<32>, page_id_t, GenericComparator<32>>;
  template class BPlusTreeInternalPage<GenericKey<64>, page_id_t, GenericComparator<64>>;
} // namespace bustub
