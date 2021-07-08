#include "Branch.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// Execute the corresponding branch according to the result of condition node.
    Result Branch::OnExecute()
    {
        if (!ConditionNode) return Result::Failure;
        auto result = ExecuteBehavior(ConditionNode.get());
        if (result == Result::Success)
        {
            return ExecuteBehavior(SuccessBranch.get());
        }
        else
        {
            return ExecuteBehavior(FailureBranch.get());
        }
    }
}