#include <fstream>

#include "vili/ComplexAttribute.hpp"
#include "vili/ListAttribute.hpp"
#include "Functions.hpp"

namespace vili
{
    ListAttribute::ListAttribute(ContainerAttribute* parent, const std::string& id) : ContainerAttribute(parent, id, Types::ListAttribute)
    {
    }

    ListAttribute::ListAttribute(const std::string& id) : ContainerAttribute(nullptr, id, Types::ListAttribute)
    {
    }

    unsigned int ListAttribute::size() const
    {
        return m_dataList.size();
    }

    BaseAttribute& ListAttribute::get(unsigned int index) const
    {
        if (index < m_dataList.size())
            return *m_dataList[index].get();
        throw aube::ErrorHandler::Raise("Vili.Vili.ListAttribute.WrongIndex", {
                                            {"index", std::to_string(index)},
                                            {"path", getNodePath()},
                                            {"size", std::to_string(m_dataList.size())}
                                        });
    }

    std::vector<BaseAttribute*>::iterator ListAttribute::begin()
    {
        m_iteratorCache.clear();
        for (int i = 0; i < m_dataList.size(); i++)
            m_iteratorCache.push_back(m_dataList[i].get());
        return m_iteratorCache.begin();
    }

    std::vector<BaseAttribute*>::iterator ListAttribute::end()
    {
        return m_iteratorCache.end();
    }

    void ListAttribute::push(const std::string& element)
    {
        m_dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::String));
        m_dataList.back()->set(element);
    }

    void ListAttribute::push(int element)
    {
        m_dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Int));
        m_dataList.back()->set(element);
    }

    void ListAttribute::push(bool element)
    {
        m_dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Bool));
        m_dataList.back()->set(element);
    }

    void ListAttribute::push(double element)
    {
        m_dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Float));
        m_dataList.back()->set(element);
    }

    void ListAttribute::insert(unsigned int index, const std::string& element)
    {
        m_dataList.insert(m_dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::String));
        m_dataList[index]->set(element);
        this->reorder(index);
    }

    void ListAttribute::insert(unsigned int index, int element)
    {
        m_dataList.insert(m_dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Int));
        m_dataList[index]->set(element);
        this->reorder(index);
    }

    void ListAttribute::insert(unsigned int index, bool element)
    {
        m_dataList.insert(m_dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Bool));
        m_dataList[index]->set(element);
        this->reorder(index);
    }

    void ListAttribute::insert(unsigned int index, double element)
    {
        m_dataList.insert(m_dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Float));
        m_dataList[index]->set(element);
        this->reorder(index);
    }

    void ListAttribute::clear()
    {
        m_dataList.clear();
    }

    void ListAttribute::erase(unsigned int index)
    {
        m_dataList.erase(m_dataList.begin() + index);
    }

    Attribute* ListAttribute::extractElement(Attribute* element)
    {
        if (Functions::Vector::isInList(std::unique_ptr<BaseAttribute>(dynamic_cast<BaseAttribute*>(element)), m_dataList))
        {
            this->removeOwnership(element);
            int indexToRelease = Functions::Vector::indexOfElement(std::unique_ptr<BaseAttribute>(dynamic_cast<BaseAttribute*>(element)), m_dataList);
            m_dataList[indexToRelease].release();
            Functions::Vector::eraseAll(m_dataList, std::unique_ptr<BaseAttribute>(dynamic_cast<BaseAttribute*>(element)));
        }
        return element;
    }

    void ListAttribute::copy(ContainerAttribute* newParent, const std::string& newid) const
    {
        if (newParent->getType() == Types::ComplexAttribute)
        {
            std::string useID = newid.empty() ? m_id : newid;
            dynamic_cast<ComplexAttribute*>(newParent)->createListAttribute(useID);
            for (int i = 0; i < m_dataList.size(); i++)
                m_dataList[i]->copy(&dynamic_cast<ComplexAttribute*>(newParent)->getListAttribute(useID));
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.ListAttribute.WrongCopyTarget", {{"path", getNodePath()},{"target", newParent->getNodePath()}});
    }

    void ListAttribute::write(std::ofstream* file, const std::string& spacing, unsigned int depth) const
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
}
