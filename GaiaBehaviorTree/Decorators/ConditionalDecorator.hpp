#pragma once

#include "../Decorator.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    class ConditionalDecorator : public Decorator
    {
    private:
        /// The condition node.
        Behavior* ConditionBehavior {nullptr};

    protected:
        /// Get the condition behavior.
        [[nodiscard]] inline Behavior* GetConditionBehavior() const noexcept
        {
            return ConditionBehavior;
        }

    public:
        /**
         * @brief Deserialize the condition behavior,
         *        then invoke Decorator's Deserialize to deserialize the decorated behavior.
         */
        void Deserialize(const boost::property_tree::ptree &root_node) override;

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
            if (ConditionBehavior) ConditionBehavior->Finalize();
            ConditionBehavior = AddSubBehavior<BehaviorType>(arguments...);
            return ConditionBehavior;
        }
    };
}