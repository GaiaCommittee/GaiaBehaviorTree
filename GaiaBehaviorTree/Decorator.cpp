#include "Decorator.hpp"
#include "Reflector.hpp"

#include <stdexcept>

namespace Gaia::BehaviorTree
{
    /// Deserialize the decorated node.
    void Decorator::Deserialize(const boost::property_tree::ptree &root_node)
    {
        auto decorated_class = root_node.begin()->first;
        auto decorated_pointer = Reflector::NewBehavior(decorated_class);
        if (!decorated_pointer) throw std::runtime_error("No reflected behavior named " + decorated_class);
        auto* decorated = AddSubBehavior(std::move(decorated_pointer));
        DecoratedBehavior = decorated;
        decorated->Deserialize(root_node.begin()->second);
    }
}