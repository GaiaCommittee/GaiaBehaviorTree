#include "Select.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// Execute sub behaviors in sequence.
    Result Select::OnExecute()
    {
        for (auto* behavior : GetInnerNodes())
        {
            if(behavior->Execute() == Result::Success)
            {
                return Result::Success;
            }
        }
        return Result::Failure;
    }
}