#include "ParallelSequence.hpp"

#include <tbb/tbb.h>

namespace Gaia::BehaviorTree::Containers
{
    Result ParallelSequence::OnExecute()
    {
        tbb::concurrent_vector<Result> results;
        results.reserve(this->Behaviors.size());
        tbb::parallel_for_each(this->Behaviors, [&results](Behavior* behavior){
            results.push_back(ExecuteBehavior(behavior));
        });
        for (const auto& result : results)
        {
            if (result == Result::Failure) return Result::Failure;
        }
        return Result::Success;
    }
}