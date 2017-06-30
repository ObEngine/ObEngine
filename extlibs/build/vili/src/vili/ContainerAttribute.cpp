#include "vili/ContainerAttribute.hpp"

namespace vili
{
    ContainerAttribute::ContainerAttribute(ContainerAttribute* parent, const std::string& id, const AttributeType& type) : Attribute(parent, id, type)
    {
    }

    Attribute* ContainerAttribute::removeOwnership(Attribute* element)
    {
        element->removeParent(this);
        return element;
    }
}
