#pragma once

#include "../Container.hpp"

#include <list>

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief A sequence will stop and return Failure when any inner Behavior returns Failure,
     *        and otherwise return Success.
     */
    class Sequence : public Container
    {
    public:
        /// Execute the sequence until a node fails.
        Result OnExecute() override;
    };

    REFLECT_DERIVED_CLASS(Behavior, Sequence)
}