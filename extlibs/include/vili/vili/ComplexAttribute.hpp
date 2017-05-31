#pragma once

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "BaseAttribute.hpp"
#include "ContainerAttribute.hpp"
#include "ListAttribute.hpp"
#include "NodeIterator.hpp"
#include "NodeValidator.hpp"

namespace vili
{
    class LinkAttribute;
    class DataTemplate;

    class ComplexAttribute : public ContainerAttribute
    {
    protected:
        std::map<std::string, std::unique_ptr<Attribute>> m_childAttributes;
        std::vector<std::string> m_childAttributesNames;
        std::vector<std::string> m_heritFrom;
        DataTemplate* m_template = nullptr;
    public:
        const static Types::AttributeType ClassType = Types::ComplexAttribute;
        ComplexAttribute(ComplexAttribute* parent, const std::string& id);
        ComplexAttribute(ComplexAttribute* parent, const std::string& id, ComplexAttribute* herit);
        ComplexAttribute(ComplexAttribute* parent, const std::string& id, std::vector<ComplexAttribute*>* multipleHerit);
        ComplexAttribute(const std::string& id);
        ComplexAttribute(const std::string& id, ComplexAttribute* herit);
        ComplexAttribute(const std::string& id, std::vector<ComplexAttribute*>* multipleHerit);

        virtual ~ComplexAttribute()
        {
        }

        Attribute* extractElement(Attribute* element) override;
        void heritage(ComplexAttribute* heritTarget);

        ComplexAttribute& getPath(std::string attributePath) const;
        ComplexAttribute& operator[](const std::string& cPath) const;

        ComplexAttribute& at(const std::string& cPath) const;
        template <class T, class ...Args>
        T& at(const std::string& cPath, Args ...pathParts) const;
        template <class ...Args>
        ComplexAttribute& at(const std::string& cPath, Args ...pathParts) const;

        template <class T>
        T& at(const std::string& cPath) const { return T(); };

        Attribute* get(const std::string& attributeID) const;
        BaseAttribute& getBaseAttribute(const std::string& attributeID) const;
        ComplexAttribute& getComplexAttribute(const std::string& attributeID) const;
        ListAttribute& getListAttribute(const std::string& attributeID) const;
        LinkAttribute& getLinkAttribute(const std::string& attributeID) const;

        Types::AttributeType getAttributeType(const std::string& id) const;
        std::vector<std::string> getAll(Types::AttributeType searchType = Types::Attribute) const;

        bool contains(const std::string& attributeID) const;
        bool contains(Types::AttributeType searchType, const std::string& attributeID) const;

        void createBaseAttribute(const std::string& attributeID, const Types::DataType& type, const std::string& data);
        void createBaseAttribute(const std::string& attributeID, const Types::DataType& type);
        void createBaseAttribute(const std::string& attributeID, const std::string& data);
        void createBaseAttribute(const std::string& attributeID, const char* data);
        void createBaseAttribute(const std::string& attributeID, bool data);
        void createBaseAttribute(const std::string& attributeID, int data);
        void createBaseAttribute(const std::string& attributeID, double data);
        void pushBaseAttribute(BaseAttribute* attribute);

        void createListAttribute(const std::string& attributeID);
        void pushListAttribute(ListAttribute* attribute);

        void createComplexAttribute(const std::string& attributeID);
        void pushComplexAttribute(ComplexAttribute* attribute);

        void createLinkAttribute(const std::string& attributeID, const std::string& path);
        void pushLinkAttribute(LinkAttribute* attribute);

        void deleteBaseAttribute(const std::string& attributeID, bool freeMemory = false);
        void deleteComplexAttribute(const std::string& attributeID, bool freeMemory = false);
        void deleteListAttribute(const std::string& attributeID, bool freeMemory = false);
        void deleteLinkAttribute(const std::string& attributeID, bool freeMemory = false);

        void write(std::ofstream* file, const std::string& spacing, unsigned int depth = 0) const override;
        void copy(ContainerAttribute* newParent, const std::string& newid = "") const override;
        void walk(std::function<void(NodeIterator&)> walkFunction, bool useCache = false);
        void walk(std::function<void(NodeIterator&)> walkFunction, NodeIterator& iterator);
        template <class T>
        T walk(std::function<void(NodeValidator<T>&)> walkFunction, bool useCache = false);
        template <class T>
        void walk(std::function<void(NodeValidator<T>&)> walkFunction, NodeValidator<T>& iterator);

        void useTemplate(DataTemplate* useTemplate);
        DataTemplate* getCurrentTemplate() const;
    };

    template <class ...Args>
    ComplexAttribute& ComplexAttribute::at(const std::string& cPath, Args ...pathParts) const
    {
        return getPath(cPath).at(pathParts...);
    }

    template <class T, class ...Args>
    T& ComplexAttribute::at(const std::string& cPath, Args ...pathParts) const
    {
        return getPath(cPath).at<T>(pathParts...);
    }

    template <>
    inline ComplexAttribute& ComplexAttribute::at<ComplexAttribute>(const std::string& cPath) const
    {
        return getComplexAttribute(cPath);
    }

    template <>
    inline ListAttribute& ComplexAttribute::at<ListAttribute>(const std::string& cPath) const
    {
        return getListAttribute(cPath);
    }

    template <>
    inline BaseAttribute& ComplexAttribute::at<BaseAttribute>(const std::string& cPath) const
    {
        return getBaseAttribute(cPath);
    }

    template <>
    inline LinkAttribute& ComplexAttribute::at<LinkAttribute>(const std::string& cPath) const
    {
        return getLinkAttribute(cPath);
    }

    template <class T>
    T ComplexAttribute::walk(std::function<void(NodeValidator<T>&)> walkFunction, bool useCache)
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
        for (std::string& complex : getAll(Types::ComplexAttribute))
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
    void ComplexAttribute::walk(std::function<void(NodeValidator<T>&)> walkFunction, NodeValidator<T>& iterator)
    {
        for (std::string& complex : getAll(Types::ComplexAttribute))
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
