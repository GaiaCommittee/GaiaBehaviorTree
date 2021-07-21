#pragma once

#include "../Container.hpp"

#include <random>

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief Random is a container that will randomly pick a sub behavior and return its execution result.
     *        Every sub behavior has equal possibility.
     */
    class Random : public Container
    {
        REFLECT_TYPE(Gaia::BehaviorTree, Container)
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