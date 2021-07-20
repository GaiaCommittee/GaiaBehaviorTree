#include "Behavior.hpp"

#include <GaiaExceptions/GaiaExceptions.hpp>

namespace Gaia::BehaviorTree
{
    /// Add an element into the set and return it.
    std::unordered_set<std::string> AddElement(std::unordered_set<std::string>&& elements, const std::string& name)
    {
        elements.emplace(name);
        return elements;
    }

    /// Constructor with reflection.
    Behavior::Behavior(Behavior *parent_behavior) :
        Reflection::ReflectedElement("Behavior", parent_behavior)
    {}

    /// Reflect this behavior with an additional reflected type name.
    Behavior::Behavior(const std::string &type_name, Behavior *parent_behavior) :
        Reflection::ReflectedElement({type_name, "Behavior"}, parent_behavior)
    {}

    /// Reflect this behavior with additional reflected type names.
    Behavior::Behavior(std::unordered_set<std::string> type_names, Behavior *parent_behavior) :
        Reflection::ReflectedElement(AddElement(std::move(type_names), "Behavior"), parent_behavior)
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

        for (auto* sub_element : GetReflectedElements("Behavior"))
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