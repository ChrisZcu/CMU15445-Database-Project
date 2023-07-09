/**
 * index_iterator.cpp
 */
#include <cassert>

#include "storage/index/index_iterator.h"

namespace bustub
{

    /*
     * NOTE: you can change the destructor/constructor method here
     * set your own input parameters
     */
    INDEX_TEMPLATE_ARGUMENTS
    INDEXITERATOR_TYPE::IndexIterator() : page_id_(INVALID_PAGE_ID){};

    INDEX_TEMPLATE_ARGUMENTS
    INDEXITERATOR_TYPE::~IndexIterator() = default; // NOLINT

    INDEX_TEMPLATE_ARGUMENTS
    auto INDEXITERATOR_TYPE::IsEnd() -> bool
    {
        auto cur_node = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(curr_page_->GetData());
        return static_cast<bool>(cur_node->GetSize() == index_ && cur_node->GetNextPageId() == INVALID_PAGE_ID);
    }

    INDEX_TEMPLATE_ARGUMENTS
    auto INDEXITERATOR_TYPE::operator*() -> const MappingType &
    {
        auto cur_node = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(curr_page_->GetData());
        return cur_node->GetPair(index_);
    }

    INDEX_TEMPLATE_ARGUMENTS
    auto INDEXITERATOR_TYPE::operator++() -> INDEXITERATOR_TYPE &
    {
        index++;
        auto cur_node = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(curr_page_->GetData());
        if (index_ == cur_node->GetSize() && cur_node->GetNExtPageId() != INVALID_PAGE_ID)
        {
            auto next_page = buffer_pool_manager_->FetchPage(cur_node->GetNextPageId());
            next_page->RUnlatch();
            buffer_pool_manager_->UnpinPage(cur_node->GetPageId(), false);
            curr_page_ = next_page;
            page_id_ = curr_page_->GetPageId();
            index_ = 0;
        }
        if (index_ == cur_node->GetSize() && cur_node->GetNExtPageId() == INVALID_PAGE_ID)
        {
            curr_page_->RUnlatch();
            buffer_pool_manager_->UnpinPage(curr_page_->GetPageId());
        }

        return *this;
    }
    INDEX_TEMPLATE_ARGUMENTS
    IndexIterator<KeyType, ValueType, KeyComparator>::IndexIterator(Page *curr_page, int index, page_id_t page_id, BufferPoolManager *bufferPoolManager)
        : page_id_(page_id), curr_page_(curr_page), index_(index), buffer_pool_manager_(bufferPoolManager) {}

    template class IndexIterator<GenericKey<4>, RID, GenericComparator<4>>;

    template class IndexIterator<GenericKey<8>, RID, GenericComparator<8>>;

    template class IndexIterator<GenericKey<16>, RID, GenericComparator<16>>;

    template class IndexIterator<GenericKey<32>, RID, GenericComparator<32>>;

    template class IndexIterator<GenericKey<64>, RID, GenericComparator<64>>;

} // namespace bustub
