//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// nested_index_join_executor.cpp
//
// Identification: src/execution/nested_index_join_executor.cpp
//
// Copyright (c) 2015-19, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "execution/executors/nested_index_join_executor.h"

namespace bustub
{

  NestIndexJoinExecutor::NestIndexJoinExecutor(ExecutorContext *exec_ctx, const NestedIndexJoinPlanNode *plan,
                                               std::unique_ptr<AbstractExecutor> &&child_executor)
      : AbstractExecutor(exec_ctx), plan_(plan), child_(std::move(child_executor))
  {
    index_info_ = exec_ctx->GetCatalog()->GetIndex(plan_->index_oid_);
    table_info_ = exec_ctx->GetCatalog()->GetTable(index_info_->table_name_);
    tree_ = dynamic_cast<BPlusTreeIndexForOneIntegerColumn *>(index_info_->index_.get());
    is_inner_ = plan_->GetJoinType() == JoinType::INNER;
    if (!(plan->GetJoinType() == JoinType::LEFT || plan->GetJoinType() == JoinType::INNER))
    {
      // Note for 2022 Fall: You ONLY need to implement left join and inner join.
      throw bustub::NotImplementedException(fmt::format("join type {} not supported", plan->GetJoinType()));
    }
  }

  void NestIndexJoinExecutor::Init()
  {
    child_->Init();
  }

  auto NestIndexJoinExecutor::Next(Tuple *tuple, RID *rid) -> bool
  {
    // 右边表有索引，则转换为right table join left，此时child对应的是原本的左表，
    // 因此通过next获得每一行的child的值，再在左表中进行索引查找
    Tuple left_tuple{};
    RID emit_rid{};
    std::vector<Value> val;
    while (child_->Next(&left_tuple, &emit_rid))
    {
      // 判断key是否在答案list，是否符合谓词
      Value value = plan_->KeyPredicate()->Evaluate(&left_tuple, child_->GetOutputSchema());
      if (!value.IsNull())
      {
        std::vector<RID> rids;
        tree_->ScanKey(Tuple{{value}, index_info_->index_->GetKeySchema()}, &rids, exec_ctx_->GetTransaction());
        Tuple right_tuple{};
        // 找到对应的行rid
        if (!rids.empty())
        {
          table_info_->table_->GetTuple(rids[0], &right_tuple, exec_ctx_->GetTransaction());
          for (uint32_t i = 0; i < child_->GetOutputSchema().GetColumns().size(); ++i)
          {
            val.push_back(left_tuple.GetValue(&child_->GetOutputSchema(), i));
          }
          for (uint32_t i = 0; i < plan_->InnerTableSchema().GetColumns().size(); ++i)
          {
            val.push_back(right_tuple.GetValue(&plan_->InnerTableSchema(), i));
          }
          *tuple = Tuple(val, &GetOutputSchema());
          return true; // 找到了对应的行，不需要考虑inner join/left join
        }
        if (!is_inner_)
        {
          for (uint32_t i = 0; i < child_->GetOutputSchema().GetColumns().size(); ++i)
          {
            val.push_back(left_tuple.GetValue(&child_->GetOutputSchema(), i));
          }
          for (uint32_t i = 0; i < plan_->InnerTableSchema().GetColumns().size(); ++i)
          {
            val.push_back(ValueFactory::GetNullValueByType(plan_->InnerTableSchema().GetColumn(i).GetType()));
          }
          *tuple = Tuple(val, &GetOutputSchema());
          return true;
        }
      }
    }
    return false;
  }

} // namespace bustub
