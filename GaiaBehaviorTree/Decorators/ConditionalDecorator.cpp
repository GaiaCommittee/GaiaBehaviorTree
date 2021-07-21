#include "ConditionalDecorator.hpp"
#include "../Reflector.hpp"

namespace Gaia::BehaviorTree::Decorators
{

    void ConditionalDecorator::Deserialize(const boost::property_tree::ptree &root_node)
    {
        auto condition_class = root_node.get<std::string>("<xmlattr>.Condition");
        auto condition_pointer = Reflector::NewBehavior(condition_class);
        if (!condition_pointer) throw std::runtime_error("No reflected behavior named " + condition_class);

        auto* condition = AddSubBehavior(std::move(condition_pointer));
        ConditionBehavior = condition;
        condition->Deserialize(root_node);

        return Decorator::Deserialize(root_node);
    }
}