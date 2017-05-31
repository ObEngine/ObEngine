#pragma once

#include "NodeIterator.hpp"

namespace vili
{
    template <class T>
    class NodeValidator : public NodeIterator
    {
    private:
        T m_result;
    public:
        NodeValidator();
        NodeValidator(ComplexAttribute* node);
        void validate(T result);
        T result();
    };
}
