#include "If.hpp"
#include "../Reflector.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /// Execute if the condition node return Success.
    Result If::OnExecute()
    {
        if (GetDecoratedBehavior() && GetConditionBehavior() &&
            GetConditionBehavior()->Execute() == Result::Success)
        {
            return GetDecoratedBehavior()->Execute();
        }
        return Result::Failure;
    }
}