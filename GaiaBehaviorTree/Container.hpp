#pragma once

#include "Behavior.hpp"

#include <list>
#include <memory>

namespace Gaia::BehaviorTree
{
    /**
     * @brief Container can manage several nodes with a controllable specific execution flow.
     */
    class Container : public Behavior
    {
    protected:
        /**
         * @brief Deserialize this container.
         * @param root_node Iterator to the document node of this container.
         * @return Amount of consumed nodes on the same level.
         */
        void Deserialize(const boost::property_tree::ptree &root_node) override;

    public:
        /**
        * @brief Construct and add a behavior to this container.
        * @tparam BehaviorType The type of the behavior to construct.
        * @tparam ConstructorArguments The types of arguments to pass to the constructor.
        * @param arguments The arguments to pass to the constructor.
        * @return The pointer to the constructed behavior.
        */
        template <typename BehaviorType, typename... ConstructorArguments>
        BehaviorType* Emplace(ConstructorArguments... arguments)
        {
            auto* node = AddSubBehavior<BehaviorType>(arguments...);
            return node;
        }

        /**
        * @brief Construct and add a behavior to this container.
        * @tparam BehaviorType The type of the behavior to construct.
        * @tparam ConstructorArguments The types of arguments to pass to the constructor.
        * @param arguments The arguments to pass to the constructor.
        * @return Reference to this container.
        */
        template <typename BehaviorType, typename... ConstructorArguments>
        Container& DoEmplace(ConstructorArguments... arguments)
        {
            Emplace<BehaviorType>(arguments...);
            return *this;
        }
    };
}