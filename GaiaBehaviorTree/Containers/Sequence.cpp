#include "Sequence.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// Execute sub behaviors in sequence.
    Result Sequence::OnExecute()
    {
        for (auto* behavior : GetInnerNodes())
        {
            if(behavior->Execute() == Result::Failure)
            {
                return Result::Failure;
            }
        }
        return Result::Success;
    }
}