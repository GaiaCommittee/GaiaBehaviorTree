#include "Select.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// OnExecute the whole sequence.
    Result Select::OnExecute()
    {
        for (auto& behavior : GetSubBehaviors())
        {
            if (behavior && behavior->Execute() == Result::Success) return Result::Success;
        }
        return Result::Failure;
    }
}