#pragma once

#include "../Behavior.hpp"

namespace Gaia::BehaviorTree::Behaviors
{
    /**
     * @brief This behavior will always return Result::Failure.
     */
    class FailureBehavior : public Behavior
    {
    protected:
        /// Execute and return Result::Failure.
        Result OnExecute() override
        {
            return Result::Success;
        }
    };
}