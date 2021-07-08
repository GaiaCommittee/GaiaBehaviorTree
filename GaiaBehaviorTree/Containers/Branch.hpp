#pragma once

#include "../Behavior.hpp"

#include <memory>

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief A special kind of container, which only have two sub behaviors,
     *        corresponding to Result::Success and Result::Failure of condition node separately.
     */
    class Branch : public Behavior
    {
    protected:
        /// Result gotten from it will decide the branch to go on.
        std::unique_ptr<Behavior> ConditionNode;
        /// Executed when condition result is Result::Success.
        std::unique_ptr<Behavior> SuccessBranch;
        /// Executed when condition result is Result::Failure.
        std::unique_ptr<Behavior> FailureBranch;

        /**
         * @brief Execute the corresponding branch according to the result of condition node.
         * @return The execution result of the chosen branch node.
         */
        Result OnExecute() override;

    public:
        /// Position enum for emplace node.
        enum class Position
        {
            Condition,
            OnSuccess,
            OnFailure
        };

        /**
        * @brief Construct and add a behavior to this container.
        * @tparam BehaviorType The type of the behavior to construct.
        * @tparam ConstructorArguments The types of arguments to pass to the constructor.
        * @param arguments The arguments to pass to the constructor.
        * @return The pointer to the constructed behavior.
        */
        template <typename BehaviorType, Position position, typename... ConstructorArguments>
        BehaviorType* Emplace(ConstructorArguments... arguments)
        {
            static_assert(std::is_base_of_v<Behavior, BehaviorType>, "BehaviorType should be derived from Behavior.");
            auto node_pointer = std::make_unique<BehaviorType>(arguments...);
            auto* node = node_pointer.get();
            RegisterBehavior(GetContext(), node);
            if (position == Position::OnSuccess) {
                if (SuccessBranch) UnregisterBehavior(GetContext(), SuccessBranch.get());
                SuccessBranch = std::move(node_pointer);
            } else if (position == Position::OnFailure) {
                if (FailureBranch) UnregisterBehavior(GetContext(), FailureBranch.get());
                FailureBranch = std::move(node_pointer);
            } else {
                if (ConditionNode) UnregisterBehavior(GetContext(), ConditionNode.get());
                ConditionNode = std::move(node_pointer);
            }
            return node;
        }
    };
}