#pragma once

#include "ConditionalDecorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Behavior decorated by If will only be executed when condition of If returns Result::Success.
     */
    class If : public ConditionalDecorator
    {
        REFLECT_TYPE(Gaia::BehaviorTree::Decorators, ConditionalDecorator)
    protected:
        /// Execute the first sub behavior if the condition behavior returns Result::Success.
        Result OnExecute() override
        {
            if (GetConditionNode() && GetConditionNode()->Execute() == Result::Success &&
                GetDecoratedNode())
            {
                return GetDecoratedNode()->Execute();
            }
            return Result::Failure;
        }
    };
}