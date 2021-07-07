#pragma once

#include "AbstractWeightContainer.hpp"

#include <tuple>
#include <random>

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief This container will randomly pick up a behavior node to execute insides it.
     * @details
     *  Every behavior node has a weight and its possibility to be picked up is based on that.
     */
    class Random : public AbstractWeightContainer
    {
    protected:
        /// Device for generating random value.
        std::random_device RandomDevice;

        /// Execute the select until a node fails.
        Result OnExecute() override;
    };
}
