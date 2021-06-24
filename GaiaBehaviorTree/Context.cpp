#include "Context.hpp"
#include "Behavior.hpp"

namespace Gaia::BehaviorTree
{
    /// Initialize the given behavior node.
    Result Context::InitializeBehavior(Behavior *node)
    {
        if (!node || node->EnvironmentContext != nullptr) return Result::Failure;

        node->EnvironmentContext = this;
        node->EnvironmentBlackboard = &Blackboard;
        return node->OnInitialize();
    }

    /// Finalize the given behavior node.
    Result Context::FinalizeBehavior(Behavior *node)
    {
        if (!node || node->EnvironmentContext != this) return Result::Failure;

        auto result = node->OnFinalize();
        node->EnvironmentContext = nullptr;
        node->EnvironmentBlackboard = nullptr;

        return result;
    }
}