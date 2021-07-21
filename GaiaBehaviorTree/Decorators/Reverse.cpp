#include "Reverse.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /// OnExecute and reverse the result.
    Result Reverse::OnExecute()
    {
        if (GetDecoratedBehavior())
        {
            return !GetDecoratedBehavior()->Execute();
        }
        return Result::Success;
    }
}