#include "Reflector.hpp"

#include <boost/property_tree/xml_parser.hpp>

namespace Gaia::BehaviorTree
{
    /// Construct a new behavior.
    std::unique_ptr<Behavior> BehaviorTree::Reflector::NewBehavior(const std::string &behavior_name)
    {
        auto finder = Behavior::GetDerivedClasses().find(behavior_name);
        if (finder != Behavior::GetDerivedClasses().end())
        {
            if (finder->second) return std::unique_ptr<Behavior>(finder->second());
        }
        return nullptr;
    }

    /// Deserialize a behavior tree from a XML document.
    std::unique_ptr<Behavior> Reflector::DeserializeXML(const std::string &xml_path)
    {
        boost::property_tree::ptree root;
        boost::property_tree::read_xml(xml_path, root);

        auto behavior_pointer = Reflector::NewBehavior(root.begin()->first);
        if (!behavior_pointer) throw std::runtime_error("No reflected behavior named" + root.begin()->first);
        behavior_pointer->Deserialize(root.begin()->second);

        return behavior_pointer;
    }
}