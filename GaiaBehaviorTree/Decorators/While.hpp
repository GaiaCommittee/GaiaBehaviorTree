#pragma once

#include "ConditionalDecorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Behavior decorated by While will be executed until condition of While returns Result::Failure.
     */
    class While : public ConditionalDecorator
    {
        REFLECT_TYPE(Gaia::BehaviorTree::Decorators, ConditionalDecorator)
    protected:
        /**
         * @brief Execute the first sub behavior if the condition behavior returns Result::Success.
         * @details Returns the last result of the decorated behavior as the whole result.
         */
        Result OnExecute() override
        {
            if (!GetConditionNode()) return Result::Failure;

            Result last_result = Result::Failure;

            while (GetConditionNode()->Execute() == Result::Success)
            {
                last_result = GetDecoratedNode()->Execute();
            }
            return last_result;
        }
    };
}