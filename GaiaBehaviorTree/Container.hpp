#pragma once

#include "Behavior.hpp"

namespace Gaia::BehaviorTree
{
    /**
     * @brief A decorator can dynamically add or modify functions of behaviors.
     */
    class Container : public Behavior
    {
        REFLECT_TYPE(Gaia::BehaviorTree, Behavior)
    private:
        /// Behavior nodes insides this container.
        std::list<Behavior*> InnerNodes {nullptr};

    protected:
        /// Get the behavior node decorated by this decorator.
        [[nodiscard]] inline const std::list<Behavior*>& GetInnerNodes() const noexcept
        {
            return InnerNodes;
        }

        /// Get inner nodes.
        void OnInitialize() override
        {
            InnerNodes.clear();
            auto sub_elements = GetReflectedElements("Behavior");
            for (auto* sub_element : sub_elements)
            {
                auto* behavior = dynamic_cast<Behavior*>(sub_element);
                if (behavior) InnerNodes.push_back(behavior);
            }
        }
    };
}

#ifndef CONTAINER_MACRO
#define CONTAINER_MACRO
#define CONTAINER_BEGIN(NodeType, NodeName) BEHAVIOR_BEGIN(NodeType, NodeName)
#define CONTAINER_END(NodeName, ConstructorArguments...) BEHAVIOR_END(NodeName, ##ConstructorArguments)
#endif