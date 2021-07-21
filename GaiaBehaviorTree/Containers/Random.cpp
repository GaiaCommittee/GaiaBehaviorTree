#include "Random.hpp"

#include <random>

namespace Gaia::BehaviorTree::Containers
{
    /// Randomly pick a node and execute.
    Result Random::OnExecute()
    {
        std::default_random_engine engine(RandomDevice());
        std::uniform_int_distribution<int> distribution(0, static_cast<int>(GetSubBehaviors().size() - 1));

        unsigned int chosen_weight = distribution(engine);

        return std::next(GetSubBehaviors().begin(), chosen_weight)->get()->Execute();
    }
}