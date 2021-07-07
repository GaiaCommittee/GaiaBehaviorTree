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
            return GetContext()->RegisterBehavior(DecoratedBehavior.get());
        }
        return Result::Success;
    }

    /// Default finalize implementation to finalize the decorated behavior.
    Result Decorator::OnFinalize()
    {
        if (!GetContext()) return Result::Failure;

        if (DecoratedBehavior)
        {
            return GetContext()->UnregisterBehavior(DecoratedBehavior.get());
        }
        return Result::Success;
    }

    /// Get the pointer to the decorated behavior.
    Behavior *Decorator::GetInnerBehavior()
    {
        return DecoratedBehavior.get();
    }
}