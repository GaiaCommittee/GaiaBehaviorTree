#include "Sequence.hpp"

namespace Gaia::BehaviorTree::Containers
{
    /// Execute sub behaviors in sequence.
    Result Sequence::OnExecute()
    {
        for (auto* sub_element : GetReflectedElements("Behavior"))
        {
            auto* behavior = dynamic_cast<Behavior*>(sub_element);
            if(behavior->Execute() == Result::Failure)
            {
                return Result::Failure;
            }
        }
        return Result::Success;
    }
}