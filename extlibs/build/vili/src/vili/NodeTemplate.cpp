#include "vili/NodeTemplate.hpp"

namespace vili
{
    NodeConstraintManager::NodeConstraintManager(ComplexNode* parent, const std::string& path) : m_attribute(parent, "link", path)
    {
    }

    void NodeConstraintManager::addConstraint(std::function<bool(DataNode*)> constraint)
    {
        m_constraints.push_back(constraint);
    }

    bool NodeConstraintManager::checkAllConstraints()
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

    LinkNode* NodeConstraintManager::getLinkNode()
    {
        return &m_attribute;
    }

    std::string NodeConstraintManager::getArgumentPath() const
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
            for (NodeConstraintManager& constraintManager : m_signature)
                attributeAddresses.push_back(constraintManager.getLinkNode());
            parent->getComplexNode(id).walk([attributeAddresses](NodeIterator& complex)
            {
                for (int i = 0; i < complex->getAll(NodeType::LinkNode).size(); i++)
                {
                    for (int j = 0; j < attributeAddresses.size(); j++)
                    {
                        if (complex->getLinkNode(complex->getAll(NodeType::LinkNode)[i]) == (*attributeAddresses[j]))
                            complex->getLinkNode(complex->getAll(NodeType::LinkNode)[i]).apply();
                    }
                }
            });
            if (m_defaultLinkRoot)
                parent->at(id).removeNode(NodeType::DataNode, "__linkroot__");
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.NodeTemplate.BuildError", {{"element", id},{"parent", parent->getNodePath()}});
    }

    bool NodeTemplate::checkSignature()
    {
        for (NodeConstraintManager& constraintManager : m_signature)
        {
            if (!constraintManager.checkAllConstraints())
                return false;
        }
        return true;
    }

    void NodeTemplate::addConstraintManager(const NodeConstraintManager& constraintManager, bool facultative)
    {
        if (facultative)
        {
            m_signatureEnd = true;
            m_signature.push_back(constraintManager);
        }
        else if (!facultative && !m_signatureEnd)
            m_signature.push_back(constraintManager);
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.NodeTemplate.WrongFacultativeParameterOrder", {{"index", std::to_string(m_signature.size())}});
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

    bool NodeTemplate::isVisible() const
    {
        return m_visible;
    }
}
