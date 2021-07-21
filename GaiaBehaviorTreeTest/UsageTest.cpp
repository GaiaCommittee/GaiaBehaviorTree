#include "../GaiaBehaviorTree/GaiaBehaviorTree.hpp"
#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <utility>

using namespace Gaia::BehaviorTree;

class OutputMessage : public Behavior
{
    REFLECT_TYPE(Gaia::BehaviorTree, Behavior)
protected:
    std::string Message;

public:
    OutputMessage EXTEND_CONSTRUCTOR(std::string message)
        Message(std::move(message))
    {}

protected:
    Result OnExecute() override
    {
        std::cout << Message << std::endl;
        return Result::Success;
    }
};

class TestCondition : public Behavior
{
    REFLECT_TYPE(Gaia::BehaviorTree, Behavior)
protected:
    Result OnExecute() override
    {
        return Result::Failure;
    }
};

class TestBehavior : public Containers::Sequence
{
public:
    BEHAVIOR(OutputMessage, message1, "Message 1.")
    BEHAVIOR(OutputMessage, message2, "Message 2.")
    DECORATOR_BEGIN(Decorators::If, switch1)
        CONDITION(TestCondition, condition)
        BEHAVIOR(OutputMessage, message3, "Condition satisfied.")
    DECORATOR_END(switch1)
};

TEST(UsageTest, BasicComposition)
{
    TestBehavior test_behavior;
    test_behavior.Initialize();
    test_behavior.Execute();
    test_behavior.Finalize();
}