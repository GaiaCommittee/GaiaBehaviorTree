#include "Behavior.hpp"
#include "Context.hpp"

namespace Gaia::BehaviorTree
{
    /// Get the context of this behavior.
    Context *BehaviorTree::Behavior::GetContext()
    {
        return EnvironmentContext;
    }

    /// Get the blackboard in the context of this behavior.
    Blackboards::Blackboard *Behavior::GetBlackboard()
    {
        return EnvironmentBlackboard;
    }

    /// Default implementation for initialize event.
    Result Behavior::OnInitialize()
    {
        return Result::Success;
    }

    /// Default implementation for finalize event.
    Result Behavior::OnFinalize()
    {
        return Result::Success;
    }

    /// Execute another behavior.
    Result Behavior::ExecuteBehavior(Behavior *behavior)
    {
        if (!behavior) throw std::runtime_error("Failed to execute behavior, target behavior is null.");
        return behavior->OnExecute();
    }

    Result Behavior::RegisterBehavior(Context *context, Behavior *behavior)
    {
        if (!context) throw std::runtime_error("Failed to register behavior: null context.");
        if (!behavior) throw std::runtime_error("Failed to register behavior: null behavior.");
        return context->RegisterBehavior(behavior);
    }

    Result Behavior::UnregisterBehavior(Context *context, Behavior *behavior)
    {
        if (!context) throw std::runtime_error("Failed to unregister behavior: null context.");
        if (!behavior) throw std::runtime_error("Failed to unregister behavior: null behavior.");
        return context->UnregisterBehavior(behavior);
    }
}
