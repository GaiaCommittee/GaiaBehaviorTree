#include "While.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /// Execute until the condition node returns Failure.
    Result While::OnExecute()
    {
        if (!GetConditionBehavior() || !GetDecoratedBehavior()) return Result::Failure;

        Result last_result = Result::Failure;

        while (GetConditionBehavior()->Execute() != Result::Failure)
        {
            if (GetDecoratedBehavior())
            {
                last_result = GetDecoratedBehavior()->Execute();
            }
        }
        return last_result;
    }
}