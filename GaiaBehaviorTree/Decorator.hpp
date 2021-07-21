#pragma once

#include "Behavior.hpp"

namespace Gaia::BehaviorTree
{
    /**
     * @brief A decorator can dynamically add or modify functions of behaviors.
     */
    class Decorator : public Behavior
    {
        REFLECT_TYPE(Gaia::BehaviorTree, Behavior)
    private:
        /// Behavior node decorated by this decorator.
        Behavior* DecoratedNode {nullptr};

    protected:
        /// Get the behavior node decorated by this decorator.
        [[nodiscard]] inline Behavior* GetDecoratedNode() const noexcept
        {
            return DecoratedNode;
        }

        /// Get the decorated node from reflection behaviors.
        void OnInitialize() override
        {
            auto sub_elements = GetReflectedElements("Behavior");
            if (sub_elements.empty()) return;
            auto* behavior = dynamic_cast<Behavior*>(*sub_elements.begin());
            if (!behavior) return;
            DecoratedNode = behavior;
        }
    };
}

#ifndef DECORATOR_MACRO
#define DECORATOR_MACRO
#define DECORATOR_BEGIN(NodeType, NodeName) BEHAVIOR_BEGIN(NodeType, NodeName)
#define DECORATOR_END(NodeName, ConstructorArguments...) BEHAVIOR_END(NodeName, ##ConstructorArguments)
#endif