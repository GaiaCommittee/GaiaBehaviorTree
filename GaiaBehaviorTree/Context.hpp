#pragma once

#include "Result.hpp"
#include "Behavior.hpp"

#include <memory>
#include <GaiaBlackboards/GaiaBlackboards.hpp>

namespace Gaia::BehaviorTree
{
    class Behavior;

    class Context
    {
        friend Result Behavior::RegisterBehavior(Context* context, Behavior* behavior);
        friend Result Behavior::UnregisterBehavior(Context* context, Behavior* behavior);

    protected:
        /// Values blackboard.
        Blackboards::Blackboard Blackboard;

        /**
         * @brief Initialize the given behavior node and bind it to this context.
         * @param node The behavior node to initialize.
         */
        Result RegisterBehavior(Behavior* node);
        /**
         * @brief Finalize the given behavior node and unbind it from this context.
         * @param node The behavior node to finalize.
         */
        Result UnregisterBehavior(Behavior* node);

        std::unique_ptr<Behavior> RootBehavior {nullptr};

    public:
        /**
         * @brief Construct and emplace this behavior as the root behavior of this context.
         * @tparam BehaviorType The type of the behavior to construct, usually a container node.
         * @tparam ConstructorArguments The types of arguments to pass to the constructor.
         * @param arguments The arguments to pass to the constructor.
         * @return The pointer to the constructed behavior.
         * @throws runtime_error If failed to construct or register new root behavior.
         * @details
         *  Previous root behavior will be replaced.
         */
        template <typename BehaviorType, typename... ConstructorArguments>
        BehaviorType* EmplaceRoot(ConstructorArguments... arguments)
        {
            static_assert(std::is_base_of_v<Behavior, BehaviorType>, "BehaviorType should be derived from Behavior.");
            if (RootBehavior) UnregisterBehavior(RootBehavior.get());
            RootBehavior = std::make_unique<BehaviorType>(arguments...);
            if (!RootBehavior) throw std::runtime_error("Failed to construct new root behavior.");
            if (RegisterBehavior(RootBehavior.get()) != Result::Success)
            {
                RootBehavior = nullptr;
                throw std::runtime_error("Failed to register the new root behavior.");
            }
            return RootBehavior.get();
        }

        /**
         * @brief Execute the root node.
         * @return The result of the root node.
         */
        Result Execute();
    };
}