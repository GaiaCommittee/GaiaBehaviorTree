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
    private:
        /// Behaviors sequence.
        std::list<Behavior*> Behaviors;

    protected:
        /// Emplace a behavior node into this select.
        void OnEmplace(Behavior *behavior) override;

        /// Clear the whole select.
        void OnClear() override;

    public:
        /// Execute the select until a node fails.
        Result Execute() override;
    };
}
