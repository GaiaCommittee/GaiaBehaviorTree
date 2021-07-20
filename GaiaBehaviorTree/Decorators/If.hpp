#pragma once

#include "../Behavior.hpp"
#include <type_traits>
#include <memory>

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Behavior decorated by If will only be executed when condition of If returns Result::Success.
     * @tparam ConditionBehavior Type of condition behavior.
     * @tparam ConstructorArguments Type of condition behavior constructor arguments.
     */
    template <typename ConditionBehavior, typename... ConstructorArguments>
    class If : public Behavior
    {
    private:
        std::unique_ptr<Behavior> Condition;

    public:
        /// None reflection constructor.
        If() : Condition(std::make_unique<ConditionBehavior>())
        {}
        /// Reflection constructor.
        explicit If(Behavior* parent) :
                Condition(std::make_unique<ConditionBehavior>()), Behavior(parent)
        {}
        /// None reflection constructor.
        explicit If(ConstructorArguments... arguments) :
            Condition(std::make_unique<ConditionBehavior>(arguments...))
        {}
        /// Reflection constructor.
        explicit If(Behavior* parent, ConstructorArguments... arguments) :
            Condition(std::make_unique<ConditionBehavior>(arguments...)), Behavior(parent)
        {}

    protected:
        /// Execute the first sub behavior if the condition behavior returns Result::Success.
        Result OnExecute() override
        {
            if (Condition->Execute() == Result::Success)
            {
                auto sub_elements = GetReflectedElements("Behavior");
                auto* behavior = dynamic_cast<Behavior*>(*sub_elements.begin());
                if (behavior) return behavior->Execute();
            }
            return Result::Failure;
        }
    };
}