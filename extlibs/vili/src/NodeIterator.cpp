#include <ComplexNode.hpp>
#include <ErrorHandler.hpp>
#include <NodeIterator.hpp>

namespace vili
{
    NodeIterator::NodeIterator()
    {
    }

    NodeIterator::NodeIterator(ComplexNode* node)
    {
        node->walk([this](NodeIterator& node) { m_cache.push_back(node.get()); });
    }

    void NodeIterator::next()
    {
        if (hasCache())
            m_node = m_cache[m_index++];
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.NodeIterator.NoCache", {{"class", "NodeIterator"},{"function", "next"}});
    }

    void NodeIterator::next(ComplexNode* node)
    {
        if (!hasCache())
            m_node = node;
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.NodeIterator.HasCache", {{"class", "NodeIterator"},{"function", "next"}});
    }

    bool NodeIterator::hasCache() const
    {
        return (m_cache.size() > 0);
    }

    ComplexNode* NodeIterator::operator->() const
    {
        return m_node;
    }

    ComplexNode* NodeIterator::get() const
    {
        return m_node;
    }

    unsigned int NodeIterator::index() const
    {
        if (hasCache())
            return m_index;
        throw aube::ErrorHandler::Raise("Vili.Vili.NodeIterator.NoCache", {{"class", "NodeIterator"},{"function", "index"}});
    }

    unsigned int NodeIterator::size() const
    {
        if (hasCache())
            return m_cache.size();
        throw aube::ErrorHandler::Raise("Vili.Vili.NodeIterator.NoCache", {{"class", "NodeIterator"},{"function", "size"}});
    }

    bool NodeIterator::first() const
    {
        if (hasCache())
            return (m_index == 0);
        throw aube::ErrorHandler::Raise("Vili.Vili.NodeIterator.NoCache", {{"class", "NodeIterator"},{"function", "first"}});
    }

    bool NodeIterator::last() const
    {
        if (hasCache())
            return (m_index >= (m_cache.size()));
        throw aube::ErrorHandler::Raise("Vili.Vili.NodeIterator.NoCache", {{"class", "NodeIterator"},{"function", "last"}});
    }

    bool NodeIterator::over() const
    {
        return m_over;
    }

    void NodeIterator::terminate()
    {
        m_over = true;
        m_index = 0;
        m_cache.clear();
    }
}
