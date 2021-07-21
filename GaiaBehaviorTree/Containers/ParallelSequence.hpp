#pragma once

#include "Sequence.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief A parallel sequence will stop and return Failure when any inner Behavior returns Failure,
     *        and otherwise return Success. All nodes will be executed in parallel, but the result can
     *        only be determined after all nodes have been executed.
     */
    class ParallelSequence : public Sequence
    {
    protected:
        /// Execute the sequence in parallel.
        Result OnExecute() override;
    };

    REFLECT_DERIVED_CLASS(Behavior, ParallelSequence)
    REFLECT_DERIVED_CLASS(Container, ParallelSequence)
}
