#include "Reverse.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /// OnExecute and reverse the result.
    Result Reverse::OnExecute()
    {
        if (GetInnerBehavior())
        {
            return !ExecuteBehavior(GetInnerBehavior());
        }
        return Result::Success;
    }
}