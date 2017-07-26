#pragma once

#include <vector>
#include <memory>

#include "DataNode.hpp"
#include "ContainerNode.hpp"

namespace vili
{
    //ListAttribute
    class ArrayNode : public ContainerNode
    {
    private:
        std::vector<std::unique_ptr<DataNode>> m_dataList;
        std::vector<DataNode*> m_iteratorCache;
        void reorder(int index);
    public:
        const static NodeType ClassType = NodeType::ArrayNode;
        ArrayNode(ContainerNode* parent, const std::string& id);
        ArrayNode(const std::string& id);

        virtual ~ArrayNode()
        {
        }

        unsigned int size() const;
        DataNode& get(unsigned int index) const;
        std::vector<DataNode*>::iterator begin();
        std::vector<DataNode*>::iterator end();
        void push(const std::string& element);
        void push(int element);
        void push(bool element);
        void push(double element);
        void insert(unsigned int index, const std::string& element);
        void insert(unsigned int index, int element);
        void insert(unsigned int index, bool element);
        void insert(unsigned int index, double element);
        void clear();
        void erase(unsigned int index);
        Node* extractElement(Node* element) override;
        void copy(ContainerNode* newParent, const std::string& newid = "") const override;
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override;
    };
}
