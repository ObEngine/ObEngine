#pragma once

#include <string>

#include <Types.hpp>

namespace vili
{
    class ContainerNode;

    /**
     * \brief Base Class for every Node in the Tree
     */
    class Node
    {
    protected:
        std::string m_id;
        NodeType m_type = NodeType::Node;
        std::string m_annotation = "";
        ContainerNode* m_parent = nullptr;
        bool m_visible = true;
        virtual void removeParent(ContainerNode* currentParent);
        friend class ContainerNode;
        friend class LinkNode;
    public:
        /**
         * \brief ClassType is redefined for every derived class
         */
        const static NodeType ClassType = NodeType::Node;
        /**
         * \brief Creates a new vili Node
         * \param parent Parent node in the tree
         * \param id Id of the Node
         * \param type Type of the Node (Overrides default ClassType)
         */
        Node(ContainerNode* parent, const std::string& id, const NodeType& type);

        Node(const Node& copy);

        /**
         * \brief Virtual Destructor for proper memory management
         */
        virtual ~Node()
        {
        }

        ContainerNode* getParent() const;

        /**
         * \brief Sets the Node annotation (Little Node description displayed when calling Node::getNodePath())
         * \param annotation New Annotation to set
         */
        virtual void setAnnotation(const std::string& annotation);
        /**
         * \brief Gets the Node annotation
         * \return A std::string that contains the Node annotation
         */
        virtual std::string getAnnotation() const;
        /**
         * \brief Gets the id of the Node
         * \return A std::string containing the id of the Node
         */
        virtual std::string getId() const;
        /**
         * \brief Returns the ClassType of the Node (All Types in vili::NodeType)
         * \return An NodeType enum value defining the NodeType of the Node
         */
        virtual NodeType getType() const;
        /**
         * \brief Sets the new parent of the Node (Raises error if the Node already has a parent)
         * \param parent Pointer to the parent Node
         */
        virtual void setParent(ContainerNode* parent);
        /**
         * \brief Get the Node Path (Example : GrandParent/Parent/Node)
         * \return A std::string that contains the NodePath of the Node
         */
        virtual std::string getNodePath() const;
        /**
         * \brief Get the Node Path (Example : GrandParent/Parent/Node) without annotations
         * \return A std::string that contains the NodePath of the Node
         */
        virtual std::string getRawNodePath() const;
        /**
         * \brief Get the depth of the Node (While the parent of the Node has a parent etc..) A Node without parent has depth = 0
         * \return An int containing the depth of the Node
         */
        unsigned int getDepth() const;
        /**
         * \brief Gets if the Node is visible or not (Visible means it exists in the dumped file)
         * \return true if the Node is visible, false otherwise
         */
        bool isVisible() const;
        /**
         * \brief Sets if the Node should be visible or not (Visible means it exists in the dumped file)
         * \param visible If equals to true the Node will be visible, if equals to false it won't
         */
        void setVisible(bool visible);
        /**
         * \brief Sets the new id of the Node (can't be changed if the Node has a parent)
         * \param id New id of the Node
         */
        virtual void setId(const std::string& id);
        /**
         * \brief Copies the Node into a new ContainerNode (Abstract method, must be implemented by derived nodes)
         * \param newParent Parent of the new copied Node
         * \param newid Id to set to the newly created Node
         */
        virtual void copy(ContainerNode* newParent, const std::string& newid = "") const = 0;
        /**
         * \brief Writes the Node to a file (Abstract method, must be implemented by derived nodes)
         * \param file File (std::ofstream) where to write the Node
         * \param spacing Default indentation of the file
         * \param depth Depth of the Node to write
         */
        virtual void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const = 0;
    };
}
