#include "Result.hpp"

namespace Gaia::BehaviorTree
{
    /// Get the reverse value of the given result.
    Result operator!(const Result& target)
    {
        if (target == Result::Success)
        {
            return Result::Failure;
        }
        return Result::Success;
    }

    /// Return Success when both a and b are Success.
    Result operator&(const Result& a, const Result& b)
    {
        if (a == Result::Success && b == Result::Success)
        {
            return Result::Success;
        }
        return Result::Failure;
    }
    /// Return Success when any of a and b is Success.
    Result operator|(const Result& a, const Result& b)
    {
        if (a == Result::Success || b == Result::Success)
        {
            return Result::Success;
        }
        return Result::Failure;
    }

    /// Return true when both a and b are Success.
    bool operator&&(const Result& a, const Result& b)
    {
        return (a == Result::Success && b == Result::Success);
    }

    /// Return true when any of a and b is Success.
    bool operator||(const Result& a, const Result& b)
    {
        return (a == Result::Success || b == Result::Success);
    }
}