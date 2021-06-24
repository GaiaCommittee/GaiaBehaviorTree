#include "Decorator.hpp"
#include "Context.hpp"

namespace Gaia::BehaviorTree
{
    /// Default initialize implementation to initialize the decorated behaivor.
    Result Decorator::OnInitialize()
    {
        if (!GetContext()) return Result::Failure;

        if (DecoratedBehavior)
        {
            return GetContext()->InitializeBehavior(DecoratedBehavior.get());
        }
        return Result::Success;
    }

    /// Default finalize implementation to finalize the decorated behavior.
    Result Decorator::OnFinalize()
    {
        if (!GetContext()) return Result::Failure;

        if (DecoratedBehavior)
        {
            return GetContext()->FinalizeBehavior(DecoratedBehavior.get());
        }
        return Result::Success;
    }

    /// Get the pointer to the decorated behavior.
    Behavior *Decorator::GetInnerBehavior()
    {
        return DecoratedBehavior.get();
    }
}