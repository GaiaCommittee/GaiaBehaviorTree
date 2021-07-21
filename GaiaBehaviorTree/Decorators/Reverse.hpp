#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Reverse will reverse the execution result of the decorated behavior.
     */
    class Reverse : public Decorator
    {
        REFLECT_TYPE(Gaia::BehaviorTree, Decorator)
    protected:
        /// Execute the first decorated behavior and returns the reversal result.
        Result OnExecute() override
        {
            if (GetDecoratedNode())
            {
                return !GetDecoratedNode()->Execute();
            }
            return Result::Failure;
        }
    };
}