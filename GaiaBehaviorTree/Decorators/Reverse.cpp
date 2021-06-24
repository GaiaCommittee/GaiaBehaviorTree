#include "Reverse.hpp"

namespace Gaia::BehaviorTree::Decorators
{
    /// Execute and reverse the result.
    Result Reverse::Execute()
    {
        if (GetInnerBehavior())
        {
            return !GetInnerBehavior()->Execute();
        }
        return Result::Success;
    }
}