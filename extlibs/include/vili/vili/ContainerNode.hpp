#pragma once

#include "Node.hpp"

namespace vili
{
    /**
     * \brief Abstract base class for ArrayNode and ComplexNode (A ContainerNode can contains other nodes)
     * @Bind
     */
    class ContainerNode : public Node
    {
    public:
        /**
         * \brief Redefines the ClassType to ContainerNode (Abstract Class)
         */
        const static NodeType ClassType = NodeType::ContainerNode;
        /**
         * \brief Creates a new ContainerNode (Abstract Class)
         * \param parent Parent of the ContainedNode
         * \param id Id of the ContainerNode
         * \param type 
         */
        ContainerNode(ContainerNode* parent, const std::string& id, const NodeType& type);
        /**
         * \brief Removes ownership of a contained child (The child will still be in the ContainerNode but will think it doesn't have a parent)
         * \param element Element to remove the ownership
         * \return A Pointer to the given Node
         */
        virtual Node* removeOwnership(Node* element);

        ContainerNode(const ContainerNode& copy);

        ~ContainerNode() override;

        /**
         * \brief Removes ownership and child Node from ContainerNode (Node won't be memory managed anymore, be cautious)
         * \param element Element to free from its parent
         * \return Pointer to the child Node
         */
        virtual Node* extractElement(Node* element) = 0;
        /**
        * \brief Copies the ContainerNode into a new ContainerNode (Abstract method, must be implemented by derived nodes)
        * \param newParent Parent of the new copied Node
        * \param newid Id to set to the newly created Node
        */
        void copy(ContainerNode* newParent, const std::string& newid = "") const override = 0;
        /**
        * \brief Writes the ContainerNode to a file (Abstract method, must be implemented by derived nodes)
        * \param file File (std::ofstream) where to write the Node
        * \param spacing Default indentation of the file
        * \param depth Depth of the Node to write
        */
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override = 0;
    };
}
