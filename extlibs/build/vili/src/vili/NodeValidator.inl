#include "vili/ComplexAttribute.hpp"
#include "vili/NodeValidator.hpp"

namespace vili
{
    template <class T>
    NodeValidator<T>::NodeValidator()
    {

    }
    template <class T>
    NodeValidator<T>::NodeValidator(ComplexAttribute* node)
    {
        node->walk([this](NodeIterator& node) { m_cache.push_back(node.get()); });
    }
    template <class T>
    void NodeValidator<T>::validate(T result)
    {
        m_result = result;
    }
    template <class T>
    T NodeValidator<T>::result()
    {
        return m_result;
    }
}
