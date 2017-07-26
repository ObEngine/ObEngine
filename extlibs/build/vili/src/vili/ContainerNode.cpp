#include "vili/ContainerNode.hpp"

namespace vili
{
    ContainerNode::ContainerNode(ContainerNode* parent, const std::string& id, const NodeType& type) : Node(parent, id, type)
    {
    }

    Node* ContainerNode::removeOwnership(Node* element)
    {
        element->removeParent(this);
        return element;
    }
}
