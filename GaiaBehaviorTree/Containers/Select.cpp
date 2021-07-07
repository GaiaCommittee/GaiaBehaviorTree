#include "Select.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// OnExecute the whole sequence.
    Result Select::OnExecute()
    {
        for (auto* behavior : Behaviors)
        {
            if (behavior && ExecuteBehavior(behavior) == Result::Success) return Result::Success;
        }
        return Result::Failure;
    }

    /// Emplace a behavior node into this sequence.
    void Select::OnEmplace(Gaia::BehaviorTree::Behavior *behavior)
    {
        Behaviors.emplace_back(behavior);
    }

    /// Clear the whole sequence.
    void Select::OnClear()
    {
        Behaviors.clear();
    }
}