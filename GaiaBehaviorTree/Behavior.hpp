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

    protected:
        /**
         * @brief Reflect this behavior with an additional reflected type name.
         * @param type_name Additional type name along side with "Behavior".
         * @param parent_behavior Parent behavior to register.
         */
        Behavior(const std::string& type_name, Behavior* parent_behavior);
        /**
         * @brief Reflect this behavior with additional reflected type names.
         * @param type_names Additional type names along side with "Behavior".
         * @param parent_behavior Parent behavior to register.
         */
        Behavior(std::unordered_set<std::string> type_names, Behavior* parent_behavior);

    protected:
        /// Get the blackboard of this behavior.
        [[nodiscard]] inline Blackboards::Blackboard* GetBlackboard() const noexcept
        {
            return ContextBlackboard.get();
        }

        /// Invoked when this behavior is initialized.
        virtual void OnInitialize() {};
        /// Invoked when this behavior is finalized.
        virtual void OnFinalize() {};
        /// Invoked when this behavior is executed.
        virtual Result OnExecute() = 0;

    public:
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
#define BEHAVIOR(BehaviorType, BehaviorName, ...) \
    class Reflected##BehaviorName : public BehaviorType \
    { \
    public: \
        template <typename... ConstructorArguments> \
        explicit Reflected##BehaviorName(Gaia::BehaviorTree::Behavior* parent, \
            ConstructorArguments... arguments) : \
            BehaviorType(parent, arguments...) \
        {} \
        inline void OnInitialize() override { \
            BehaviorType::OnInitialize();} \
        inline void OnFinalize() override { \
            BehaviorType::OnFinalize();} \
        inline Gaia::BehaviorTree::Result OnExecute() override { \
            return BehaviorType::OnExecute();}          \
    } BehaviorName {this, ##__VA_ARGS__};
#define CONTAINER(ContainerType, ContainerName, Body, ...) \
    class Reflected##ContainerName : public ContainerType             \
    {                                                    \
    public:                                              \
        template <typename... ConstructorArguments> \
        explicit Reflected##ContainerName(Gaia::BehaviorTree::Behavior* parent, \
            ConstructorArguments... arguments) : \
            ContainerType(parent, arguments...) \
        {} \
        inline void OnInitialize() override { \
            ContainerType::OnInitialize();} \
        inline void OnFinalize() override { \
            ContainerType::OnFinalize();} \
        inline Gaia::BehaviorTree::Result OnExecute() override { \
            return ContainerType::OnExecute();} \
        Body \
    } ContainerName {this, ##__VA_ARGS__};
#define CONTAINER_BEGIN(ContainerType, ContainerName) \
    class Reflected##ContainerName : public ContainerType \
    { \
    public: \
        template <typename... ConstructorArguments> \
        explicit Reflected##ContainerName(Gaia::BehaviorTree::Behavior* parent, \
            ConstructorArguments... arguments) : \
            ContainerType(parent, arguments...) \
        {} \
        inline void OnInitialize() override { \
            ContainerType::OnInitialize();} \
        inline void OnFinalize() override { \
            ContainerType::OnFinalize();} \
        inline Gaia::BehaviorTree::Result OnExecute() override { \
            return ContainerType::OnExecute();}
#define CONTAINER_END(ContainerName, ...) \
    } ContainerName {this, ##__VA_ARGS__};
#define DECORATOR(DecoratorType, DecoratorName, Body, ...) \
    class Reflected##DecoratorName : public DecoratorType  \
    {                                                      \
    public: \
        template <typename... ConstructorArguments> \
        explicit Reflected##DecoratorName(Gaia::BehaviorTree::Behavior* parent, \
            ConstructorArguments... arguments) : \
            DecoratorType(parent, arguments...) \
        {} \
        inline void OnInitialize() override { \
            DecoratorType::OnInitialize();} \
        inline void OnFinalize() override { \
            DecoratorType::OnFinalize();} \
        inline Gaia::BehaviorTree::Result OnExecute() override { \
            return DecoratorType::OnExecute();} \
        Body \
    } DecoratorName {this, ##__VA_ARGS__};
#define DECORATOR_BEGIN(DecoratorType, DecoratorName) \
    class Reflected##DecoratorName : public DecoratorType \
    { \
    public: \
        template <typename... ConstructorArguments> \
        explicit Reflected##DecoratorName(Gaia::BehaviorTree::Behavior* parent, \
            ConstructorArguments... arguments) : \
            DecoratorType(parent, arguments...) \
        {} \
        inline void OnInitialize() override { \
            DecoratorType::OnInitialize();} \
        inline void OnFinalize() override { \
            DecoratorType::OnFinalize();} \
        inline Gaia::BehaviorTree::Result OnExecute() override { \
            return DecoratorType::OnExecute();}
#define DECORATOR_END(DecoratorName, ...) \
    } DecoratorName {this, ##__VA_ARGS__};
#endif