#pragma once

#include <string>

#include "Types.hpp"

namespace vili
{
    class ContainerAttribute;

    class Attribute
    {
    protected:
        std::string m_id;
        Types::AttributeType m_type = Types::Attribute;
        std::string m_annotation = "";
        ContainerAttribute* m_parent = nullptr;
        bool m_visible = true;
        virtual void removeParent(ContainerAttribute* currentParent);
        virtual ContainerAttribute* getParent() const;
        friend class ContainerAttribute;
        friend class LinkAttribute;
        friend void LoadErrors(const std::string& errorFile);
    public:
        const static Types::AttributeType ClassType = Types::Attribute;
        Attribute(ContainerAttribute* parent, const std::string& id, const Types::AttributeType& type);

        virtual ~Attribute()
        {
        }

        virtual void setAnnotation(const std::string& annotation);
        virtual std::string getAnnotation() const;
        virtual std::string getID() const;
        virtual Types::AttributeType getType() const;
        virtual void setParent(ContainerAttribute* parent);
        virtual std::string getNodePath() const;
        unsigned int getDepth() const;
        bool isVisible() const;
        void setVisible(bool visible);
        virtual void setID(const std::string& id);
        virtual void copy(ContainerAttribute* newParent, const std::string& newid = "") const = 0;
        virtual void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const = 0;
    };
}
