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

    /// Additionally initialize the condition node.
    Result If::OnInitialize()
    {
        if (!GetContext()) return Result::Failure;
        return RegisterBehavior(GetContext(), ConditionNode.get()) & Decorator::OnInitialize();
    }

    /// Additionally finalize the condition node.
    Result If::OnFinalize()
    {
        if (!GetContext()) return Result::Failure;
        return UnregisterBehavior(GetContext(), ConditionNode.get()) & Decorator::OnFinalize();
    }
}