#include "Suppress.hpp"

namespace Gaia::BehaviorTree
{
    /// Execute the decorated node if elapsed time is more than interval time.
    Result Decorators::Suppress::OnExecute()
    {
        if (!GetInnerBehavior()) return DefaultResult;
        auto current_time_point = std::chrono::steady_clock::now();
        if (current_time_point - LastExecutionTime > IntervalTime)
        {
            LastExecutionTime = current_time_point;
            return ExecuteBehavior(GetInnerBehavior());
        }
        return DefaultResult;
    }
}
