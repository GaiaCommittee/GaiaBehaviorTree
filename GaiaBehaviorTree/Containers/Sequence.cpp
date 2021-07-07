#include "Sequence.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// OnExecute the whole sequence.
    Result Sequence::OnExecute()
    {
        for (auto* behavior : Behaviors)
        {
            if (behavior && ExecuteBehavior(behavior) == Result::Failure) return Result::Failure;
        }
        return Result::Success;
    }

    /// Emplace a behavior node into this sequence.
    void Sequence::OnEmplace(Gaia::BehaviorTree::Behavior *behavior)
    {
        Behaviors.emplace_back(behavior);
    }

    /// Clear the whole sequence.
    void Sequence::OnClear()
    {
        Behaviors.clear();
    }
}