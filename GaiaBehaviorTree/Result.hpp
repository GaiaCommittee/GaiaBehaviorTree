#pragma once

namespace Gaia::BehaviorTree
{
    /// The result of the execution.
    enum class Result
    {
        Success,
        Failure
    };

    /**
     * @brief Get the reverse value of the given result.
     * @param target The result to get the reversed value.
     * @retval Success if target is Failure.
     * @retval Failure if target is Success.
     */
    Result operator!(const Result& target);

    /// Return Success when both a and b are Success.
    Result operator&(const Result& a, const Result& b);
    /// Return Success when any of a and b is Success.
    Result operator|(const Result& a, const Result& b);

    /// Return true when both a and b are Success.
    bool operator&&(const Result& a, const Result& b);
    /// Return true when any of a and b is Success.
    bool operator||(const Result& a, const Result& b);
}