#pragma once

#include "../Decorator.hpp"

#include <functional>

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Decorated node will be repeatedly executed until condition node returns failure.
     */
    class While : public Decorator
    {
    private:
        /// The condition node.
        std::unique_ptr<Behavior> ConditionNode;

    protected:
        /// Additionally initialize the condition node.
        Result OnInitialize() override;
        /// Additionally finalize the condition node.
        Result OnFinalize() override;
        /**
         * @brief Execute until the condition node returns Failure.
         * @return Returns Failure if condition node is null, otherwise returns the result from the inner behavior
         *         when condition node firstly returns Failure.
         */
        Result OnExecute() override;

    public:
        /**
         * @brief Construct and add this behavior as the condition node to this decorator.
         * @tparam BehaviorType The type of the behavior to construct.
         * @tparam ConstructorArguments The types of arguments to pass to the constructor.
         * @param arguments The arguments to pass to the constructor.
         * @return The pointer to the constructed behavior.
         * @details
         *  Previous decorated behavior will be replaced without triggering OnFinalize(),
         *  because it may have not been initialized by the time it is replaced.
         */
        template <typename BehaviorType, typename... ConstructorArguments>
        BehaviorType* EmplaceCondition(ConstructorArguments... arguments)
        {
            static_assert(std::is_base_of_v<Behavior, BehaviorType>, "BehaviorType should be derived from Behavior.");
            auto node_instance = std::make_unique<BehaviorType>(arguments...);
            auto* node_pointer = node_instance.get();
            ConditionNode = std::move(node_instance);
            return node_pointer;
        }
    };
}