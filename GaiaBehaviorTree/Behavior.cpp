#include "Behavior.hpp"

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
}
