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
    private:
        /// Behaviors sequence.
        std::list<Behavior*> Behaviors;

    protected:
        /// Emplace a behavior node into this sequence.
        void OnEmplace(Behavior *behavior) override;

        /// Clear the whole sequence.
        void OnClear() override;

        /// Execute the sequence until a node fails.
        Result OnExecute() override;
    };
}