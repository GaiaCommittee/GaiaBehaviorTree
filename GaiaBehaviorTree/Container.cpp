#include "Container.hpp"

namespace Gaia::BehaviorTree
{
    /// Default initialize implementation by initialize all inner nodes.
    Result Container::OnInitialize()
    {
        if (!GetContext()) return Result::Failure;

        for (auto& behavior : InnerBehaviors)
        {
            GetContext()->RegisterBehavior(behavior.get());
        }

        return Result::Success;
    }

    /// Default finalize implementation by finalize all inner nodes.
    Result Container::OnFinalize()
    {
        if (!GetContext()) return Result::Failure;

        for (auto& behavior : InnerBehaviors)
        {
            GetContext()->UnregisterBehavior(behavior.get());
        }

        return Result::Success;
    }

    /// Clear all inner nodes.
    void Container::Clear()
    {
        OnClear();
        InnerBehaviors.clear();
    }
}