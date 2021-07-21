#include "Sequence.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// OnExecute the whole sequence.
    Result Sequence::OnExecute()
    {
        for (auto& behavior : GetSubBehaviors())
        {
            if (behavior->Execute() == Result::Failure) return Result::Failure;
        }
        return Result::Success;
    }
}