#pragma once

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "DataNode.hpp"
#include "ContainerNode.hpp"
#include "ArrayNode.hpp"
#include "NodeIterator.hpp"
#include "NodeValidator.hpp"

namespace vili
{
    class LinkNode;
    class NodeTemplate;

    /**
     * \brief A ComplexNode can contains every other Nodes (including itself) hence allowing a tree-like structure
     * @Bind
     */
    class ComplexNode : public ContainerNode
    {
    protected:
        std::vector<std::unique_ptr<Node>> m_children;
        std::vector<std::string> m_heritFrom;
        NodeTemplate* m_template = nullptr;
        ComplexNode& getPath(std::string attributePath) const;
        void walk(std::function<void(NodeIterator&)> walkFunction, NodeIterator& iterator);
        template <class T>
        void walk(std::function<void(NodeValidator<T>&)> walkFunction, NodeValidator<T>& iterator);
        std::unique_ptr<Node>& getNodePtr(const std::string& id);
    public:
        /**
         * \brief Redefines ClassType to NodeType::ComplexNode
         */
        const static NodeType ClassType = NodeType::ComplexNode;
        /**
         * \brief Creates new ComplexNode
         * \param parent Parent of the new Complex
         * \param id Id of the newly created ComplexNode
         */
        ComplexNode(ComplexNode* parent, const std::string& id);
        /**
         * \brief Creates an orphan ComplexNode (you monster)
         * \param id Id of the newly created ComplexNode
         */
        ComplexNode(const std::string& id);

        ComplexNode(const ComplexNode& copy);

        ~ComplexNode() override;

        /**
        * \brief Removes ownership and child Node from ComplexNode (Node won't be memory managed anymore, be cautious)
        * \param element Element to free from its parent
        * \return Pointer to the child Node
        */
        Node* extractElement(Node* element) override;
        /**
         * \brief Copies all Nodes from another ComplexNode recursively (All herited Nodes are made non-visible)
         * \param heritTarget ComplexNode to herit from
         */
        void heritage(ComplexNode* heritTarget);
        
        /**
         * \brief Access a ComplexNode child
         * \param id Id of the ComplexNode child 
         * \return A reference to the ComplexNode child
         */
        ComplexNode& operator[](const std::string& id) const;

        /**
        * \brief Access a ComplexNode in the tree using a path with slash-separation (.at("NodeA/NodeB/NodeC") for example)
        * \param path Path of the ComplexNode to access
        * \return A reference to the ComplexNode
        */
        ComplexNode& at(const std::string& path) const;
        /**
        * \brief Access a casted Node in the tree using a path (with multiple path parts) (.at("NodeA", "NodeB", "NodeB") for example)
        * \tparam T Type of the Node used for cast
        * \tparam Args Variadic Template
        * \param cPath Current Path Part if the Variadic Template
        * \param pathParts All other part parts not yet interpreted
        * \return A reference to the casted Node
        */
        template <class T, class ...Args>
        T& at(const std::string& cPath, Args ...pathParts) const;
        /**
        * \brief Access a ComplexNode in the tree using a path (with multiple path parts) (.at("NodeA", "NodeB", "NodeB") for example)
        * \tparam Args Variadic Template
        * \param cPath Current Path Part if the Variadic Template
        * \param pathParts All other part parts not yet interpreted
        * \return A reference to the ComplexNode
        */
        template <class ...Args>
        ComplexNode& at(const std::string& cPath, Args ...pathParts) const;

        /**
        * \brief Access a casted Node in the tree using a path (with multiple path parts) (.at("NodeA", "NodeB", "NodeB") for example)
        * \tparam T Type of the Node used for cast
        * \param id Id of the Node to access
        * \return A reference to the casted Node
        */
        template <class T>
        T& at(const std::string& id) const { return T(); };

        /**
         * \brief Get raw non-casted Node pointer by id
         * \param id Id of the Node to get
         * \return A pointer to the Node
         */
        Node* get(const std::string& id) const;
        /**
         * \brief Get a DataNode contained in the ComplexNode
         * \param id Id of the Node to get
         * \return A pointer to the DataNode
         */
        DataNode& getDataNode(const std::string& id) const;
        /**
        * \brief Get a ComplexNode contained in the ComplexNode
        * \param id Id of the Node to get
        * \return A pointer to the ComplexNode
        */
        ComplexNode& getComplexNode(const std::string& id) const;
        /**
        * \brief Get a ArrayNode contained in the ComplexNode
        * \param id Id of the Node to get
        * \return A pointer to the ArrayNode
        */
        ArrayNode& getArrayNode(const std::string& id) const;
        /**
        * \brief Get a LinkNode contained in the ComplexNode
        * \param id Id of the Node to get
        * \return A pointer to the LinkNode
        */
        LinkNode& getLinkNode(const std::string& id) const;

        /**
         * \brief Get the type of a contained Node
         * \param id Id of the Node to get the NodeType
         * \return NodeType enum value representing the type of the Node with the given id
         */
        NodeType getNodeType(const std::string& id) const;
        /**
         * \brief Get all the Node Ids of the given Type contained in the ComplexNode
         * \param searchType Type of the Nodes you want to get (NodeType::Node works for all Nodes and NodeType::ContainerNode for ArrayNode and ComplexNode)
         * \return A std::vector of std::string containing the Id of the Nodes of the given type contained in the ComplexNode
         */
        std::vector<Node*> getAll(NodeType searchType = NodeType::Node) const;

        template <class T>
        std::vector<T*> getAll() const;

        /**
         * \brief Checks if the ComplexNode contains a Node with the given Id
         * \param id Id of the Node you want to search in the ComplexNode
         * \return true if a Node with the given id was found in the ComplexNode, false otherwise
         */
        bool contains(const std::string& id) const;
        /**
         * \brief Checks if the ComplexNode contains a Node with the given Id and the given NodeType
         * \param searchType Type of the Node you want to search in the ComplexNode
         * \param id Id of the Node you want to search in the ComplexNode
         * \return true if a Node with the given id and the given NodeType was found in the ComplexNode, false otherwise
         */
        bool contains(NodeType searchType, const std::string& id) const;

        /**
         * \brief Creates a DataNode in the ComplexNode
         * \param id Id of the DataNode to create
         * \param type DataType of the DataNode to create
         * \param data Value of the DataNode is serialized form
         * \return A reference to the newly created DataNode
         */
        DataNode& createDataNode(const std::string& id, const DataType& type, const std::string& data);
        /**
        * \brief Creates a DataNode in the ComplexNode
        * \param id Id of the DataNode to create
        * \param type DataType of the DataNode to create
        * \return A reference to the newly created DataNode
        */
        DataNode& createDataNode(const std::string& id, const DataType& type);
        /**
        * \brief Creates a DataNode in the ComplexNode
        * \param id Id of the DataNode to create
        * \param data String Value of the new DataNode
        * \return A reference to the newly created DataNode
        */
        DataNode& createDataNode(const std::string& id, const std::string& data);
        /**
        * \brief Creates a DataNode in the ComplexNode
        * \param id Id of the DataNode to create
        * \param data String Value of the new DataNode
        * \return A reference to the newly created DataNode
        */
        DataNode& createDataNode(const std::string& id, const char* data);
        /**
        * \brief Creates a DataNode in the ComplexNode
        * \param id Id of the DataNode to create
        * \param data Bool Value of the new DataNode
        * \return A reference to the newly created DataNode
        */
        DataNode& createDataNode(const std::string& id, bool data);
        /**
        * \brief Creates a DataNode in the ComplexNode
        * \param id Id of the DataNode to create
        * \param data Int Value of the new DataNode
        * \return A reference to the newly created DataNode
        */
        DataNode& createDataNode(const std::string& id, int data);
        /**
        * \brief Creates a DataNode in the ComplexNode
        * \param id Id of the DataNode to create
        * \param data Float Value of the new DataNode
        * \return A reference to the newly created DataNode
        */
        DataNode& createDataNode(const std::string& id, double data);
        /**
         * \brief Pushes an existing DataNode in the ComplexNode
         * \param attribute Pointer to the DataNode to push to the ComplexNode
         * \return A reference to the newly pushed DataNode
         */
        DataNode& pushDataNode(DataNode* attribute);

        /**
         * \brief Creates an ArrayNode in the ComplexNode
         * \param id Id of the ArrayNode to create
         * \return A reference to the newly created ArrayNode
         */
        ArrayNode& createArrayNode(const std::string& id);
        /**
         * \brief Pushes an existing ArrayNode in the ComplexNode
         * \param attribute Pointer to the ArrayNode to push to the ComplexNode
         * \return A reference to the newly pushed ArrayNode
         */
        ArrayNode& pushArrayNode(ArrayNode* attribute);

        /**
         * \brief Creates a ComplexNode in the ComplexNode
         * \param id Id of the ComplexNode to create
         * \return A reference to the newly created ComplexNode
         */
        ComplexNode& createComplexNode(const std::string& id);
        /**
         * \brief Pushes an existing ComplexNode in the ComplexNode
         * \param attribute Pointer to the ComplexNode to push to the ComplexNode
         * \return A reference to the newly pushed ComplexNode
         */
        ComplexNode& pushComplexNode(ComplexNode* attribute);

        /**
         * \brief Creates a LinkNode in the ComplexNode
         * \param id Id of the LinkNode to create
         * \param path Path of the Node the LinkNode should point to
         * \return A reference to the newly created LinkNode
         */
        LinkNode& createLinkNode(const std::string& id, const std::string& path);
        /**
         * \brief Pushes an existing LinkNode in the ComplexNode
         * \param attribute Pointer to the LinkNode to push to the ComplexNode 
         * \return A reference to the newly pushed LinkNode
         */
        LinkNode& pushLinkNode(LinkNode* attribute);

        /**
         * \brief Removes a child Node from the ComplexNode
         * \param id Id of the Node to remove
         * \param freeMemory If equals to true, the DataNode will be erased from memory\n 
         *                   else it will juste remove the Tree from the tree while keeping the DataNode pointer valid
         */
        void remove(const std::string& id);

        /**
         * \brief Removes all children of the ComplexNode
         * \param freeMemory If equals to true, all children will be erased from memory.
         */
        void clear();

        /**
        * \brief Writes the ComplexNode to a file
        * \param file File (std::ofstream) where to write the Node
        * \param spacing Default indentation of the file
        * \param depth Depth of the Node to write
        */
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth = 0) const override;
        /**
        * \brief Copies the ComplexNode into a new ContainerNode
        * \param newParent Parent of the new copied Node
        * \param newid Id to set to the newly created Node
        */
        void copy(ContainerNode* newParent, const std::string& newid = "") const override;

        /**
         * \brief Walks through the tree using a NodeIterator
         * \param walkFunction Function to execute at every ComplexNode child in the tree
         * \param useCache Should be equals to true if the NodeIterator is in cached mode, false if it should be in realtime mode
         */
        void walk(std::function<void(NodeIterator&)> walkFunction, bool useCache = false);
        /**
         * \brief Walks through the tree using a NodeValidator
         * \tparam T Type of the value returned by the NodeValidator
         * \param walkFunction Function to execute at every ComplexNode child in the tree
         * \param useCache Should be equals to true if the NodeValidator is in cached mode, false if it should be in realtime mode
         * \return The value returned by the NodeValidator
         */
        template <class T>
        T walk(std::function<void(NodeValidator<T>&)> walkFunction, bool useCache = false);

        /**
         * \brief Tells the ComplexNode to use the given NodeTemplate
         * \param useTemplate Pointer to the NodeTemplate the ComplexNode should use
         */
        void useTemplate(NodeTemplate* useTemplate);
        /**
         * \brief Gets the current template used by the ComplexNode
         * \return A pointer to the NodeTemplate used by the ComplexNode (nullptr if none is used)
         */
        NodeTemplate* getCurrentTemplate() const;
    };

    template <class ...Args>
    ComplexNode& ComplexNode::at(const std::string& cPath, Args ...pathParts) const
    {
        return getPath(cPath).at(pathParts...);
    }

    template <class T, class ...Args>
    T& ComplexNode::at(const std::string& cPath, Args ...pathParts) const
    {
        return getPath(cPath).at<T>(pathParts...);
    }

    template <>
    inline ComplexNode& ComplexNode::at<ComplexNode>(const std::string& cPath) const
    {
        return getComplexNode(cPath);
    }

    template <>
    inline ArrayNode& ComplexNode::at<ArrayNode>(const std::string& cPath) const
    {
        return getArrayNode(cPath);
    }

    template <>
    inline DataNode& ComplexNode::at<DataNode>(const std::string& cPath) const
    {
        return getDataNode(cPath);
    }

    template <>
    inline LinkNode& ComplexNode::at<LinkNode>(const std::string& cPath) const
    {
        return getLinkNode(cPath);
    }

    template <class T>
    T ComplexNode::walk(std::function<void(NodeValidator<T>&)> walkFunction, bool useCache)
    {
        if (useCache)
        {
            NodeValidator<T> baseIterator(this);
            while (!baseIterator.last())
            {
                baseIterator.next();
                walkFunction(baseIterator);
            }

            return baseIterator.result();
        }
        NodeValidator<T> baseIterator;
        for (std::string& complex : getAll(NodeType::ComplexNode))
        {
            if (!baseIterator.over())
                getComplexNode(complex).walk<T>(walkFunction, baseIterator);
            else
                break;
        }
        if (!baseIterator.over())
        {
            baseIterator.next(this);
            walkFunction(baseIterator);
        }
        return baseIterator.result();
    }

    template <class T>
    void ComplexNode::walk(std::function<void(NodeValidator<T>&)> walkFunction, NodeValidator<T>& iterator)
    {
        for (std::string& complex : getAll(NodeType::ComplexNode))
        {
            if (!iterator.over())
                getComplexNode(complex).walk<T>(walkFunction, iterator);
            else
                break;
        }
        if (!iterator.over())
        {
            iterator.next(this);
            walkFunction(iterator);
        }
    }

    template <class T>
    std::vector<T*> ComplexNode::getAll() const
    {
        std::vector<T*> nodes;
        for (Node* child : this->getAll(T::ClassType))
            nodes.push_back(static_cast<T*>(child));
        return nodes;
    }
}
