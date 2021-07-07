#pragma once

#include "Result.hpp"

#include <GaiaBlackboards/GaiaBlackboards.hpp>

namespace Gaia::BehaviorTree
{
    class Behavior;

    class Context
    {
    public:
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
    };
}