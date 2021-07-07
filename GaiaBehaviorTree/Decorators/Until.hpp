#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree
{
    /**
     * @brief This decorator will repeatedly execute the inner behavior until it returns StopValue.
     * @tparam StopValue When decorated node returns this value, the execution loop will stop.
     */
    template<Result StopValue>
    class Until : public Decorator
    {
    public:
        /**
         * @brief Repeatedly execute the decorated node until it returns StopValue.
         * @return StopValue.
         */
        Result Execute() override
        {
            if (!GetInnerBehavior()) return Result::Failure;
            while (GetInnerBehavior()->Execute() != StopValue);
            return StopValue;
        }
    };

    /// Repeatedly execute the decorated node until it succeeded.
    using UntilSucceeded = Until<Result::Success>;
    /// Repeatedly execute the decorated node until it failed.
    using UntilFailed = Until<Result::Failure>;
}