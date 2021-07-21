#include "Behavior.hpp"

#include <GaiaExceptions/GaiaExceptions.hpp>
#include <tbb/tbb.h>

namespace Gaia::BehaviorTree
{
    /// Initialize this behavior and its sub behaviors.
    void Behavior::Initialize()
    {
        if (!ContextBlackboard)
        {
            ContextBlackboard = std::make_shared<Blackboards::Blackboard>();
            OwnedContextBlackboard = true;
        }
        OnInitialize();

        for (auto& sub_behavior : GetSubBehaviors())
        {
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

        for (auto& sub_behavior : GetSubBehaviors())
        {
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

    /// Remove the given sub behavior.
    void Behavior::RemoveSubBehavior(Behavior *behavior)
    {
        auto finder = SubBehaviors.begin();
        while (finder != SubBehaviors.end())
        {
            if (finder->get() != behavior)
            {
                ++finder;
                continue;
            }
            else
            {
                finder->get()->Finalize();
                finder = SubBehaviors.erase(finder);
            }
        }
    }

    /// Clear all sub behaviors.
    void Behavior::ClearSubBehavior()
    {
        tbb::parallel_for_each(SubBehaviors, [](std::unique_ptr<Behavior>& behavior)
        {
           behavior->Finalize();
        });
        SubBehaviors.clear();
    }
}