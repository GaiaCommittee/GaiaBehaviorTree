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
    private:
        /// Inner behaviors list for memory management.
        std::list<std::unique_ptr<Behavior>> InnerBehaviors;

    protected:
        /// Triggered when a new behavior is added to this container.
        virtual void OnEmplace(Behavior* behavior) = 0;
        /// Triggered before all inner behaviors are removed.
        virtual void OnClear() = 0;

        /// Initialize all inner nodes by default.
        Result OnInitialize() override;
        /// Finalize all inner nodes by default.
        Result OnFinalize() override;

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
            static_assert(std::is_base_of_v<Behavior, BehaviorType>, "BehaviorType should be derived from Behavior.");
            auto* node = InnerBehaviors.emplace_back(std::make_unique<BehaviorType>(arguments...)).get();
            RegisterBehavior(GetContext(), node);
            OnEmplace(node);
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
        BehaviorType* RepeatedlyEmplace(unsigned int count, ConstructorArguments... arguments)
        {
            auto* node = Container::Emplace<BehaviorType>(arguments...);
            RegisterBehavior(GetContext(), node);
            for (auto index = 0; index < count; ++index)
            {
                OnEmplace(node);
            }
            return node;
        }

        /// Clear this container without triggering finalize event.
        void Clear();
    };
}