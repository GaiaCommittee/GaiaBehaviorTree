#pragma once

#include "../Behavior.hpp"
#include <type_traits>
#include <memory>

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Behavior decorated by Until Success will be executed in a loop until it succeeds.
     */
    class UntilSucceed : public Behavior
    {
    protected:
        /// Execute the first decorated behavior and returns the reversal result.
        Result OnExecute() override
        {
            auto sub_elements = GetReflectedElements("Behavior");
            auto* behavior = dynamic_cast<Behavior*>(*sub_elements.begin());
            while (Condition->Execute() != Result::Success)
            return Result::Success;
        }
    };

    /**
     * @brief Behavior decorated by Until Success will be executed in a loop until it fails.
     */
    class UntilFail : public Behavior
    {
    protected:
        /// Execute the first decorated behavior and returns the reversal result.
        Result OnExecute() override
        {
            auto sub_elements = GetReflectedElements("Behavior");
            auto* behavior = dynamic_cast<Behavior*>(*sub_elements.begin());
            while (Condition->Execute() != Result::Failure)
                return Result::Success;
        }
    };
}