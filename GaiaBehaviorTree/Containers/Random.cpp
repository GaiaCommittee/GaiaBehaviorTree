#include "Random.hpp"

#include <random>

namespace Gaia::BehaviorTree::Containers
{
    /// Execute sub behaviors in sequence.
    Result Random::OnExecute()
    {
        auto sub_elements = GetReflectedElements("Behavior");

        if (sub_elements.empty()) return Result::Failure;

        std::default_random_engine engine(RandomDevice());
        std::uniform_int_distribution<int> distribution(0, static_cast<int>(sub_elements.size() - 1));

        auto chosen_iterator = std::next(sub_elements.begin(), distribution(engine));

        auto* behavior = dynamic_cast<Behavior*>(*chosen_iterator);

        if (behavior)
        {
            return behavior->Execute();
        }
        return Result::Failure;
    }
}