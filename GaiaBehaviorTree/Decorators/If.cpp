#include "If.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /// Execute if the condition node return Success.
    Result If::OnExecute()
    {
        if (GetDecoratedBehavior() && ConditionNode && ConditionNode->Execute() == Result::Success)
        {
            return GetDecoratedBehavior()->Execute();
        }
        return Result::Failure;
    }
}