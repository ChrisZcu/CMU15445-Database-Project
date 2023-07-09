//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// aggregation_executor.cpp
//
// Identification: src/execution/aggregation_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
#include <memory>
#include <vector>

#include "execution/executors/aggregation_executor.h"

namespace bustub
{

    AggregationExecutor::AggregationExecutor(ExecutorContext *exec_ctx, const AggregationPlanNode *plan,
                                             std::unique_ptr<AbstractExecutor> &&child)
        : AbstractExecutor(exec_ctx),
          plan_(plan), child_(std::move(child)),
          aht_(plan_->GetAggregates(), plan_->GetAggregateTypes()), aht_iterator_(aht_.Begin()) {}

    void AggregationExecutor::Init()
    {
        child_->Init();
        // 备份所有的数据到aht中
        Tuple tuple;
        RID rid;
        while (child_->Next(&tuple, &rid))
        {
            auto aggregate_key = MakeAggregateKey(&tuple);
            auto aggregate_value = MakeAggregateValue(&tuple);
            aht_.InsertCombine(aggregate_key, aggregate_value);
        }
        aht_iterator_ = aht_.Begin();
    }

    auto AggregationExecutor::Next(Tuple *tuple, RID *rid) -> bool
    {
        Schema s(*plan_->output_schema_);
        if (aht_iterator_ == aht_.End())
            return false;
        std::vector<Value> v(aht_iterator_.Key().group_bys_);
        for (const auto &i : aht_iterator_.Val().aggregates_)
        {
            v.push_back(i);
        }
        *tuple = {v, &s};
        ++aht_iterator_;
        return true;
    }

    auto AggregationExecutor::GetChildExecutor() const -> const AbstractExecutor * { return child_.get(); }

} // namespace bustub
