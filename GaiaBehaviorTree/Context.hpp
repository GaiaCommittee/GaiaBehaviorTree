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
         * @brief Initialize the given behavior node.
         * @param node The behavior node to initialize.
         */
        Result InitializeBehavior(Behavior* node);
        /**
         * @brief Finalize the given behavior node.
         * @param node The behavior node to finalize.
         */
        Result FinalizeBehavior(Behavior* node);
    };
}