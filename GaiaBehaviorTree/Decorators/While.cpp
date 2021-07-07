#include "While.hpp"
#include "../Context.hpp"

namespace Gaia::BehaviorTree::Decorators
{

    Result While::OnExecute()
    {
        if (!ConditionNode || !GetInnerBehavior()) return Result::Failure;

        Result last_result = Result::Failure;

        while (ExecuteBehavior(ConditionNode.get()) != Result::Failure)
        {
            if (GetInnerBehavior())
            {
                last_result = ExecuteBehavior(GetInnerBehavior());
            }
        }
        return last_result;
    }

    Result While::OnInitialize()
    {
        if (!GetContext()) return Result::Failure;
        return RegisterBehavior(GetContext(), ConditionNode.get()) & Decorator::OnInitialize();
    }

    Result While::OnFinalize()
    {
        if (!GetContext()) return Result::Failure;
        return UnregisterBehavior(GetContext(), ConditionNode.get()) & Decorator::OnInitialize();
    }
}