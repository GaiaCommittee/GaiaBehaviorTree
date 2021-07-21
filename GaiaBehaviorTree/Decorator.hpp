#pragma once

#include "Behavior.hpp"

#include <memory>
#include <type_traits>

namespace Gaia::BehaviorTree
{
    /**
     * @brief Decorator can add advanced logic functions to behavior by conditional execution and
     *        decorating the result of a behavior.
     */
    class Decorator : public Behavior
    {
        REFLECT_INTERFACE(Decorator)
    private:
        /// The decorated behavior.
        Behavior* DecoratedBehavior {nullptr};

    protected:
        /// Get the decorated behavior.
        [[nodiscard]] inline Behavior* GetDecoratedBehavior() const noexcept
        {
            return DecoratedBehavior;
        }

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
            if (DecoratedBehavior) RemoveSubBehavior(DecoratedBehavior);
            DecoratedBehavior = AddSubBehavior<BehaviorType>(arguments...);
            return DecoratedBehavior;
        }

        /**
        * @brief Construct and add this behavior to this decorator.
        * @tparam BehaviorType The type of the behavior to construct.
        * @tparam ConstructorArguments The types of arguments to pass to the constructor.
        * @param arguments The arguments to pass to the constructor.
        * @return The reference to this decorator.
        * @details
        *  Previous decorated behavior will be finalized and replaced.
        */
        template <typename BehaviorType, typename... ConstructorArguments>
        Decorator& DoEmplace(ConstructorArguments... arguments)
        {
            if (DecoratedBehavior) RemoveSubBehavior(DecoratedBehavior);
            DecoratedBehavior = AddSubBehavior<BehaviorType>(arguments...);
            return *this;
        }
    };
}