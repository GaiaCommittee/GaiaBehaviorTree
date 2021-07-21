#pragma once

#include "ConditionalDecorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Behavior decorated by Until Success will be executed in a loop until it succeeds.
     */
    template <Result DesiredResult>
    class Until : public Decorator
    {
        REFLECT_TYPE(Gaia::BehaviorTree, Decorator)
    protected:
        /// Execute the first decorated behavior and returns the reversal result.
        Result OnExecute() override
        {
            if (!GetDecoratedNode()) return !DesiredResult;
            while (GetDecoratedNode()->Execute() != DesiredResult)
            {
                if (GetDecoratedNode()) GetDecoratedNode()->Execute();
            }
            return DesiredResult;
        }
    };
}