#pragma once

#include <vector>
#include <memory>

#include "BaseAttribute.hpp"
#include "ContainerAttribute.hpp"

namespace vili
{
    //ListAttribute
    class ListAttribute : public ContainerAttribute
    {
    private:
        std::vector<std::unique_ptr<BaseAttribute>> m_dataList;
        std::vector<BaseAttribute*> m_iteratorCache;
        void reorder(int index);
    public:
        const static Types::AttributeType ClassType = Types::ListAttribute;
        ListAttribute(ContainerAttribute* parent, const std::string& id);
        ListAttribute(const std::string& id);

        virtual ~ListAttribute()
        {
        }

        unsigned int size() const;
        BaseAttribute& get(unsigned int index) const;
        std::vector<BaseAttribute*>::iterator begin();
        std::vector<BaseAttribute*>::iterator end();
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
        Attribute* extractElement(Attribute* element) override;
        void copy(ContainerAttribute* newParent, const std::string& newid = "") const override;
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override;
    };
}
