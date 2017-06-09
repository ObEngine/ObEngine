#include "vili/DataTemplate.hpp"

namespace vili
{
    AttributeConstraintManager::AttributeConstraintManager(ComplexAttribute* parent, std::string path) : m_attribute(parent, "link", path)
    {
    }

    void AttributeConstraintManager::addConstraint(std::function<bool(BaseAttribute*)> constraint)
    {
        m_constraints.push_back(constraint);
    }

    bool AttributeConstraintManager::checkAllConstraints()
    {
        for (std::function<bool(BaseAttribute*)>& constraint : m_constraints)
        {
            if (!constraint(m_attribute.get<BaseAttribute*>()))
                return false;
        }
        if (m_attribute.get<BaseAttribute*>()->getAnnotation() != "Set")
            return false;
        m_attribute.get<BaseAttribute*>()->setAnnotation("UnSet");
        return true;
    }

    LinkAttribute* AttributeConstraintManager::getLinkAttribute()
    {
        return &m_attribute;
    }

    std::string AttributeConstraintManager::getArgumentPath() const
    {
        return m_attribute.getFullPath();
    }

    DataTemplate::DataTemplate(const std::string& name) : m_body("root")
    {
        m_name = name;
    }

    ComplexAttribute* DataTemplate::getBody()
    {
        return &m_body;
    }

    void DataTemplate::build(ComplexAttribute* parent, const std::string& id)
    {
        if (checkSignature())
        {
            m_body.at("__body__").copy(parent, id);
            std::vector<LinkAttribute*> attributeAddresses;
            for (AttributeConstraintManager& constraintManager : m_signature)
                attributeAddresses.push_back(constraintManager.getLinkAttribute());
            parent->getComplexAttribute(id).walk([attributeAddresses](NodeIterator& complex)
            {
                for (int i = 0; i < complex->getAll(Types::LinkAttribute).size(); i++)
                {
                    std::cout << complex->getAll(Types::LinkAttribute)[i] << std::endl;
                }
                for (int i = 0; i < complex->getAll(Types::LinkAttribute).size(); i++)
                {
                    for (int j = 0; j < attributeAddresses.size(); j++)
                    {
                        if (complex->getLinkAttribute(complex->getAll(Types::LinkAttribute)[i]) == (*attributeAddresses[j]))
                            complex->getLinkAttribute(complex->getAll(Types::LinkAttribute)[i]).apply();
                    }
                }
            });
            if (m_defaultLinkRoot)
                parent->at(id).deleteBaseAttribute("__linkroot__");
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataTemplate.BuildError", {{"element", id},{"parent", parent->getNodePath()}});
    }

    bool DataTemplate::checkSignature()
    {
        for (AttributeConstraintManager& constraintManager : m_signature)
        {
            if (!constraintManager.checkAllConstraints())
                return false;
        }
        return true;
    }

    void DataTemplate::addConstraintManager(const AttributeConstraintManager& constraintManager, bool facultative)
    {
        if (facultative)
        {
            m_signatureEnd = true;
            m_signature.push_back(constraintManager);
        }
        else if (!facultative && !m_signatureEnd)
            m_signature.push_back(constraintManager);
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataTemplate.WrongFacultativeParameterOrder", {{"index", std::to_string(m_signature.size())}});
    }

    void DataTemplate::useDefaultLinkRoot()
    {
        m_defaultLinkRoot = true;
    }

    unsigned int DataTemplate::getArgumentCount() const
    {
        return m_signature.size();
    }

    std::string DataTemplate::getName() const
    {
        return m_name;
    }

    void DataTemplate::setVisible(bool visible)
    {
        m_visible = visible;
    }

    bool DataTemplate::isVisible()
    {
        return m_visible;
    }
}
