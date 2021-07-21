#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Execute the decorated node and return a const result.
     * @tparam TargetResult The result to return after the execution.
     */
    template <Result TargetResult>
    class ForceResult : public Decorator
    {
    protected:
        Result OnExecute() override
        {
            if (GetDecoratedBehavior()) GetDecoratedBehavior()->Execute();
            return TargetResult;
        }
    };

    using ForceSucess = ForceResult<Result::Success>;
    REFLECT_DERIVED_CLASS(Behavior, ForceSuccess)
    using ForceFailure = ForceResult<Result::Failure>;
    REFLECT_DERIVED_CLASS(Behavior, ForceFailure)
}