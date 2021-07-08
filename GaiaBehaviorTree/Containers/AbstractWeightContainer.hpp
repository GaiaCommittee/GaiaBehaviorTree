#pragma once

#include "../Container.hpp"

#include <tuple>
#include <list>

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief In this container, and each node has a corresponding weight.
     */
    class AbstractWeightContainer : public Container
    {
    private:
        ///Total weights of all inner behaviors.
        unsigned int TotalWeightSource {0};
        /// Behaviors with weights.
        std::list<std::tuple<unsigned int, Behavior*>> Behaviors;

    protected:
        /// This node should not be used directly.
        AbstractWeightContainer() = default;

        /// List of nodes and its weights.
        const decltype(Behaviors)& WeightNodes {Behaviors};
        /// Total weight of all nodes in this container.
        const decltype(TotalWeightSource)& TotalWeight {TotalWeightSource};

    protected:
        /**
         * @brief Add a node with the given weight,
         * @param behavior The behavior to add.
         * @param weight Weight of the node.
         */
        void AddWeightNode(Behavior* behavior, unsigned int weight = 1);

    protected:
        /// Emplace a behavior node into this container, with default weight 1.
        void OnEmplace(Behavior *behavior) final;

        /// Clear the whole select.
        void OnClear() final;

    public:
        /**
        * @brief Construct and add a behavior to this container.
        * @tparam BehaviorType The type of the behavior to construct.
        * @tparam ConstructorArguments The types of arguments to pass to the constructor.
        * @param arguments The arguments to pass to the constructor.
        * @return The pointer to the constructed behavior.
        */
        template <typename BehaviorType, typename... ConstructorArguments>
        BehaviorType* EmplaceWeightNode(unsigned int weight, ConstructorArguments... arguments)
        {
            static_assert(std::is_base_of_v<Behavior, BehaviorType>, "BehaviorType should be derived from Behavior.");
            auto* node = Emplace<BehaviorType>(arguments...);
            RegisterBehavior(GetContext(), node);
            AddWeightNode(node, weight);
            return node;
        }

        /**
        * @brief Construct and add a behavior to this container repeatedly.
        * @tparam BehaviorType The type of the behavior to construct.
        * @tparam ConstructorArguments The types of arguments to pass to the constructor.
        * @param count The count of the times to add this behavior.
        * @param arguments The arguments to pass to the constructor.
        * @return The pointer to the constructed behavior.
        */
        template <typename BehaviorType, typename... ConstructorArguments>
        BehaviorType* RepeatedlyEmplaceWeightNode(unsigned int count, unsigned int weight,
                                                  ConstructorArguments... arguments)
        {
            auto* node = Container::Emplace<BehaviorType>(arguments...);
            RegisterBehavior(GetContext(), node);
            for (auto index = 0; index < count; ++index)
            {
                AddWeightNode(node, weight);
            }
            return node;
        }
    };
}