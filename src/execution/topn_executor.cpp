#include "execution/executors/topn_executor.h"

namespace bustub
{

    TopNExecutor::TopNExecutor(ExecutorContext *exec_ctx, const TopNPlanNode *plan,
                               std::unique_ptr<AbstractExecutor> &&child_executor)
        : AbstractExecutor(exec_ctx), plan_(plan), child_(std::move(child_executor)) {}

    void TopNExecutor::Init()
    {
        child_->Init();
        // 比较器
        auto cmp = [order_bys = plan_->order_bys_, schema = child_->GetOutputSchema()](const Tuple *tuple_a, const Tuple *tuple_b)
        {
            for (auto &order_by : order_bys)
            {
                switch (order_by)
                {
                case OrderByType::INVALID:
                case OrderByType::DEFAULT:
                case OrderByType::ASC:
                    if (static_cast<bool>(order_by.second->Evaluate(&tuple_a, schema).CompareLessThan(order_by.second->Evaluate(&tuple_b, schema))))
                        return true;
                    else
                        return false;
                    break;
                case OrderByType::DESC:
                    if (static_cast<bool>(order_by.second->Evaluate(&tuple_a, schema).CompareLessThan(order_by.second->Evaluate(&tuple_b, schema))))
                        return false;
                    else
                        return true;
                    break;

                default:
                    break;
                }
            }
            return false;
        };
        Tuple tuple{};
        RID rid{};
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(cmp)> pq(cmp);
        while (child_->Next(&tuple, &rid))
        {
            pq.push(tuple);
            if (pq.size() > plan_->GetN())
                pq.pop();
        }
        while (!pq.empty())
        {
            tuples_stack_.push(pq.top());
            pq.pop();
        }
    }

    auto TopNExecutor::Next(Tuple *tuple, RID *rid) -> bool
    {
        if (tuples_stack_.empty())
            return false;
        *tuple = tuples_stack_.top();
        *rid = tuple->GetRid();
        tuples_stack_.pop();
        return true;
    }

} // namespace bustub
