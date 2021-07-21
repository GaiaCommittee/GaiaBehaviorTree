#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Reverse decorator will execute and reverse the result of the decorated behavior.
     */
    class Reverse : public Decorator
    {
    protected:
        /// Execute and reverse the result.
        Result OnExecute() override;
    };

    REFLECT_DERIVED_CLASS(Behavior, Reverse)
}