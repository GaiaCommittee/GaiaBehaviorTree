#pragma once

#include "../Decorator.hpp"

#include <chrono>

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Suppress the execution frequency by set the minial execution interval time.
     * @details
     *  If the elapsed time to the last execution is less than required, then it will let the invoker thread
     *  sleep the remaining time before execute the decorated behavior.
     */
    class Suppress : public Decorator
    {
    public:
        /// Execution interval time.
        std::chrono::steady_clock::duration IntervalTime {std::chrono::milliseconds(10)};

    protected:
        /// Time point of the last execution.
        std::chrono::steady_clock::time_point LastExecutionTime {std::chrono::steady_clock::now() - IntervalTime};
        /// Execute the decorated node if elapsed time is more than interval time.
        Result OnExecute() override;

    public:
        /// Read optional interval time form "IntervalTime", and then invoke Decorator::Deserialize(...).
        void Deserialize(const boost::property_tree::ptree &root_node) override;
    };

    REFLECT_DERIVED_CLASS(Behavior, Suppress)
}
