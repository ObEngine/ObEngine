#pragma once

#include <string>

#include "BaseAttribute.hpp"
#include "ComplexAttribute.hpp"
#include "ContainerAttribute.hpp"
#include "ListAttribute.hpp"

namespace vili
{
    class ComplexAttribute;

    class LinkAttribute : public Attribute
    {
    private:
        std::string m_path = "";
    public:
        const static Types::AttributeType ClassType = Types::LinkAttribute;
        LinkAttribute(ComplexAttribute* parent, const std::string& id, const std::string& path);
        Attribute* getTarget();

        template <class T>
        T get()
        {
        }

        std::string getPath() const;
        std::string getFullPath() const;
        void apply();
        bool operator==(const LinkAttribute& compare) const;
        void copy(ContainerAttribute* newParent, const std::string& newid = "") const override;
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override;
    };

    template <>
    inline BaseAttribute* LinkAttribute::get()
    {
        if (getTarget()->getType() == Types::BaseAttribute)
            return static_cast<BaseAttribute*>(getTarget());
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.LinkAttribute.WrongBaseAttributeLink", {{"path", getNodePath()},{"targetpath", m_path}});
    }

    template <>
    inline ComplexAttribute* LinkAttribute::get()
    {
        if (getTarget()->getType() == Types::ComplexAttribute)
            return static_cast<ComplexAttribute*>(getTarget());
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.LinkAttribute.WrongComplexAttributeLink", {{"path", getNodePath()},{"targetpath", m_path}});
    }

    template <>
    inline ListAttribute* LinkAttribute::get()
    {
        if (getTarget()->getType() == Types::ListAttribute)
            return static_cast<ListAttribute*>(getTarget());
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.LinkAttribute.WrongListAttributeLink", {{"path", getNodePath()},{"targetpath", m_path}});
    }
}
