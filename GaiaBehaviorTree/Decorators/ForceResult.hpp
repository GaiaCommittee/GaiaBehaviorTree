#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Force result will force the decorated node return the target result.
     */
    template <Result TargetResult>
    class ForceResult : public Decorator
    {
        REFLECT_TYPE(Gaia::BehaviorTree, Decorator)
    protected:
        /// Execute the first decorated behavior and returns the reversal result.
        Result OnExecute() override
        {
            if (GetDecoratedNode())
            {
                GetDecoratedNode()->Execute();
            }
            return TargetResult;
        }
    };
}