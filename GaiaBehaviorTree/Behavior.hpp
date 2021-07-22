#pragma once

#include <GaiaReflection/GaiaReflection.hpp>
#include <GaiaBlackboards/GaiaBlackboards.hpp>
#include <memory>

#include "Result.hpp"

namespace Gaia::BehaviorTree
{
    /**
     * @brief Behavior can be declared in other behaviors and have their own sub behaviors.
     */
    class Behavior : public Reflection::ReflectedContainer, public Reflection::ReflectedElement
    {
    private:
        /**
         * @brief Blackboard for variables accessing.
         * @details
         *  It will be initialized as a new blackboard if it is null when this behavior is initializing,
         *  and it will be passed to sub behaviors of this behavior.
         */
        std::shared_ptr<Blackboards::Blackboard> ContextBlackboard {nullptr};
        /// Whether the context blackboard is constructed and owned by this behavior.
        bool OwnedContextBlackboard {false};

    public:
        /// None reflection constructor.
        Behavior() = default;
        /// Reflection constructor when this behavior is added to another behavior.
        explicit Behavior(Behavior* parent_behavior);
        /**
         * @brief Reflect this behavior with additional reflected type names.
         * @param type_names Additional type names along side with "Behavior".
         * @param parent_behavior Parent behavior to register.
         */
        Behavior(Behavior *parent_behavior, const std::unordered_set<std::string>& type_names);

    protected:
        /// Invoked when this behavior is initialized.
        virtual void OnInitialize() {};
        /// Invoked when this behavior is finalized.
        virtual void OnFinalize() {};
        /// Invoked when this behavior is executed.
        virtual Result OnExecute() = 0;

    public:
        /// Get the blackboard of this behavior.
        [[nodiscard]] inline Blackboards::Blackboard* GetBlackboard() const noexcept
        {
            return ContextBlackboard.get();
        }

        /// Initialize this behavior and its sub behaviors.
        void Initialize();
        /// Finalize this behavior and its sub behaviors.
        void Finalize();
        /// Execute this behavior.
        Result Execute();
    };
};

#ifndef BEHAVIOR_MACRO
#define BEHAVIOR_MACRO
/// Allow this behavior to be auto reflected sub behaviors.
#define REFLECT_TYPE(Namespace, InterfaceType) \
    public: using Namespace::InterfaceType::InterfaceType;

#define EXTEND_CONSTRUCTOR(Arguments...) (Gaia::BehaviorTree::Behavior* parent, ##Arguments) : \
    Gaia::BehaviorTree::Behavior(parent),

#define EXTEND_NAME_CONSTRUCTOR(Arguments...) \
    (Gaia::BehaviorTree::Behavior* parent, const std::string &type_name, ##Arguments) : \
    Gaia::BehaviorTree::Behavior(parent, type_name),

#define EXTEND_NAMES_CONSTRUCTOR(Arguments...) \
    (Gaia::BehaviorTree::Behavior* parent, std::unordered_set<std::string> names, ##Arguments) : \
    Gaia::BehaviorTree::Behavior(parent, names),

/// Individual node
#define BEHAVIOR(BehaviorType, BehaviorName, ConstructorArguments...) \
    BehaviorType BehaviorName {this, ##ConstructorArguments};
/// Node content description begins.
#define BEHAVIOR_BEGIN(NodeType, NodeName) \
    class Reflected##NodeName : public NodeType \
    { \
    public: \
        template <typename... Arguments> \
        explicit Reflected##NodeName(Gaia::BehaviorTree::Behavior* parent, \
            Arguments... arguments) : \
            NodeType(parent, arguments...) \
        {} \
        inline void OnInitialize() override { \
            NodeType::OnInitialize();} \
        inline void OnFinalize() override { \
            NodeType::OnFinalize();} \
        inline Gaia::BehaviorTree::Result OnExecute() override { \
            return NodeType::OnExecute();}
/// Node content description ends.
#define BEHAVIOR_END(NodeName, ConstructorArguments...) \
    } NodeName {this, ##ConstructorArguments};
#endif