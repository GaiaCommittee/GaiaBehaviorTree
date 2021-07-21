#pragma once

#include "ConditionalDecorator.hpp"

#include <functional>

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Decorated node will be repeatedly executed until condition node returns failure.
     */
    class While : public ConditionalDecorator
    {
    protected:
        /**
         * @brief Execute until the condition node returns Failure.
         * @return Returns Failure if condition node is null, otherwise returns the result from the inner behavior
         *         when condition node firstly returns Failure.
         */
        Result OnExecute() override;
    };

    REFLECT_DERIVED_CLASS(Behavior, While)
}