#include "vili/NodeTemplate.hpp"

namespace vili
{
    AttributeConstraintManager::AttributeConstraintManager(ComplexNode* parent, std::string path) : m_attribute(parent, "link", path)
    {
    }

    void AttributeConstraintManager::addConstraint(std::function<bool(DataNode*)> constraint)
    {
        m_constraints.push_back(constraint);
    }

    bool AttributeConstraintManager::checkAllConstraints()
    {
        for (std::function<bool(DataNode*)>& constraint : m_constraints)
        {
            if (!constraint(m_attribute.get<DataNode*>()))
                return false;
        }
        if (m_attribute.get<DataNode*>()->getAnnotation() != "Set")
            return false;
        m_attribute.get<DataNode*>()->setAnnotation("UnSet");
        return true;
    }

    LinkNode* AttributeConstraintManager::getLinkAttribute()
    {
        return &m_attribute;
    }

    std::string AttributeConstraintManager::getArgumentPath() const
    {
        return m_attribute.getFullPath();
    }

    NodeTemplate::NodeTemplate(const std::string& name) : m_body("root")
    {
        m_name = name;
    }

    ComplexNode* NodeTemplate::getBody()
    {
        return &m_body;
    }

    void NodeTemplate::build(ComplexNode* parent, const std::string& id)
    {
        if (checkSignature())
        {
            m_body.at("__body__").copy(parent, id);
            std::vector<LinkNode*> attributeAddresses;
            for (AttributeConstraintManager& constraintManager : m_signature)
                attributeAddresses.push_back(constraintManager.getLinkAttribute());
            parent->getComplexAttribute(id).walk([attributeAddresses](NodeIterator& complex)
            {
                for (int i = 0; i < complex->getAll(NodeType::LinkNode).size(); i++)
                {
                    for (int j = 0; j < attributeAddresses.size(); j++)
                    {
                        if (complex->getLinkAttribute(complex->getAll(NodeType::LinkNode)[i]) == (*attributeAddresses[j]))
                            complex->getLinkAttribute(complex->getAll(NodeType::LinkNode)[i]).apply();
                    }
                }
            });
            if (m_defaultLinkRoot)
                parent->at(id).deleteBaseAttribute("__linkroot__");
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataTemplate.BuildError", {{"element", id},{"parent", parent->getNodePath()}});
    }

    bool NodeTemplate::checkSignature()
    {
        for (AttributeConstraintManager& constraintManager : m_signature)
        {
            if (!constraintManager.checkAllConstraints())
                return false;
        }
        return true;
    }

    void NodeTemplate::addConstraintManager(const AttributeConstraintManager& constraintManager, bool facultative)
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

    void NodeTemplate::useDefaultLinkRoot()
    {
        m_defaultLinkRoot = true;
    }

    unsigned int NodeTemplate::getArgumentCount() const
    {
        return m_signature.size();
    }

    std::string NodeTemplate::getName() const
    {
        return m_name;
    }

    void NodeTemplate::setVisible(bool visible)
    {
        m_visible = visible;
    }

    bool NodeTemplate::isVisible()
    {
        return m_visible;
    }
}
