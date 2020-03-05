#pragma once

#include <string>

#include <ArrayNode.hpp>
#include <ComplexNode.hpp>
#include <ContainerNode.hpp>
#include <DataNode.hpp>

namespace vili
{
    class ComplexNode;

    /**
     * \brief A Node that is linked to another one in the Tree
     */
    class LinkNode : public Node
    {
    private:
        std::string m_path = "";
    public:
        /**
         * \brief Redefines the ClassType to NodeType::LinkNode
         */
        const static NodeType ClassType = NodeType::LinkNode;
        /**
         * \brief Creates a new LinkNode
         * \param parent ComplexNode parent where the LinkNode is contained
         * \param id Id of the LinkNode
         * \param path Path of the Node the LinkNode is pointing to
         */
        LinkNode(ComplexNode* parent, const std::string& id, const std::string& path);
        ~LinkNode() override;
        LinkNode(const LinkNode& copy);
        /**
         * \brief Get the Node the LinkNode is pointing to
         * \return A pointer to the Node the LinkNode is pointing to
         */
        Node* getTarget();

        /**
         * \brief Gets the Node the LinkNode is pointing to and casts it
         * \tparam T Type of the Node you want to cast the pointed Node to
         * \return The casted pointed Node
         */
        template <class T>
        T get()
        {
        }

        /**
         * \brief Gets the path of the pointed Node
         * \return A std::string containing the path to the pointed Node
         */
        std::string getPath() const;
        /**
         * \brief Gets the path of the pointed Node (Without using __linkroot__)
         * \return A std::string containing the path to the pointed Node
         */
        std::string getFullPath() const;
        /**
         * \brief Transforms the LinkNode to a copy of the pointed Node
         */
        void apply();
        /**
         * \brief Compares if two LinkNode are pointing to the same Node
         * \param compare The other LinkNode to compare
         * \return true if the two LinkNode are pointing to the same Node, false otherwise
         */
        bool operator==(const LinkNode& compare) const;
        /**
        * \brief Copies the LinkNode into a new ContainerNode
        * \param newParent Parent of the new copied LinkNode
        * \param newid Id to set to the newly created LinkNode
        */
        void copy(ContainerNode* newParent, const std::string& newid = "") const override;
        /**
        * \brief Writes the LinkNode to a file
        * \param file File (std::ofstream) where to write the LinkNode
        * \param spacing Default indentation of the file
        * \param depth Depth of the Node to write
        */
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override;
    };

    template <>
    inline DataNode* LinkNode::get()
    {
        if (getTarget()->getType() == NodeType::DataNode)
            return static_cast<DataNode*>(getTarget());
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.LinkNode.WrongBaseAttributeLink", {{"path", getNodePath()},{"targetpath", m_path}});
    }

    template <>
    inline ComplexNode* LinkNode::get()
    {
        if (getTarget()->getType() == NodeType::ComplexNode)
            return static_cast<ComplexNode*>(getTarget());
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.LinkNode.WrongComplexAttributeLink", {{"path", getNodePath()},{"targetpath", m_path}});
    }

    template <>
    inline ArrayNode* LinkNode::get()
    {
        if (getTarget()->getType() == NodeType::ArrayNode)
            return static_cast<ArrayNode*>(getTarget());
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.LinkNode.WrongListAttributeLink", {{"path", getNodePath()},{"targetpath", m_path}});
    }
}
