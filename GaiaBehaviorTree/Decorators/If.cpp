#include "If.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /// Execute if the condition node return Success.
    Result If::OnExecute()
    {
        if (ConditionNode && ExecuteBehavior(ConditionNode.get()) == Result::Success && GetInnerBehavior())
        {
            return ExecuteBehavior(GetInnerBehavior());
        }
        return Result::Failure;
    }
}