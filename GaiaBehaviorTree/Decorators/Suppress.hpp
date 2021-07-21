#pragma once

#include "../Decorator.hpp"

#include <chrono>

namespace Gaia::BehaviorTree::Decorators
{
    /**
     * @brief Suppress the execution frequency by set the minial execution interval time.
     * @details
     *  If the elapsed time to the last execution is less than required, the execution will be skipped,
     *  and return the default value.
     */
    class Suppress : public Decorator
    {
    public:
        /// Default result to return.
        Result DefaultResult {Result::Failure};
        /// Execution interval time.
        std::chrono::steady_clock::duration IntervalTime {std::chrono::milliseconds(10)};

    protected:
        /// Time point of the last execution.
        std::chrono::steady_clock::time_point LastExecutionTime {std::chrono::steady_clock::now() - IntervalTime};
        /// Execute the decorated node if elapsed time is more than interval time.
        Result OnExecute() override;
    };
}
