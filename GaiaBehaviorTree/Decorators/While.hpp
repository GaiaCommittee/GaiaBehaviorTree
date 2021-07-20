#pragma once

#include "../Behavior.hpp"
#include <type_traits>
#include <memory>

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Behavior decorated by While will be executed until condition of While returns Result::Failure.
     * @tparam ConditionBehavior Type of condition behavior.
     * @tparam ConstructorArguments Type of condition behavior constructor arguments.
     */
    template <typename ConditionBehavior, typename... ConstructorArguments>
    class While : public Behavior
    {
    private:
        std::unique_ptr<Behavior> Condition;

    public:
        /// None reflection constructor.
        While() : Condition(std::make_unique<ConditionBehavior>())
        {}
        /// Reflection constructor.
        explicit While(Behavior* parent) :
                Condition(std::make_unique<ConditionBehavior>()), Behavior(parent)
        {}
        /// None reflection constructor.
        explicit While(ConstructorArguments... arguments) :
                Condition(std::make_unique<ConditionBehavior>(arguments...))
        {}
        /// Reflection constructor.
        explicit While(Behavior* parent, ConstructorArguments... arguments) :
                Condition(std::make_unique<ConditionBehavior>(arguments...)), Behavior(parent)
        {}

    protected:
        /**
         * @brief Execute the first sub behavior if the condition behavior returns Result::Success.
         * @details Returns the last result of the decorated behavior as the whole result.
         */
        Result OnExecute() override
        {
            auto sub_elements = GetReflectedElements("Behavior");
            auto* behavior = dynamic_cast<Behavior*>(*sub_elements.begin());
            if (!behavior) return Result::Failure;

            Result last_result = Result::Failure;

            while (Condition->Execute() == Result::Success)
            {
                last_result = behavior->Execute();
            }
            return last_result;
        }
    };
}