#include "vili/Attribute.hpp"
#include "vili/ContainerAttribute.hpp"
#include "ErrorHandler.hpp"
#include "Functions.hpp"

namespace vili
{
    Attribute::Attribute(ContainerAttribute* parent, const std::string& id, const Types::AttributeType& type)
    {
        m_id = id;
        m_type = type;
        m_parent = parent;
    }

    void Attribute::removeParent(ContainerAttribute* currentParent)
    {
        if (m_parent == currentParent || m_parent == nullptr)
            m_parent = nullptr;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.Attribute.WrongParentRemover", {
                                                {"wrongparent", currentParent->getNodePath()},
                                                {"path", getNodePath()}
                                            });
    }

    void Attribute::setAnnotation(const std::string& annotation)
    {
        m_annotation = annotation;
    }

    std::string Attribute::getAnnotation() const
    {
        return m_annotation;
    }

    std::string Attribute::getID() const
    {
        return m_id;
    }

    Types::AttributeType Attribute::getType() const
    {
        return m_type;
    }

    ContainerAttribute* Attribute::getParent() const
    {
        return m_parent;
    }

    void Attribute::setParent(ContainerAttribute* parent)
    {
        if (m_parent == nullptr)
            m_parent = parent;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.Attribute.AlreadyHaveParent", {{"path", getNodePath()},{"parent", parent->getNodePath()}});
    }

    std::string Attribute::getNodePath() const
    {
        std::vector<std::string> parentChain;
        ContainerAttribute* currentParent = this->getParent();
        while (currentParent != nullptr)
        {
            parentChain.push_back(currentParent->getID() +
                (!currentParent->getAnnotation().empty() ? "<" + currentParent->getAnnotation() + ">" : ""));
            currentParent = currentParent->getParent();
        }
        reverse(parentChain.begin(), parentChain.end());
        parentChain.push_back(this->getID() + (!this->getAnnotation().empty() ? "<" + this->getAnnotation() + ">" : ""));
        return Functions::Vector::join(parentChain, "/");
    }

    unsigned int Attribute::getDepth() const
    {
        ContainerAttribute* currentParent = this->getParent();
        unsigned int depth = 0;
        while (currentParent != nullptr)
        {
            currentParent = currentParent->getParent();
            depth++;
        }
        return depth;
    }

    bool Attribute::isVisible() const
    {
        return m_visible;
    }

    void Attribute::setVisible(bool visible)
    {
        m_visible = visible;
    }

    void Attribute::setID(const std::string& id)
    {
        if (m_parent == nullptr)
            m_id = id;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.Attribute.ChangeIDWithParent", {{"path", getNodePath()}});
    }
}
