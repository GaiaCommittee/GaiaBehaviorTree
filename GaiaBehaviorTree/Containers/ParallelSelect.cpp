#include "ParallelSelect.hpp"
#include <tbb/tbb.h>

namespace Gaia::BehaviorTree::Containers
{
    /// Execute sub behaviors in sequence.
    Result ParallelSelect::OnExecute()
    {
        tbb::concurrent_vector<Result> results;
        results.reserve(GetInnerNodes().size());
        tbb::parallel_for_each(GetInnerNodes(), [&results](Behavior* behavior){
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