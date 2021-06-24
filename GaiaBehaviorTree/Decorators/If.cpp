#include "If.hpp"

namespace Gaia::BehaviorTree::Decorators
{

    Result If::Execute()
    {
        if (ConditionNode && ConditionNode->Execute() == Result::Success)
        {
            return GetInnerBehavior()->Execute();
        }
        return Result::Failure;
    }

    /// Additionally initialize the condition node.
    Result If::OnInitialize()
    {
        if (!GetContext()) return Result::Failure;
        return GetContext()->InitializeBehavior(ConditionNode.get()) & Decorator::OnInitialize();
    }

    /// Additionally finalize the condition node.
    Result If::OnFinalize()
    {
        if (!GetContext()) return Result::Failure;
        return GetContext()->InitializeBehavior(ConditionNode.get()) & Decorator::OnFinalize();
    }
}