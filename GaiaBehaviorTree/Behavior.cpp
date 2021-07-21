#include "Behavior.hpp"

#include <GaiaExceptions/GaiaExceptions.hpp>

namespace Gaia::BehaviorTree
{
    /// Constructor with reflection.
    Behavior::Behavior(Behavior *parent_behavior) :
        Reflection::ReflectedElement(parent_behavior, "Behavior")
    {}

    /// Reflect this behavior with additional reflected type names.
    Behavior::Behavior(Behavior *parent_behavior, const std::unordered_set<std::string>& type_names) :
        Reflection::ReflectedElement(parent_behavior, type_names)
    {}

    /// Initialize this behavior and its sub behaviors.
    void Behavior::Initialize()
    {
        if (!ContextBlackboard)
        {
            ContextBlackboard = std::make_shared<Blackboards::Blackboard>();
            OwnedContextBlackboard = true;
        }
        OnInitialize();

        for (auto* sub_element : GetReflectedElements())
        {
            auto* sub_behavior = dynamic_cast<Behavior*>(sub_element);
            // Pass blackboard to sub behaviors.
            sub_behavior->ContextBlackboard = ContextBlackboard;
            sub_behavior->OwnedContextBlackboard = false;
            sub_behavior->Initialize();
        }
    }

    /// Finalize this behavior and its sub behaviors.
    void Behavior::Finalize()
    {
        OnFinalize();

        for (auto* sub_element : GetReflectedElements("Behavior"))
        {
            auto* sub_behavior = dynamic_cast<Behavior*>(sub_element);
            sub_behavior->Finalize();
        }

        if (OwnedContextBlackboard)
            ContextBlackboard->Clear();
    }

    /// Execute this behavior.
    Result Behavior::Execute()
    {
        if (!ContextBlackboard)
            throw Exceptions::NullPointerException("Context Blackboard",
                                                   "This behavior has not been properly initialized.");
        return OnExecute();
    }
}