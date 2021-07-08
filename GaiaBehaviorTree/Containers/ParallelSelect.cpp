#include "ParallelSelect.hpp"

#include <tbb/tbb.h>

namespace Gaia::BehaviorTree
{
    /// Execute all nodes in parallel.
    Result Containers::ParallelSelect::OnExecute()
    {
        tbb::concurrent_vector<Result> results;
        results.reserve(this->Behaviors.size());
        tbb::parallel_for_each(this->Behaviors, [&results](Behavior* behavior){
            results.push_back(ExecuteBehavior(behavior));
        });
        for (const auto& result : results)
        {
            if (result == Result::Success) return Result::Success;
        }
        return Result::Failure;
    }
}