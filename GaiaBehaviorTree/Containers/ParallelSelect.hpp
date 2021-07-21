#pragma once

#include "Select.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief A parallel sequence will stop and return Failure when any inner Behavior returns Failure,
     *        and otherwise return Success. All nodes will be executed in parallel, but the result can
     *        only be determined after all nodes have been executed.
     */
     class ParallelSelect : public Select
     {
     protected:
         /// Execute the nodes in parallel.
         Result OnExecute() override;
     };

    REFLECT_DERIVED_CLASS(Behavior, ParallelSelect)
    REFLECT_DERIVED_CLASS(Container, ParallelSelect)
}