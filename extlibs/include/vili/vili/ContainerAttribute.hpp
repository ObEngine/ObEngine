#pragma once

#include "Attribute.hpp"

namespace vili
{
    //ContainerAttribute
    class ContainerAttribute : public Attribute
    {
    public:
        const static Types::AttributeType ClassType = Types::ContainerAttribute;
        ContainerAttribute(ContainerAttribute* parent, const std::string& id, const Types::AttributeType& type);
        virtual Attribute* removeOwnership(Attribute* element);

        virtual ~ContainerAttribute()
        {
        }

        virtual Attribute* extractElement(Attribute* element) = 0;
        void copy(ContainerAttribute* newParent, const std::string& newid = "") const override = 0;
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override = 0;
    };
}
