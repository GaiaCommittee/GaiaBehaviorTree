#pragma once

#include "ConditionalDecorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Decorated node can only be executed when condition node returns success.
     */
    class If : public ConditionalDecorator
    {
    private:
        /// The condition node.
        Behavior* ConditionBehavior;

    protected:
        /**
         * @brief Execute if the condition node return Success.
         * @return The execution result of the decorated node, otherwise returns Result::Failure.
         */
        Result OnExecute() override;
    };

    REFLECT_DERIVED_CLASS(Behavior, If)
}