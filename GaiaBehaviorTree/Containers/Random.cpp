#include "Random.hpp"

#include <random>

namespace Gaia::BehaviorTree::Containers
{
    /// Randomly pick a node and execute.
    Result Random::OnExecute()
    {
        std::default_random_engine engine(RandomDevice());
        std::uniform_int_distribution<int> distribution(1, static_cast<int>(TotalWeight));

        unsigned int chosen_weight = distribution(engine);

        unsigned long current_total_weight = 0;
        for (const auto& [weight, node] : WeightNodes)
        {
            current_total_weight += weight;
            if (current_total_weight > chosen_weight)
            {
                return ExecuteBehavior(node);
            }
        }
    }
}