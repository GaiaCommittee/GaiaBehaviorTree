#include "ParallelSequence.hpp"

#include <tbb/tbb.h>

namespace Gaia::BehaviorTree::Containers
{
    Result ParallelSequence::OnExecute()
    {
        tbb::concurrent_vector<Result> results;
        results.reserve(GetSubBehaviors().size());
        tbb::parallel_for_each(this->GetSubBehaviors(), [&results](std::unique_ptr<Behavior>& behavior){
            results.push_back(behavior->Execute());
        });
        for (const auto& result : results)
        {
            if (result == Result::Failure) return Result::Failure;
        }
        return Result::Success;
    }
}