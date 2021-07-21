#include "Container.hpp"
#include "Reflector.hpp"

#include <stdexcept>

namespace Gaia::BehaviorTree
{
    /// Construct the container from a document tree.
    void Container::Deserialize(const boost::property_tree::ptree &root_node)
    {
        for (auto [node_class, node] : root_node)
        {
            auto behavior_pointer = Reflector::NewBehavior(node_class);
            if (!behavior_pointer) throw std::runtime_error("No reflected behavior named" + node_class);
            auto* behavior = AddSubBehavior(std::move(behavior_pointer));
            behavior->Deserialize(node);
        }
    }
}
