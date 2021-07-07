#include "While.hpp"

namespace Gaia::BehaviorTree::Decorators
{

    Result While::Execute()
    {
        if (!ConditionNode || !GetInnerBehavior()) return Result::Failure;

        Result last_result = Result::Failure;

        while (ConditionNode->Execute() != Result::Failure)
        {
            if (GetInnerBehavior())
            {
                last_result = GetInnerBehavior()->Execute();
            }
        }
        return last_result;
    }

    Result While::OnInitialize()
    {
        if (!GetContext()) return Result::Failure;
        return GetContext()->UnregisterBehavior(ConditionNode.get()) & Decorator::OnInitialize();
    }

    Result While::OnFinalize()
    {
        if (!GetContext()) return Result::Failure;
        return GetContext()->UnregisterBehavior(ConditionNode.get()) & Decorator::OnInitialize();
    }
}