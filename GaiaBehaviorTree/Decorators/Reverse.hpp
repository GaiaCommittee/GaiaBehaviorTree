#pragma once

#include "../Behavior.hpp"
#include <type_traits>
#include <memory>

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Reverse will reverse the execution result of the decorated behavior.
     */
    class Reverse : public Behavior
    {
    protected:
        /// Execute the first decorated behavior and returns the reversal result.
        Result OnExecute() override
        {
            if (Condition->Execute() == Result::Success)
            {
                auto sub_elements = GetReflectedElements("Behavior");
                auto* behavior = dynamic_cast<Behavior*>(*sub_elements.begin());
                if (behavior) return !behavior->Execute();
            }
            return Result::Failure;
        }
    };
}