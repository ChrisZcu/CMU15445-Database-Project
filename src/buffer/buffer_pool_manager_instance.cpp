//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// buffer_pool_manager_instance.cpp
//
// Identification: src/buffer/buffer_pool_manager.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/buffer_pool_manager_instance.h"

#include "common/exception.h"
#include "common/macros.h"

namespace bustub
{

  BufferPoolManagerInstance::BufferPoolManagerInstance(size_t pool_size, DiskManager *disk_manager, size_t replacer_k,
                                                       LogManager *log_manager)
      : pool_size_(pool_size), disk_manager_(disk_manager), log_manager_(log_manager)
  {
    // we allocate a consecutive memory space for the buffer pool
    pages_ = new Page[pool_size_];
    page_table_ = new ExtendibleHashTable<page_id_t, frame_id_t>(bucket_size_);
    replacer_ = new LRUKReplacer(pool_size, replacer_k);

    // Initially, every page is in the free list.
    for (size_t i = 0; i < pool_size_; ++i)
    {
      free_list_.emplace_back(static_cast<int>(i));
    }
  }

  BufferPoolManagerInstance::~BufferPoolManagerInstance()
  {
    delete[] pages_;
    delete page_table_;
    delete replacer_;
  }
  // update both the hash table (map page to frame) and replacer(update frame state)
  auto BufferPoolManagerInstance::NewPgImp(page_id_t *page_id) -> Page *
  {
    frame_id_t frame_id;
    std::scoped_lock<std::mutex> lock(latch_);
    // free place for page allocation
    if (!free_list_.empty())
    {
      *page_id = AllocatePage();
      frame_id = free_list_.front();
      free_list_.pop_front();

      pages_[frame_id].page_id_ = *page_id;
      pages_[frame_id].is_dirty_ = false;
      pages_[frame_id].pin_count_ = 1;
      pages_[frame_id].ResetMemory();

      page_table_->Insert(*page_id, frame_id);
      replacer_->RecordAccess(frame_id);
      replacer_->SetEvictable(frame_id, false);

      return &pages_[frame_id];
    }
    // full, then evict a existing page, replace an existing page id in hash table
    if (replacer_->Evict(&frame_id))
    {
      // the frame_id has been updated after evict, reuse the memory space
      if (pages_[frame_id].is_dirty_)
      { // need to write to the disk first
        disk_manager_->WritePage(pages_[frame_id].page_id_, pages_[frame_id].data_);
        pages_[frame_id].is_dirty_ = false;
      }
      *page_id = AllocatePage();
      page_table_->Remove(pages_[frame_id].page_id_);
      pages_[frame_id].is_dirty_ = false;
      pages_[frame_id].page_id_ = *page_id;
      pages_[frame_id].pin_count_ = 1;
      pages_[frame_id].ResetMemory();

      page_table_->Insert(*page_id, frame_id);
      replacer_->RecordAccess(frame_id);
      replacer_->SetEvictable(frame_id, false);
      return &pages_[frame_id];
    }
    return nullptr;
  }
  // read from disk, but not new a page
  auto BufferPoolManagerInstance::FetchPgImp(page_id_t page_id) -> Page *
  {
    std::scoped_lock<std::mutex> lock(latch_);
    frame_id_t frame_id;
    if (page_id == INVALID_PAGE_ID)
    {
      return nullptr;
    }

    if (page_table_->Find(page_id, frame_id))
    {
      replacer_->RecordAccess(frame_id);
      replacer_->SetEvictable(frame_id, true);
      pages_[frame_id].pin_count_++;
      return &pages_[frame_id];
    }
    if (!free_list_.empty())
    {
      frame_id = free_list_.front();
      free_list_.pop_front();
      disk_manager_->ReadPage(page_id, pages_[frame_id].data_);
      pages_[frame_id].page_id_ = page_id;
      pages_[frame_id].is_dirty_ = false;
      pages_[frame_id].pin_count_ = 1;

      replacer_->RecordAccess(frame_id);
      replacer_->SetEvictable(frame_id, false);
      page_table_->Insert(page_id, frame_id);
      return &pages_[frame_id];
    }
    if (replacer_->Evict(&frame_id))
    {
      if (pages_[frame_id].is_dirty_)
      {
        disk_manager_->WritePage(pages_[frame_id].page_id_, pages_[frame_id].data_);
        pages_[frame_id].is_dirty_ = false;
      }
      page_table_->Remove(pages_[frame_id].page_id_);
      disk_manager_->ReadPage(page_id, pages_[frame_id].data_);
      pages_[frame_id].page_id_ = page_id;
      pages_[frame_id].is_dirty_ = false;
      pages_[frame_id].pin_count_++;

      replacer_->RecordAccess(frame_id);
      replacer_->SetEvictable(frame_id, false);

      page_table_->Insert(page_id, frame_id);
      return &pages_[frame_id];
    }

    return nullptr;
  }
  // 1. if found, unpin, then set it be evictable
  auto BufferPoolManagerInstance::UnpinPgImp(page_id_t page_id, bool is_dirty) -> bool
  {
    std::scoped_lock<std::mutex> lock(latch_);
    if (page_id == INVALID_PAGE_ID)
      return false;
    frame_id_t frame_id;
    if (page_table_->Find(page_id, frame_id))
    {
      if (pages_[frame_id].pin_count_ <= 0)
        return false;
      pages_[frame_id].pin_count_--;
      if (pages_[frame_id].pin_count_ == 0)
      {
        replacer_->SetEvictable(frame_id, true);
      }
      if (!pages_[frame_id].is_dirty_)
      {
        pages_[frame_id].is_dirty_ = is_dirty;
      }
    }

    return false;
  }

  auto BufferPoolManagerInstance::FlushPgImp(page_id_t page_id) -> bool
  {
    std::scoped_lock<std::mutex> lock(latch_);
    if (page_id == INVALID_PAGE_ID)
    {
      return false;
    }
    frame_id_t frame_id;
    if (page_table_->Find(page_id, frame_id))
    {
      disk_manager_->WritePage(page_id, pages_[frame_id].data_);
      pages_[frame_id].is_dirty_ = false;
      return true;
    }

    return false;
  }

  void BufferPoolManagerInstance::FlushAllPgsImp()
  {
    for (size_t i = 0; i < pool_size_; i++)
    {
      FlushPgImp(pages_[i].page_id_);
    }
  }

  auto BufferPoolManagerInstance::DeletePgImp(page_id_t page_id) -> bool
  {
    std::scoped_lock<std::mutex> lock(latch_);
    if (page_id == INVALID_PAGE_ID)
      return false;
    frame_id_t frame_id;
    if (page_table_->Find(page_id, frame_id))
    {
      if (pages_[frame_id].GetPinCount() != 0)
        return false;
      if (pages_[frame_id].is_dirty_)
      {
        disk_manager_->WritePage(page_id, pages_[frame_id].data_);
      }
      page_table_->Remove(page_id);
      replacer_->Remove(frame_id);
      pages_[frame_id].page_id_ = INVALID_PAGE_ID;
      pages_[frame_id].pin_count_ = 0;
      pages_[frame_id].is_dirty_ = false;
      pages_[frame_id].ResetMemory();
      free_list_.push_back(frame_id); // reuse frame
      DeallocatePage(page_id);
      return true;
    }

    return true;
  }

  auto BufferPoolManagerInstance::AllocatePage() -> page_id_t { return next_page_id_++; }

} // namespace bustub
