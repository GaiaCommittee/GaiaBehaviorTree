#include "Suppress.hpp"
#include <thread>

namespace Gaia::BehaviorTree
{
    /// Execute the decorated node if elapsed time is more than interval time.
    Result Decorators::Suppress::OnExecute()
    {
        auto current_time_point = std::chrono::steady_clock::now();
        if (current_time_point - LastExecutionTime < IntervalTime)
        {
            std::this_thread::sleep_for(IntervalTime - (current_time_point - LastExecutionTime));
        }
        if (!GetDecoratedBehavior()) return Result::Failure;
        return GetDecoratedBehavior()->Execute();
    }

    void Decorators::Suppress::Deserialize(const boost::property_tree::ptree &root_node)
    {
        auto interval_milliseconds = root_node.get_optional<unsigned int>(
                "<xmlattr>.IntervalTime").value_or(10);
        IntervalTime = std::chrono::milliseconds(interval_milliseconds);

        Decorator::Deserialize(root_node);
    }
}
