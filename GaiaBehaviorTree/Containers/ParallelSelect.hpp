#pragma once

#include "../Container.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief Parallel Select is the parallel version of Select,
     *        which means that all sub behaviors will be executed in parallel.
     *        Select is a list of behaviors that will be executed in sequence,
     *        the whole select returns Result::Failure if all sub behaviors failed,
     *        and returns Result::Success when firstly meets a success.
     */
    class ParallelSelect : public Container
    {
        REFLECT_TYPE(Gaia::BehaviorTree, Container)
    protected:
        /**
         * @brief Execute sub behaviors in sequence.
         * @return Returns Result::Failure when firstly meets a failure, otherwise return Result::Success.
         */
        Result OnExecute() override;
    };
}
