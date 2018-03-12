#include <ContainerNode.hpp>
#include <ErrorHandler.hpp>
#include <Functions.hpp>
#include <Node.hpp>

namespace vili
{
    Node::Node(ContainerNode* parent, const std::string& id, const NodeType& type)
    {
        m_id = id;
        m_type = type;
        m_parent = parent;
    }

    Node::Node(const Node& copy)
    {
        m_id = copy.m_id;
        m_type = copy.m_type;
        m_annotation = copy.m_annotation;
        m_parent = copy.m_parent;
        m_visible = copy.m_visible;
    }

    void Node::removeParent(ContainerNode* currentParent)
    {
        if (m_parent == currentParent || m_parent == nullptr)
            m_parent = nullptr;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.Node.WrongParentRemover", {
                {"wrongparent", currentParent->getNodePath()},
                {"path", getNodePath()}
            });
    }

    void Node::setAnnotation(const std::string& annotation)
    {
        m_annotation = annotation;
    }

    std::string Node::getAnnotation() const
    {
        return m_annotation;
    }

    std::string Node::getId() const
    {
        return m_id;
    }

    NodeType Node::getType() const
    {
        return m_type;
    }

    ContainerNode* Node::getParent() const
    {
        return m_parent;
    }

    void Node::setParent(ContainerNode* parent)
    {
        if (m_parent == nullptr)
            m_parent = parent;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.Node.AlreadyHaveParent", {{"path", getNodePath()},{"parent", parent->getNodePath()}});
    }

    std::string Node::getNodePath() const
    {
        std::vector<std::string> parentChain;
        ContainerNode* currentParent = this->getParent();
        while (currentParent != nullptr)
        {
            parentChain.push_back(currentParent->getId() +
                (!currentParent->getAnnotation().empty() ? "<" + currentParent->getAnnotation() + ">" : ""));
            currentParent = currentParent->getParent();
        }
        reverse(parentChain.begin(), parentChain.end());
        parentChain.push_back(this->getId() + (!this->getAnnotation().empty() ? "<" + this->getAnnotation() + ">" : ""));
        return Functions::Vector::join(parentChain, "/");
    }

    std::string Node::getRawNodePath() const
    {
        std::vector<std::string> parentChain;
        ContainerNode* currentParent = this->getParent();
        while (currentParent != nullptr)
        {
            parentChain.push_back(currentParent->getId());
            currentParent = currentParent->getParent();
        }
        reverse(parentChain.begin(), parentChain.end());
        parentChain.push_back(this->getId());
        return Functions::Vector::join(parentChain, "/");
    }

    unsigned int Node::getDepth() const
    {
        ContainerNode* currentParent = this->getParent();
        unsigned int depth = 0;
        while (currentParent != nullptr)
        {
            currentParent = currentParent->getParent();
            depth++;
        }
        return depth;
    }

    bool Node::isVisible() const
    {
        return m_visible;
    }

    void Node::setVisible(bool visible)
    {
        m_visible = visible;
    }

    void Node::setId(const std::string& id)
    {
        if (m_parent == nullptr)
            m_id = id;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.Node.ChangeIDWithParent", {{"path", getNodePath()}});
    }
}
