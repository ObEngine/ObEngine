#pragma once

#include <vector>

namespace vili
{
    class ComplexAttribute;

    class NodeIterator
    {
    protected:
        std::vector<ComplexAttribute*> m_cache;
        bool m_over = false;
        unsigned int m_index = 0;
        ComplexAttribute* m_node = nullptr;
        void next();
        void next(ComplexAttribute* node);
        friend class ComplexAttribute;
    public:
        NodeIterator();
        NodeIterator(ComplexAttribute* node);
        ComplexAttribute* operator->() const;
        ComplexAttribute* get() const;
        bool hasCache() const;
        unsigned int index() const;
        unsigned int size() const;
        bool first() const;
        bool last() const;
        bool over() const;
        void terminate();
    };
}
