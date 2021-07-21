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
        Behavior* ConditionNode;

    protected:
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
            if (ConditionNode) ConditionNode->Finalize();
            ConditionNode = AddSubBehavior<BehaviorType>(arguments...);
            return ConditionNode;
        }
    };
}