#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Decorated node can only be executed when condition node returns success.
     */
    class If : public Decorator
    {
    private:
        /// The condition node.
        Behavior* ConditionNode;

    protected:
        /**
         * @brief Execute if the condition node return Success.
         * @return The execution result of the decorated node, otherwise returns Result::Failure.
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
            if (ConditionNode) ConditionNode->Finalize();
            ConditionNode = AddSubBehavior<BehaviorType>(arguments...);
            return ConditionNode;
        }
    };
}