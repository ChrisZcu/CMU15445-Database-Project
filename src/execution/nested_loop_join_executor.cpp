//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// nested_loop_join_executor.cpp
//
// Identification: src/execution/nested_loop_join_executor.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/nested_loop_join_executor.h"
#include "binder/table_ref/bound_join_ref.h"
#include "common/exception.h"

namespace bustub
{

  NestedLoopJoinExecutor::NestedLoopJoinExecutor(ExecutorContext *exec_ctx, const NestedLoopJoinPlanNode *plan,
                                                 std::unique_ptr<AbstractExecutor> &&left_executor,
                                                 std::unique_ptr<AbstractExecutor> &&right_executor)
      : AbstractExecutor(exec_ctx),
        plan_(plan),
        left_executor_(std::move(left_executor)),
        right_executor_(std::move(right_executor)),
        left_schema_(left_executor_->GetOutputSchema()),
        right_schema_(right_executor_->GetOutputSchema())
  {
    if (!(plan->GetJoinType() == JoinType::LEFT || plan->GetJoinType() == JoinType::INNER))
    {
      // Note for 2022 Fall: You ONLY need to implement left join and inner join.
      throw bustub::NotImplementedException(fmt::format("join type {} not supported", plan->GetJoinType()));
    }
    if (plan->GetJoinType() == JoinType::INNER)
      is_inner_ = true;
  }

  void NestedLoopJoinExecutor::Init()
  {
    // 在init中获取所有right的tuple
    Tuple tup;
    RID rid;
    left_executor_->Init();
    right_executor_->Init();
    while (right_executor_->Next(&tup, &rid))
    {
      right_tuples_.push_back(tup);
    }
  }

  auto NestedLoopJoinExecutor::Next(Tuple *tuple, RID *rid) -> bool
  {
    if (right_tuples_.empty())
    {
      if (is_inner_)
        return false;
      // left join
      if (!left_executor_->Next(&left_tuple_, &left_rid_))
        return false;
      std::vector<Value> v;
      // 一行结果
      for (uint32_t i = 0; i < left_schema_.GetColumns().size(); ++i)
      {
        v.push_back(left_tuple_.GetValue(&left_schema_, i));
      }
      for (uint32_t i = 0; i < right_schema_.GetColumns().size(); i++)
      {
        v.push_back(ValueFactory::GetNullValueByType(right_schema_.GetColumn(i).GetType()));
      }
      *tuple = {v, &GetOutputSchema()};
      return true;
    }
    if (index_ == 0)
    {
      if (!left_executor_->Next(&left_tuple_, &left_rid_))
      {
        return false;
      }
    }
    while (true)
    {
      // 完成一行，开始下一行right
      if (index_ == right_tuples_.size())
      {
        index_ = 0;
        is_match_ = false;
        if (!left_executor_->Next(&left_tuple_, &left_rid_))
        {
          return false;
        }
      }
      // 中间行,并且匹配到了left行
      for (; index_ < right_tuples_.size(); ++index_)
      {
        auto cmp = plan_->Predicate().EvaluateJoin(&left_tuple_, left_schema_, &right_tuples_[index_], right_schema_);
        if (!cmp.IsNull() && cmp.GetAs<bool>())
        {
          std::vector<Value> val;
          for (uint32_t i = 0; i < left_schema_.GetColumns().size(); ++i)
          {
            val.push_back(left_tuple_.GetValue(&left_schema_, i));
          }
          for (uint32_t i = 0; i < right_schema_.GetColumns().size(); ++i)
          {
            val.push_back(right_tuples_[index_].GetValue(&left_schema_, i));
          }
          *tuple = {val, &GetOutputSchema()};
          is_match_ = true;
          ++index_;
          return true;
        }
      }
      // 未找到匹配行，这时候区分inner join和left join
      if (!is_inner_)
      {
        if (is_match_)
        {
          is_match_ = false;
        }
        else
        {
          std::vector<Value> val;
          for (uint32_t i = 0; i < left_schema_.GetColumns().size(); ++i)
            val.push_back(left_tuple_.GetValue(&left_schema_, i));
          for (uint32_t i = 0; i < right_schema_.GetColumns().size(); ++i)
            val.push_back(ValueFactory::GetNullValueByType(right_schema_.GetColumn(i).GetType()));
          *tuple = {val, &GetOutputSchema()};
          return true;
        }
      }
    }
    return false;
  }

} // namespace bustub
