#include "While.hpp"
#include "../Context.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /// Execute until the condition node returns Failure.
    Result While::OnExecute()
    {
        if (!ConditionNode || !GetInnerBehavior()) return Result::Failure;

        Result last_result = Result::Failure;

        while (ExecuteBehavior(ConditionNode.get()) != Result::Failure)
        {
            if (GetInnerBehavior())
            {
                last_result = ExecuteBehavior(GetInnerBehavior());
            }
        }
        return last_result;
    }
}