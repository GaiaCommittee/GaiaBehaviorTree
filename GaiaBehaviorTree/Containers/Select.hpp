#pragma once

#include "../Container.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /**
     * @brief A Select will stop and return Success when any inner Behavior returns Success,
     *        and otherwise return Failure.
     */
    class Select : public Container
    {
    public:
        /// Execute the select until a node fails.
        Result OnExecute() override;
    };

    REFLECT_DERIVED_CLASS(Behavior, Select)
    REFLECT_DERIVED_CLASS(Container, Select)
}
