#pragma once

#include "Node.hpp"

namespace vili
{
    //ContainerAttribute
    class ContainerNode : public Node
    {
    public:
        const static NodeType ClassType = NodeType::ContainerNode;
        ContainerNode(ContainerNode* parent, const std::string& id, const NodeType& type);
        virtual Node* removeOwnership(Node* element);

        virtual ~ContainerNode()
        {
        }

        virtual Node* extractElement(Node* element) = 0;
        void copy(ContainerNode* newParent, const std::string& newid = "") const override = 0;
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override = 0;
    };
}
