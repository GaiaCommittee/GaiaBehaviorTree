#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Reverse decorator will execute and reverse the result of the decorated behavior.
     */
    class Reverse : public Decorator
    {
    public:
        /// Execute and reverse the result.
        Result Execute() override;
    };
}