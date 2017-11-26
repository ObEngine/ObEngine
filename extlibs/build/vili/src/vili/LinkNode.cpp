#include <fstream>

#include "vili/LinkNode.hpp"
#include "Functions.hpp"

namespace vili
{
    LinkNode::LinkNode(ComplexNode* parent, const std::string& id, const std::string& path) : Node(parent, id, NodeType::LinkNode)
    {
        m_path = path;
    }

    LinkNode::~LinkNode()
    {
    }

    LinkNode::LinkNode(const LinkNode& copy) : Node(copy)
    {
        m_path = copy.m_path;
    }

    Node* LinkNode::getTarget()
    {
        std::string linkroot = "";
        ComplexNode* complexParent = dynamic_cast<ComplexNode*>(m_parent);
        if (complexParent->contains(NodeType::DataNode, "__linkroot__"))
            linkroot = complexParent->getDataNode("__linkroot__").get<std::string>();
        ContainerNode* root = this->getParent();
        while (root->getParent() != nullptr)
            root = root->getParent();
        std::string abspath = linkroot + "/" + m_path;
        Node* location = root;
        std::vector<std::string> fullPath = Functions::String::split(abspath, "/");
        for (const std::string& pathPart : fullPath)
        {
            if (location->getType() == NodeType::ComplexNode)
            {
                ComplexNode* complexLocation = static_cast<ComplexNode*>(location);
                if (complexLocation->contains(NodeType::ComplexNode, pathPart))
                    location = &complexLocation->getComplexNode(pathPart);
                else if (complexLocation->contains(NodeType::DataNode, pathPart))
                {
                    location = &complexLocation->getDataNode(pathPart);
                    break;
                }
                else if (complexLocation->contains(NodeType::ArrayNode, pathPart))
                    location = &complexLocation->getArrayNode(pathPart);
                else
                    throw aube::ErrorHandler::Raise("Vili.Vili.LinkNode.WrongLinkPath", {{"path", getNodePath()},{"target", m_path},{"pathpart", pathPart}});
            }
            else if (location->getType() == NodeType::ArrayNode)
            {
                ArrayNode* listLocation = static_cast<ArrayNode*>(location);
                if (Functions::String::isStringInt(pathPart) && stoi(pathPart) < listLocation->size())
                    location = &listLocation->get(stoi(pathPart));
                else
                    throw aube::ErrorHandler::Raise("Vili.Vili.LinkNode.WrongLinkListIndex", {{"path", getNodePath()},{"target", m_path},{"index", pathPart}});
            }
        }
        return location;
    }

    std::string LinkNode::getPath() const
    {
        return m_path;
    }

    std::string LinkNode::getFullPath() const
    {
        std::string linkroot = "";
        ComplexNode* complexParent = dynamic_cast<ComplexNode*>(m_parent);
        if (complexParent->contains(NodeType::DataNode, "__linkroot__"))
            linkroot = complexParent->getDataNode("__linkroot__").get<std::string>();
        return linkroot + "/" + m_path;
    }

    void LinkNode::apply()
    {
        ComplexNode* complexParent = dynamic_cast<ComplexNode*>(m_parent);
        Node* target = this->getTarget();

        complexParent->extractElement(this);

        target->copy(complexParent, m_id);
        delete this;
    }

    bool LinkNode::operator==(const LinkNode& compare) const
    {
        return (this->getFullPath() == compare.getFullPath());
    }

    void LinkNode::copy(ContainerNode* newParent, const std::string& newid) const
    {
        if (newParent->getType() == NodeType::ComplexNode)
            dynamic_cast<ComplexNode*>(newParent)->createLinkNode(newid.empty() ? m_id : newid, m_path);
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.LinkNode.WrongCopyTarget", {{"path", getNodePath()},{"target", newParent->getNodePath()}});
    }

    void LinkNode::write(std::ofstream* file, const std::string& spacing, unsigned int depth) const
    {
        if (m_visible)
        {
            for (unsigned int j = 0; j < depth - 1; j++)
                (*file) << spacing;
            (*file) << m_id << ":&(" << getPath() << ")" << std::endl;
        }
    }
}
