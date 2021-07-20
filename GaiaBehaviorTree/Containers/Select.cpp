#include "Select.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// Execute sub behaviors in sequence.
    Result Select::OnExecute()
    {
        for (auto* sub_element : GetReflectedElements("Behavior"))
        {
            auto* behavior = dynamic_cast<Behavior*>(sub_element);
            if(behavior->Execute() == Result::Success)
            {
                return Result::Success;
            }
        }
        return Result::Failure;
    }
}