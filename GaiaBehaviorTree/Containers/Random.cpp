#include "Random.hpp"

#include <random>

namespace Gaia::BehaviorTree::Containers
{
    /// Execute sub behaviors in sequence.
    Result Random::OnExecute()
    {
        if (GetInnerNodes().empty()) return Result::Failure;

        std::default_random_engine engine(RandomDevice());
        std::uniform_int_distribution<int> distribution(0, static_cast<int>(GetInnerNodes().size() - 1));

        auto chosen_iterator = std::next(GetInnerNodes().begin(), distribution(engine));

        if (*chosen_iterator)
        {
            return (*chosen_iterator)->Execute();
        }
        return Result::Failure;
    }
}