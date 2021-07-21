#include "Reflector.hpp"

namespace Gaia::BehaviorTree
{
    /// Construct a new behavior.
    std::unique_ptr<Behavior> BehaviorTree::Reflector::NewBehavior(const std::string &behavior_name)
    {
        auto finder = Behavior::GetDerivedClasses().find(behavior_name);
        if (finder != Behavior::GetDerivedClasses().end())
        {
            if (finder->second) return std::unique_ptr<Behavior>(finder->second());
        }
        return nullptr;
    }
}