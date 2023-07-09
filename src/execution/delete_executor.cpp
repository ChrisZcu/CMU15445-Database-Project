//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// delete_executor.cpp
//
// Identification: src/execution/delete_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <memory>

#include "execution/executors/delete_executor.h"

namespace bustub
{

    DeleteExecutor::DeleteExecutor(ExecutorContext *exec_ctx, const DeletePlanNode *plan,
                                   std::unique_ptr<AbstractExecutor> &&child_executor)
        : AbstractExecutor(exec_ctx), plan_(plan), child_executor_(std::move(child_executor)) {}

    void DeleteExecutor::Init()
    {
        table_info_ = exec_ctx_->GetCatalog()->GetTable(plan_->TableOid());
        table_name_ = table_info_->name_;
        table_ = table_info_->table_.get();
        iterator_ = std::make_unique<TableIterator>(table_->Begin(this->GetExecutorContext()->GetTransaction()));
        child_executor_->Init();
        try
        {
            if (!exec_ctx_->GetLockManager()->LockTable(exec_ctx_->GetTransaction(), LockManager::LockMode::INTENTION_EXCLUSIVE, table_info_->oid_))
            {
                throw ExecutionException("delete lock failed");
            }
        }
        catch (TransactionAbortException &e)
        {
            throw NotImplementedException("DeleteExecutor is not implemented");
        }
    }

    auto DeleteExecutor::Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool
    {
        if (isSuccessful_)
            return false;
        Tuple tup;
        RID r;
        int s = 0;
        std::vector<Value> num;
        std::vector<Column> c;
        c.emplace_back("", INTEGER);
        Schema schema(c);
        while (child_executor_->Next(&tup, &r))
        {
            // 标记删除
            if (table_->MarkDelete(r, this->GetExecutorContext()->GetTransaction()))
            {
                try
                {
                    if (!exec_ctx_->GetLockManager()->LockRow(exec_ctx_->GetTransaction(), LockManager::LockMode::EXCLUSIVE, table_info_->oid_, r))
                    {
                        throw ExecutionException("lock row exclusive failed");
                    }
                }
                catch (TransactionAbortException &e)
                {
                    throw ExecutionException("delete Transaction abort");
                }
                s++;
            }
        }
        Value v(INTEGER, s);
        num.push_back(v);
        Tuple t(num, &schema);
        *tuple = t;
        isSuccessful_ = true;
        return true;
    }

} // namespace bustub
