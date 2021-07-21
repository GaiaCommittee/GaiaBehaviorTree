#pragma once

#include "Behavior.hpp"
#include "Container.hpp"
#include "Decorator.hpp"
#include <boost/property_tree/ptree.hpp>
#include <memory>

namespace Gaia::BehaviorTree
{
    /**
     * @brief Reflector can construct behaviors, containers, or decorators according their class names.
     * @attention Memory of all objects constructed here will not be managed by this reflector.
     */
    class Reflector
    {
    public:
        /**
         * @brief Construct a new behavior.
         * @param behavior_name Reflection name of the behavior class.
         * @return Raw pointer to the new behavior.
         */
        static std::unique_ptr<Behavior> NewBehavior(const std::string& behavior_name);

        /// Deserialize a behavior tree from a XML document.
        static std::unique_ptr<Behavior> DeserializeXML(const std::string& xml_path);
    };
}