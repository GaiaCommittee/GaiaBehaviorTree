#pragma once

#include <GaiaReflection/GaiaReflection.hpp>
#include <GaiaBlackboards/GaiaBlackboards.hpp>
#include <memory>
#include <list>
#include <boost/property_tree/ptree.hpp>
#include "Result.hpp"

namespace Gaia::BehaviorTree
{
    /**
     * @brief Behavior can be declared in other behaviors and have their own sub behaviors.
     */
    class Behavior : public Reflection::ReflectedInterface
    {
        REFLECT_INTERFACE(Behavior)
    private:
        /**
         * @brief Blackboard for variables accessing.
         * @details
         *  It will be initialized as a new blackboard if it is null when this behavior is initializing,
         *  and it will be passed to sub behaviors of this behavior.
         */
        std::shared_ptr<Blackboards::Blackboard> ContextBlackboard {nullptr};
        /// Whether the context blackboard is constructed and owned by this behavior.
        bool OwnedContextBlackboard {false};

        /// Sub behaviors for this behavior.
        std::list<std::unique_ptr<Behavior>> SubBehaviors;

    public:
        /// None reflection constructor.
        Behavior() = default;

    protected:
        /// Add a sub behavior into this behavior.
        Behavior* AddSubBehavior(std::unique_ptr<Behavior>&& behavior)
        {
            auto& pointer = SubBehaviors.emplace_back(std::move(behavior));
            return pointer.get();
        }

        /// Add a sub behavior into this behavior.
        template<typename BehaviorType, typename... Arguments>
        BehaviorType* AddSubBehavior(Arguments... arguments)
        {
            static_assert(std::is_base_of_v<Behavior, BehaviorType>, "BehaviorType should be derived from Behavior.");
            auto iterator = SubBehaviors.emplace(std::make_unique<BehaviorType>(arguments...));
            return iterator->get();
        }

        /// Remove the given sub behavior.
        void RemoveSubBehavior(Behavior* behavior);

        /// Clear all sub behaviors.
        void ClearSubBehavior();

        /// Get sub behaviors of this behavior.
        [[nodiscard]] const decltype(SubBehaviors)& GetSubBehaviors() const noexcept
        {
            return SubBehaviors;
        }

        /// Get the blackboard of this behavior.
        [[nodiscard]] inline Blackboards::Blackboard* GetBlackboard() const noexcept
        {
            return ContextBlackboard.get();
        }
        /// Invoked when this behavior is initializing.
        virtual void OnInitialize() {};
        /// Invoked when this behavior is finalizing.
        virtual void OnFinalize() {};
        /// Invoked when this behavior is being executed.
        virtual Result OnExecute() = 0;

    public:
        /// Initialize this behavior and its sub behaviors.
        void Initialize();
        /// Finalize this behavior and its sub behaviors.
        void Finalize();
        /// Execute this behavior.
        Result Execute();

        /**
         * @brief Do nothing by default. Derived classes can read settings here.
         * @param root_node Document node for current behavior.
         */
        virtual void Deserialize(const boost::property_tree::ptree &root_node);
    };
};