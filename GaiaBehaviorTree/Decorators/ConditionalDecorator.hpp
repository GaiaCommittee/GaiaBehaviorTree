#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Interface for decorators with condition.
     */
    class ConditionalDecorator : public Decorator
    {
        REFLECT_TYPE(Gaia::BehaviorTree, Decorator)
    private:
        /// Node for condition.
        Behavior* ConditionNode {nullptr};

    protected:
        /// Get the condition node of this decorator.
        [[nodiscard]] inline Behavior* GetConditionNode() const noexcept
        {
            return ConditionNode;
        }

        /// Get decorated node and condition node.
        void OnInitialize() override
        {
            // Get decorated node.
            Decorator::OnInitialize();

            auto sub_elements = GetReflectedElements("Condition");
            if (sub_elements.empty()) return;
            auto* condition = dynamic_cast<Behavior*>(*sub_elements.begin());
            if (!condition) return;
            ConditionNode = condition;
        }
    };
}

#ifndef CONDITION_MACRO
#define CONDITION_MACRO
#define CONDITION(BehaviorType, BehaviorName, ConstructorArguments...) \
    BEHAVIOR(BehaviorType, BehaviorName, {"Condition"}, ##ConstructorArguments)
#define CONDITION_BEGIN(NodeType, NodeName) BEHAVIOR_BEGIN(NodeType, NodeName)
#define CONDITION_END(NodeName, ConstructorArguments) BEHAVIOR_END(NodeName, \
    std::unordered_set<std::string>{"Condition"}, ##ConstructorArguments)
#endif