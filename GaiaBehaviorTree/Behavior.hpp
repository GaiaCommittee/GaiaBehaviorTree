#pragma once

#include <GaiaBlackboards/GaiaBlackboards.hpp>

#include "Result.hpp"

namespace Gaia::BehaviorTree
{
    class Context;

    /**
     * @brief Interface for the node of behavior tree.
     */
    class Behavior
    {
        /// Context manages environment facilities and nodes instances.
        friend class Context;

    private:
        /// Pointer to the context of this node.
        Context* EnvironmentContext {nullptr};
        /// Pointer to the blackboard in the context of this node.
        Blackboards::Blackboard* EnvironmentBlackboard {nullptr};

    protected:
        /// Behavior should only created in a context.
        Behavior() = default;

        /// Get the context of this behavior.
        [[nodiscard]] Context* GetContext();
        /// Get the blackboard in the context of this behavior.
        [[nodiscard]] Blackboards::Blackboard* GetBlackboard();

        /**
         * @brief Execute another behavior.
         * @return Result returned by the given behavior.
         */
        static Result ExecuteBehavior(Behavior* behavior);
        /// Register the given behavior into the given context.
        static Result RegisterBehavior(Context* context, Behavior* behavior);
        /// Unregister the given behavior from the given context.
        static Result UnregisterBehavior(Context* context, Behavior* behavior);

        /**
         * @brief Invoked when this node is added to a context.
         * @return Whether this behavior is successfully initialized or not.
         */
        virtual Result OnInitialize();
        /**
         * @brief Invoked when this node is removed from a content.
         * @return Whether this behavior is successfully finalized or not.
         */
        virtual Result OnFinalize();
        /// Do something defined by the derived class.
        virtual Result OnExecute() = 0;

    public:
        /// Make destructor virtual for derived classes.
        virtual ~Behavior() = default;
    };
}