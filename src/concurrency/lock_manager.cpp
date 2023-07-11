//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lock_manager.cpp
//
// Identification: src/concurrency/lock_manager.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "concurrency/lock_manager.h"

#include "common/config.h"
#include "concurrency/transaction.h"
#include "concurrency/transaction_manager.h"

namespace bustub
{

  auto LockManager::LockTable(Transaction *txn, LockMode lock_mode, const table_oid_t &oid) -> bool
  {
    // 首先进行合法性验证：保证当前事务所处的阶段和申请的锁不冲突
    // 判断冲突：给定的隔离层级下分别进行判断，并且任何层级不允许在收缩阶段进行加不同粒度的锁
    switch (txn->GetIsolationLevel())
    {
    case IsolationLevel::READ_UNCOMMITTED:
      switch (lock_mode)
      {
      case LockMode::SHARED:
      case LockMode::INTENTION_SHARED:
      case LockMode::SHARED_INTENTION_EXCLUSIVE:
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_SHARED_ON_READ_UNCOMMITTED);
        /* code */
        break;
      default:
        if (txn->GetState() == TransactionState::SHRINKING)
          if (lock_mode == LockMode::EXCLUSIVE || lock_mode == LockMode::INTENTION_EXCLUSIVE)
          {
            txn->SetState(TransactionState::ABORTED);
            throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
          }
        break;
      }
      break;
    case IsolationLevel::READ_COMMITTED:
      if (txn->GetState() == TransactionState::SHRINKING)
        if (lock_mode != LockMode::INTENTION_SHARED && lock_mode != LockMode::SHARED)
        {
          txn->SetState(TransactionState::ABORTED);
          throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
        }
      break;
    case IsolationLevel::REPEATABLE_READ:
      if (txn->GetState() == TransactionState::SHRINKING)
      {
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::LOCK_ON_SHRINKING);
      }
      break;
    default:
      break;
    }
    // 对请求队列上锁，防止新的请求
    //  首先获得lock manager的互斥锁,获得对应的table的请求队列的锁
    table_lock_map_latch_.lock();
    if (table_lock_map_.find(oid) == table_lock_map_.end())
      table_lock_map_.emplace(oid, std::shared_ptr<LockRequestQueue>());
    ;
    auto lock_request_queue = table_lock_map_.find(oid)->second;
    lock_request_queue->latch_.lock();
    table_lock_map_latch_.unlock();

    // 主体加锁逻辑分为升级锁和加新的锁
    // 1. 锁升级
    for (auto request : lock_request_queue->request_queue_)
    {
      // 注意返回的是表对应的所有的request，有的可能不是此txn的
      if (request->txn_id_ != txn->GetTransactionId())
        continue;
      if (request->lock_mode_ == lock_mode)
      {
        lock_request_queue->latch_.unlock();
        return;
      }
      // 判断是否已经有txn在处理锁升级的请求
      if (lock_request_queue->upgrading_ != INVALID_TXN_ID)
      {
        lock_request_queue->latch_.unlock();
        txn->SetState(TransactionState::ABORTED);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::UPGRADE_CONFLICT);
      }
      // 锁降级抛错
      switch (request->lock_mode_)
      {
      case LockMode::INTENTION_SHARED:
        if (!(lock_mode == LockMode::SHARED || lock_mode == LockMode::EXCLUSIVE || lock_mode == LockMode::INTENTION_EXCLUSIVE || lock_mode == LockMode::SHARED_INTENTION_EXCLUSIVE))
        {
          lock_request_queue->latch_.unlock();
          txn->SetState(TransactionState);
          throw TransactionAbortException(txn->GetTransactionId(), AbortReason::INCOMPATIBLE_UPGRADE);
        }
      case LockMode::SHARED:
        if (!(lock_mode == LockMode::EXCLUSIVE || lock_mode == LockMode::SHARED_INTENTION_EXCLUSIVE))
        {
          lock_request_queue->latch_.unlock();
          txn->SetState(TransactionState);
          throw TransactionAbortException(txn->GetTransactionId(), AbortReason::INCOMPATIBLE_UPGRADE);
        }
      case LockMode::INTENTION_EXCLUSIVE:
        if (!(lock_mode == LockMode::EXCLUSIVE || lock_mode == LockMode::SHARED_INTENTION_EXCLUSIVE))
        {
          lock_request_queue->latch_.unlock();
          txn->SetState(TransactionState);
          throw TransactionAbortException(txn->GetTransactionId(), AbortReason::INCOMPATIBLE_UPGRADE);
        }
      case LockMode::SHARED_INTENTION_EXCLUSIVE:
        if (lock_mode != LockMode::EXCLUSIVE)
        {
          lock_request_queue->latch_.unlock();
          txn->SetState(TransactionState);
          throw TransactionAbortException(txn->GetTransactionId(), AbortReason::INCOMPATIBLE_UPGRADE);
        }
        break;
      default:
        lock_request_queue->latch_.unlock();
        txn->SetState(TransactionState);
        throw TransactionAbortException(txn->GetTransactionId(), AbortReason::INCOMPATIBLE_UPGRADE);
        break;
      }
      // 开始锁升级
      // 删除旧的request锁
      lock_request_queue->request_queue_.remove(request);
      InsertOrDeleteTableLockSet(txn, request, false);

      // 生成新的锁请求加入队列
      auto upgrade_lock_request = std::make_shared<LockRequest>(txn->GetTransactionId(), lock_mode, oid);
      auto iter = lock_request_queue->request_queue_.begin();
      for (; iter < lock_request_queue.end(); ++iter)
        // 处理无效的请求
        if (!(*iter)->granted_)
          break;
      lock_request_queue->request_queue_.insert(iter, upgrade_lock_request);
      lock_request_queue->upgrading_ = txn->GetTransactionId();

      std::unique_lock<std::mutex> lock(lock_request_queue->latch_, std::adopt_lock);
      // 判断事务被唤醒时候的状态，如果已加的锁和请求加的锁不兼容则需要重新进行判断
      while (!GrantLock(upgrade_lock_request, lock_request_queue))
      {
        // 条件变量释放出锁，让其他事务拿锁进行处理，再通过竞争抢锁，以此来进行下一轮状态的判断
        lock_request_queue->cv_.wait(lock);

        // 判断状态
        if (txn->GetState() == TransactionState::ABORTED)
        {
          lock_request_queue->upgrading_ = INVALID_TXN_ID;
          lock_request_queue->request_queue_.remove(upgrade_lock_request);
          lock_request_queue->cv_.notify_all();
          return false;
        }
      }
      // 升级成功
      lock_request_queue->upgrading_ = INVALID_TXN_ID;
      upgrade_lock_request->granted_ = true;
      InsertOrDeleteTableLockSet(txn, upgrade_lock_request, true);
      return true;
    }

    // 2. 增加新的锁
    // 处理请求：生成请求
    auto lock_request = std::make_shared<LockRequest>(txn->GetTransactionId(), lock_mode, oid);
    lock_request_queue->request_queue_.push_back(lock_request);

    std::unique_lock<std::mutex> lock(lock_request_queue->latch_, std::adopt_lock);
    while (!GrantLock(lock_request, lock_request_queue)) // 进行加锁
    {
      // 加锁失败，等待条件变量，重新加锁
      lock_request_queue->cv_.wait(lock);
      if (txn->GetState() == TransactionState::ABORTED)
      {
        lock_request_queue->request_queue_.remove(lock_request);
        lock_request_queue->cv_.notify_all();
        return false;
      }
    }

    // 完成锁任务
    lock_request->granted_ = true;
    InsertOrDeleteTableLockSet(txn, lock_request, true);
    if (lock_mode == LockMode::EXCLUSIVE)
    {
      lock_request_queue->cv_.notify_all();
    }
    // 成功申请锁
    return true;
  }

  auto LockManager::UnlockTable(Transaction *txn, const table_oid_t &oid) -> bool { return true; }

  auto LockManager::LockRow(Transaction *txn, LockMode lock_mode, const table_oid_t &oid, const RID &rid) -> bool
  {
    return true;
  }

  auto LockManager::UnlockRow(Transaction *txn, const table_oid_t &oid, const RID &rid) -> bool { return true; }

  void LockManager::AddEdge(txn_id_t t1, txn_id_t t2) {}

  void LockManager::RemoveEdge(txn_id_t t1, txn_id_t t2) {}

  auto LockManager::HasCycle(txn_id_t *txn_id) -> bool { return false; }

  auto LockManager::GetEdgeList() -> std::vector<std::pair<txn_id_t, txn_id_t>>
  {
    std::vector<std::pair<txn_id_t, txn_id_t>> edges(0);
    return edges;
  }

  void LockManager::RunCycleDetection()
  {
    while (enable_cycle_detection_)
    {
      std::this_thread::sleep_for(cycle_detection_interval);
      { // TODO(students): detect deadlock
      }
    }
  }
  auto LockManager::InsertOrDeleteTableLockSet(Transaction *txn, const std::shared_ptr<LockRequest> &lock_request, bool insert) -> void
  {
    switch (lock_request->lock_mode_)
    {
    case LockMode::SHARED:
      if (insert)
        txn->GetSharedTableLockSet()->insert(lock_request->oid_);
      else
        txn->GetSharedTableLockSet()->erase(lock_request->oid_);
      break;
    case LockMode::EXCLUSIVE:
      if (insert)
        txn->GetExclusiveTableLockSet()->insert(lock_request->oid_);
      else
        txn->GetExclusiveTableLockSet()->erase(lock_request->oid_);
      break;
    case LockMode::INTENTION_SHARED:
      if (insert)
        txn->GetIntentionSharedTableLockSet()->insert(lock_request->oid_);
      else
        txn->GetIntentionSharedTableLockSet()->erase(lock_request->oid_);
      break;
    case LockMode::INTENTION_EXCLUSIVE:
      if (insert)
        txn->GetIntentionExclusiveTableLockSet()->insert(lock_request->oid_);
      else
        txn->GetIntentionExclusiveTableLockSet()->erase(lock_request->oid_);
      break;
    case LockMode::SHARED_INTENTION_EXCLUSIVE:
      if (insert)
        txn->GetSharedIntentionExclusiveTableLockSet()->insert(lock_request->oid_);
      else
        txn->GetSharedIntentionExclusiveTableLockSet()->erase(lock_request->oid_);
      break;
    default:
      break;
    }
  }
  auto LockManager::InsertOrDeleteRowLockSet(Transaction *txn, const std::shared_ptr<LockRequest> &lock_request, bool insert) -> void
  {
    auto s_row_lock_set = txn->GetSharedRowLockSet();
    auto x_row_lock_Set = txn->GetExclusiveRowLockSet();
    switch (lock_request->lock_mode_)
    {
    case LockMode::SHARED:
      if (insert)
        InsertRowLockSet(s_row_lock_set, lock_request->oid_, lock_request->rid_);
      else
        DeleteRowLockSet(s_row_lock_set, lock_request->oid_, lock_request->rid_);
      break;
    case LockMode::EXCLUSIVE:
      if (insert)
        InsertRowLockSet(x_row_lock_Set, lock_request->oid_, lock_request->rid_);
      else
        DeleteRowLockSet(x_row_lock_Set, lock_request->oid_, lock_request->rid_);
    default:
      break;
    }
  }
} // namespace bustub
