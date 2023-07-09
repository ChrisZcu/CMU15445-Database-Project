//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// seq_scan_executor.cpp
//
// Identification: src/execution/seq_scan_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/seq_scan_executor.h"

namespace bustub
{

    SeqScanExecutor::SeqScanExecutor(ExecutorContext *exec_ctx, const SeqScanPlanNode *plan) : AbstractExecutor(exec_ctx), plan_(plan) {}

    void SeqScanExecutor::Init()
    {
        // 获得table信息，catalog 为hashmap,通过gettable获得对应的table信息
        auto table_info = exec_ctx_->GetCatalog()->GetTable(plan_->GetTableOid());
        table_ = table_info->table_.get();
        // 迭代器初始化
        iterator_ = std::make_unique<TableIterator>(table_->Begin(exec_ctx_->GetTransaction()));
        // 全表扫描，锁定整张表
        try
        { // 获取隔离级别
            if (exec_ctx_->GetTransaction()->GetIsolationLevel() != IsolationLevel::READ_UNCOMMITTED && !exec_ctx_->GetLockManager()->LockTable(exec_ctx_->GetTransaction(), LockManager::LockMode::INTENTION_SHARED, table_info->oid_))
            {
                throw ExecutionException("lock table share failed");
            }
        }
        catch (TransactionAbortException &e)
        {
            throw ExecutionException("seq scan Transaction abort");
        }
    }

    auto SeqScanExecutor::Next(Tuple *tuple, RID *rid) -> bool
    {
        // 尝试获取读锁,锁定行
        try
        {
            if (exec_ctx_->GetTransaction()->GetIsolationLevel() != IsolationLevel::READ_UNCOMMITTED)
            {
                if (!exec_ctx_->GetLockManager()->LockRow(exec_ctx_->GetTransaction(), LockManager::LockMode::SHARED,
                                                          exec_ctx_->GetCatalog()->GetTable(plan_->GetTableOid())->oid_, (*(*iterator_)).GetRid()))
                {
                    throw ExecutionException("lock row intention share failed");
                }
            }
        }
        catch (TransactionAbortException &e)
        {
            throw ExecutionException("seq scan TransactionAbort");
        }
        if (*iterator_ != table_->End())
        {
            *tuple = *((*iterator_)++);
            *rid = tuple->GetRid();
        }
        return false;
    }

} // namespace bustub
