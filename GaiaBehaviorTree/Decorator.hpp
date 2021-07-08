#pragma once

#include "Behavior.hpp"

#include <memory>
#include <type_traits>

namespace Gaia::BehaviorTree
{
    class Behavior;

    /**
     * @brief Decorator can add advanced logic functions to behavior by conditional execution and
     *        decorating the result of a behavior.
     */
    class Decorator : public Behavior
    {
        friend class Context;

    private:
        /// The decorated behavior.
        std::unique_ptr<Behavior> DecoratedBehavior {nullptr};

    protected:
        /// Trigger OnInitialize() of the DecoratedBehavior by default.
        Result OnInitialize() override;
        /// Trigger OnFinalize() of the DecoratedBehavior by default.
        Result OnFinalize() override;

        /// Get the pointer to the decorated behavior.
        Behavior* GetInnerBehavior();

    public:
        /**
         * @brief Construct and add this behavior to this decorator.
         * @tparam BehaviorType The type of the behavior to construct.
         * @tparam ConstructorArguments The types of arguments to pass to the constructor.
         * @param arguments The arguments to pass to the constructor.
         * @return The pointer to the constructed behavior.
         * @details
         *  Previous decorated behavior will be replaced without triggering OnFinalize(),
         *  because it may have not been initialized by the time it is replaced.
         */
        template <typename BehaviorType, typename... ConstructorArguments>
        BehaviorType* Emplace(ConstructorArguments... arguments)
        {
            static_assert(std::is_base_of_v<Behavior, BehaviorType>, "BehaviorType should be derived from Behavior.");
            UnregisterBehavior(GetContext(), DecoratedBehavior.get());
            DecoratedBehavior = std::make_unique<BehaviorType>(arguments...);
            RegisterBehavior(GetContext(), DecoratedBehavior.get());
            return static_cast<BehaviorType*>(DecoratedBehavior.get());
        }
    };
}