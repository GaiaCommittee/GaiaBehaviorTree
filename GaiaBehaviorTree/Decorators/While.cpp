#include "While.hpp"
#include "../Context.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /// Execute until the condition node returns Failure.
    Result While::OnExecute()
    {
        if (!ConditionNode || !GetDecoratedBehavior()) return Result::Failure;

        Result last_result = Result::Failure;

        while (ConditionNode->Execute() != Result::Failure)
        {
            if (GetDecoratedBehavior())
            {
                last_result = GetDecoratedBehavior()->Execute();
            }
        }
        return last_result;
    }
}