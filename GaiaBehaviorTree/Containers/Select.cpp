#include "Select.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// Execute the whole sequence.
    Result Select::Execute()
    {
        for (auto* behavior : Behaviors)
        {
            if (behavior && behavior->Execute() == Result::Success) return Result::Success;
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