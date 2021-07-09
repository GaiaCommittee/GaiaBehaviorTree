#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Exectue the decorated node and return a const result.
     * @tparam TargetResult The result to return after the execution.
     */
    template <Result TargetResult>
    class ForceResult : public Decorator
    {
    protected:
        Result OnExecute() override
        {
            if (GetInnerBehavior()) ExecuteBehavior(GetInnerBehavior());
            return TargetResult;
        }
    };
}