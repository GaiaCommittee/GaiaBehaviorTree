#pragma once

#include "../Behavior.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief Sequence is a list of behaviors that will be executed in sequence,
     *        the whole sequence returns Result::Success if all sub behaviors returns success,
     *        and returns Result::Failure when firstly meets a failure.
     */
    class Sequence : public Behavior
    {
    public:
        using Behavior::Behavior;

    protected:
        /**
         * @brief Execute sub behaviors in sequence.
         * @return Returns Result::Failure when firstly meets a failure, otherwise return Result::Success.
         */
        Result OnExecute() override;
    };
}