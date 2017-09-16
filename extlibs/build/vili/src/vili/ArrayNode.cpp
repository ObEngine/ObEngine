#include <fstream>

#include "vili/ComplexNode.hpp"
#include "vili/ArrayNode.hpp"
#include "Functions.hpp"

namespace vili
{
    ArrayNode::ArrayNode(ContainerNode* parent, const std::string& id) : ContainerNode(parent, id, NodeType::ArrayNode)
    {
    }

    ArrayNode::ArrayNode(const std::string& id) : ContainerNode(nullptr, id, NodeType::ArrayNode)
    {
    }

    ArrayNode::ArrayNode(const ArrayNode& copy) : ContainerNode(copy)
    {
        /*for (auto& data : copy.m_dataList)
        {
            m_dataList.emplace_back(*data);
            m_dataList.end()->get()->setParent(this);
        }*/
    }

    ArrayNode::~ArrayNode()
    {
    }

    unsigned int ArrayNode::size() const
    {
        return m_dataList.size();
    }

    DataNode& ArrayNode::get(unsigned int index) const
    {
        if (index < m_dataList.size())
            return *m_dataList[index].get();
        throw aube::ErrorHandler::Raise("Vili.Vili.ArrayNode.WrongIndex", {
            {"index", std::to_string(index)},
            {"path", getNodePath()},
            {"size", std::to_string(m_dataList.size())}
        });
    }

    DataNode& ArrayNode::operator[](unsigned index) const
    {
        return this->get(index);
    }

    std::vector<DataNode*>::iterator ArrayNode::begin()
    {
        m_iteratorCache.clear();
        for (int i = 0; i < m_dataList.size(); i++)
            m_iteratorCache.push_back(m_dataList[i].get());
        return m_iteratorCache.begin();
    }

    std::vector<DataNode*>::iterator ArrayNode::end()
    {
        return m_iteratorCache.end();
    }

    void ArrayNode::push(const std::string& element)
    {
        m_dataList.push_back(std::make_unique<DataNode>(this, "#" + std::to_string(m_dataList.size()), DataType::String));
        m_dataList.back()->set(element);
    }

    void ArrayNode::push(int element)
    {
        m_dataList.push_back(std::make_unique<DataNode>(this, "#" + std::to_string(m_dataList.size()), DataType::Int));
        m_dataList.back()->set(element);
    }

    void ArrayNode::push(bool element)
    {
        m_dataList.push_back(std::make_unique<DataNode>(this, "#" + std::to_string(m_dataList.size()), DataType::Bool));
        m_dataList.back()->set(element);
    }

    void ArrayNode::push(double element)
    {
        m_dataList.push_back(std::make_unique<DataNode>(this, "#" + std::to_string(m_dataList.size()), DataType::Float));
        m_dataList.back()->set(element);
    }

    void ArrayNode::insert(unsigned int index, const std::string& element)
    {
        m_dataList.insert(m_dataList.begin() + index, std::make_unique<DataNode>(this, "#" + std::to_string(m_dataList.size()), DataType::String));
        m_dataList[index]->set(element);
        this->reorder(index);
    }

    void ArrayNode::insert(unsigned int index, int element)
    {
        m_dataList.insert(m_dataList.begin() + index, std::make_unique<DataNode>(this, "#" + std::to_string(m_dataList.size()), DataType::Int));
        m_dataList[index]->set(element);
        this->reorder(index);
    }

    void ArrayNode::insert(unsigned int index, bool element)
    {
        m_dataList.insert(m_dataList.begin() + index, std::make_unique<DataNode>(this, "#" + std::to_string(m_dataList.size()), DataType::Bool));
        m_dataList[index]->set(element);
        this->reorder(index);
    }

    void ArrayNode::insert(unsigned int index, double element)
    {
        m_dataList.insert(m_dataList.begin() + index, std::make_unique<DataNode>(this, "#" + std::to_string(m_dataList.size()), DataType::Float));
        m_dataList[index]->set(element);
        this->reorder(index);
    }

    void ArrayNode::clear()
    {
        m_dataList.clear();
    }

    void ArrayNode::erase(unsigned int index)
    {
        m_dataList.erase(m_dataList.begin() + index);
    }

    Node* ArrayNode::extractElement(Node* element)
    {
        if (Functions::Vector::isInList(std::unique_ptr<DataNode>(dynamic_cast<DataNode*>(element)), m_dataList))
        {
            this->removeOwnership(element);
            int indexToRelease = Functions::Vector::indexOfElement(std::unique_ptr<DataNode>(dynamic_cast<DataNode*>(element)), m_dataList);
            m_dataList[indexToRelease].release();
            Functions::Vector::eraseAll(m_dataList, std::unique_ptr<DataNode>(dynamic_cast<DataNode*>(element)));
        }
        return element;
    }

    void ArrayNode::copy(ContainerNode* newParent, const std::string& newid) const
    {
        if (newParent->getType() == NodeType::ComplexNode)
        {
            std::string useID = newid.empty() ? m_id : newid;
            dynamic_cast<ComplexNode*>(newParent)->createArrayNode(useID);
            for (int i = 0; i < m_dataList.size(); i++)
                m_dataList[i]->copy(&dynamic_cast<ComplexNode*>(newParent)->getArrayNode(useID));
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.ArrayNode.WrongCopyTarget", {{"path", getNodePath()},{"target", newParent->getNodePath()}});
    }

    void ArrayNode::write(std::ofstream* file, const std::string& spacing, unsigned int depth) const
    {
        if (m_visible)
        {
            for (unsigned int j = 0; j < depth - 1; j++)
                (*file) << spacing;
            (*file) << m_id << ":[" << std::endl;
            for (unsigned int k = 0; k < size(); k++)
                this->get(k).write(file, spacing, depth + 1);
            for (unsigned int l = 0; l < depth - 1; l++)
                (*file) << spacing;
            (*file) << "]" << std::endl;
        }
    }

    void ArrayNode::reorder(int index)
    {
        for (int i = index + 1; i < m_dataList.size(); i++)
        {
            this->removeOwnership(m_dataList[i].get());
            m_dataList[i]->setId("#" + std::to_string(i));
            m_dataList[i]->setParent(this);
        }
    }
}
