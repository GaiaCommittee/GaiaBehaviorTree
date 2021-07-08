#include "AbstractWeightContainer.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// Emplace a node into the list.
    void AbstractWeightContainer::OnEmplace(Behavior *behavior)
    {
        AddWeightNode(behavior, 1);
    }

    /// Clear the whole list.
    void AbstractWeightContainer::OnClear()
    {
        for (const auto& [weight, node] : Behaviors)
        {
            UnregisterBehavior(GetContext(), node);
        }
        Behaviors.clear();
        TotalWeightSource = 0;
    }

    /// Add a node with a weight into this list.
    void AbstractWeightContainer::AddWeightNode(Behavior *behavior, unsigned int weight)
    {
        TotalWeightSource += weight;
        Behaviors.emplace_back(weight, behavior);
    }
}