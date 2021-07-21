#include "ParallelSelect.hpp"

#include <tbb/tbb.h>

namespace Gaia::BehaviorTree
{
    /// Execute all nodes in parallel.
    Result Containers::ParallelSelect::OnExecute()
    {
        tbb::concurrent_vector<Result> results;
        results.reserve(GetSubBehaviors().size());
        tbb::parallel_for_each(GetSubBehaviors(), [&results](std::unique_ptr<Behavior>& behavior){
            results.push_back(behavior->Execute());
        });
        for (const auto& result : results)
        {
            if (result == Result::Success) return Result::Success;
        }
        return Result::Failure;
    }
}