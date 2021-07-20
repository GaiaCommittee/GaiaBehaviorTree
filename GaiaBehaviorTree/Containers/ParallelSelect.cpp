#include "ParallelSelect.hpp"
#include <tbb/tbb.h>

namespace Gaia::BehaviorTree::Containers
{
    /// Execute sub behaviors in sequence.
    Result ParallelSelect::OnExecute()
    {
        tbb::concurrent_vector<Result> results;
        auto sub_elements = GetReflectedElements("Behaviors");
        results.reserve(sub_elements.size());
        tbb::parallel_for_each(sub_elements, [&results](Reflection::ReflectedElement* element){
            auto* behavior = dynamic_cast<Behavior*>(element);
            if (behavior)
                results.push_back(behavior->Execute());
        });
        for (const auto& result : results)
        {
            if (result == Result::Success) return Result::Success;
        }
        return Result::Failure;
    }
}