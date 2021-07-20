#pragma once

#include "../Behavior.hpp"

#include <random>

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief Random is a container that will randomly pick a sub behavior and return its execution result.
     *        Every sub behavior has equal possibility.
     */
    class Random : public Behavior
    {
    public:
        using Behavior::Behavior;

    protected:
        /// Device for generating random value.
        std::random_device RandomDevice;

        /**
         * @brief Execute sub behaviors in sequence.
         * @return Returns Result::Failure when firstly meets a failure, otherwise return Result::Success.
         */
        Result OnExecute() override;
    };
}