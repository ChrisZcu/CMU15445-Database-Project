//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// insert_executor.cpp
//
// Identification: src/execution/insert_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <memory>

#include "execution/executors/insert_executor.h"

namespace bustub
{

    InsertExecutor::InsertExecutor(ExecutorContext *exec_ctx, const InsertPlanNode *plan,
                                   std::unique_ptr<AbstractExecutor> &&child_executor)
        : AbstractExecutor(exec_ctx), plan_(plan), child_executor_(std::move(child_executor)) {}

    void InsertExecutor::Init()
    {
        throw NotImplementedException("InsertExecutor is not implemented");
    }
    // 一定是从下游pull数据
    auto InsertExecutor::Next([[maybe_unused]] Tuple *tuple, RID *rid) -> bool
    {
        if (isSuccessful_)
            return false;
        Tuple tup;
        RID r;
        std::vector<Value> num;

        std::vector<Column> col;
        col.emplace_back("", INTEGER);
        Schema schmema(col);
        int s = 0; // 最终返回的结果，插入的数目
        while (child_executor_->Next(&tup, &r))
        {
            // 插入table中
            if (table_->InsertTuple(tup, &r, this->GetExecutorContext()->GetTransaction()))
            {
                try
                {
                    if (!exec_ctx_->GetLockManager()->LockRow(exec_ctx_->GetTransaction(), LockManager::LockMode::EXCLUSIVE, table_info_->oid_, r))
                    {
                        throw ExecutionException("lock row execulation failed");
                    }
                }
                catch (TransactionAbortException &e)
                {
                    throw ExecutionException("insert Transaction Abort");
                }
                // 更新索引，只有在插入和删除需要更新索引
                auto indexs = exec_ctx_->GetCatalog()->GetTableIndexes(table_name_);
                for (auto index : indexs)
                {
                    auto key = tup.KeyFromTuple(table_info_->schema_, index->key_schema_, index->index_->GetKeyAttrs());
                    index->index_->InsertEntry(key, r, this->GetExecutorContext()->GetTransaction());
                }
                s++;
            }
        }
        Value v(INTEGER, s);
        num.push_back(v);
        Tuple t(num, &schmema);
        *tuple = tup;
        isSuccessful_ = true;
        return true;
    }

} // namespace bustub
