#pragma once

#include "../Behavior.hpp"

namespace Gaia::BehaviorTree::Behaviors
{
    /**
     * @brief This behavior will always return Result::Success.
     */
    class SuccessBehavior : public Behavior
    {
    protected:
        /// Execute and return Result::Success.
        Result OnExecute() override
        {
            return Result::Success;
        }
    };
}
