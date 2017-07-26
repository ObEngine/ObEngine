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
     */
    class ComplexNode : public ContainerNode
    {
    protected:
        std::map<std::string, std::unique_ptr<Node>> m_childAttributes;
        std::vector<std::string> m_childAttributesNames;
        std::vector<std::string> m_heritFrom;
        NodeTemplate* m_template = nullptr;
    public:
        /**
         * \brief Redefines ClassType to NodeType::ComplexNode
         */
        const static NodeType ClassType = NodeType::ComplexNode;
        ComplexNode(ComplexNode* parent, const std::string& id);
        ComplexNode(ComplexNode* parent, const std::string& id, ComplexNode* herit);
        ComplexNode(ComplexNode* parent, const std::string& id, std::vector<ComplexNode*>* multipleHerit);
        ComplexNode(const std::string& id);
        ComplexNode(const std::string& id, ComplexNode* herit);
        ComplexNode(const std::string& id, std::vector<ComplexNode*>* multipleHerit);

        virtual ~ComplexNode()
        {
        }

        Node* extractElement(Node* element) override;
        void heritage(ComplexNode* heritTarget);

        ComplexNode& getPath(std::string attributePath) const;
        ComplexNode& operator[](const std::string& cPath) const;

        ComplexNode& at(const std::string& cPath) const;
        template <class T, class ...Args>
        T& at(const std::string& cPath, Args ...pathParts) const;
        template <class ...Args>
        ComplexNode& at(const std::string& cPath, Args ...pathParts) const;

        template <class T>
        T& at(const std::string& cPath) const { return T(); };

        Node* get(const std::string& attributeID) const;
        DataNode& getBaseAttribute(const std::string& attributeID) const;
        ComplexNode& getComplexAttribute(const std::string& attributeID) const;
        ArrayNode& getListAttribute(const std::string& attributeID) const;
        LinkNode& getLinkAttribute(const std::string& attributeID) const;

        NodeType getAttributeType(const std::string& id) const;
        std::vector<std::string> getAll(NodeType searchType = NodeType::Node) const;

        bool contains(const std::string& attributeID) const;
        bool contains(NodeType searchType, const std::string& attributeID) const;

        DataNode& createBaseAttribute(const std::string& attributeID, const DataType& type, const std::string& data);
        DataNode& createBaseAttribute(const std::string& attributeID, const DataType& type);
        DataNode& createBaseAttribute(const std::string& attributeID, const std::string& data);
        DataNode& createBaseAttribute(const std::string& attributeID, const char* data);
        DataNode& createBaseAttribute(const std::string& attributeID, bool data);
        DataNode& createBaseAttribute(const std::string& attributeID, int data);
        DataNode& createBaseAttribute(const std::string& attributeID, double data);
        DataNode& pushBaseAttribute(DataNode* attribute);

        ArrayNode& createListAttribute(const std::string& attributeID);
        ArrayNode& pushListAttribute(ArrayNode* attribute);

        ComplexNode& createComplexAttribute(const std::string& attributeID);
        ComplexNode& pushComplexAttribute(ComplexNode* attribute);

        LinkNode& createLinkAttribute(const std::string& attributeID, const std::string& path);
        LinkNode& pushLinkAttribute(LinkNode* attribute);

        void deleteBaseAttribute(const std::string& attributeID, bool freeMemory = false);
        void deleteComplexAttribute(const std::string& attributeID, bool freeMemory = false);
        void deleteListAttribute(const std::string& attributeID, bool freeMemory = false);
        void deleteLinkAttribute(const std::string& attributeID, bool freeMemory = false);

        void write(std::ofstream* file, const std::string& spacing, unsigned int depth = 0) const override;
        void copy(ContainerNode* newParent, const std::string& newid = "") const override;
        void walk(std::function<void(NodeIterator&)> walkFunction, bool useCache = false);
        void walk(std::function<void(NodeIterator&)> walkFunction, NodeIterator& iterator);
        template <class T>
        T walk(std::function<void(NodeValidator<T>&)> walkFunction, bool useCache = false);
        template <class T>
        void walk(std::function<void(NodeValidator<T>&)> walkFunction, NodeValidator<T>& iterator);

        void useTemplate(NodeTemplate* useTemplate);
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
        return getComplexAttribute(cPath);
    }

    template <>
    inline ArrayNode& ComplexNode::at<ArrayNode>(const std::string& cPath) const
    {
        return getListAttribute(cPath);
    }

    template <>
    inline DataNode& ComplexNode::at<DataNode>(const std::string& cPath) const
    {
        return getBaseAttribute(cPath);
    }

    template <>
    inline LinkNode& ComplexNode::at<LinkNode>(const std::string& cPath) const
    {
        return getLinkAttribute(cPath);
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
                getComplexAttribute(complex).walk<T>(walkFunction, baseIterator);
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
                getComplexAttribute(complex).walk<T>(walkFunction, iterator);
            else
                break;
        }
        if (!iterator.over())
        {
            iterator.next(this);
            walkFunction(iterator);
        }
    }
}
