#include <algorithm>

#include <Scene/Exceptions.hpp>
#include <Scene/SceneNode.hpp>

namespace obe::scene
{
    void SceneNode::add_child(Movable& child)
    {
        m_children.push_back(&child);
    }

    void SceneNode::remove_child(Movable& child)
    {
        const auto child_to_remove = std::ranges::remove(m_children, &child).begin();
        if (child_to_remove == m_children.end())
            throw Exceptions::ChildNotInSceneNode(this, &child, EXC_INFO);
        m_children.erase(child_to_remove, m_children.end());
    }

    void SceneNode::set_position(const transform::UnitVector& position)
    {
        for (const auto& child : m_children)
        {
            transform::UnitVector offset = position - m_position;
            child->move(offset);
        }
        Movable::set_position(position);
    }

    void SceneNode::move(const transform::UnitVector& position)
    {
        for (const auto& child : m_children)
        {
            child->move(position);
        }
        Movable::move(position);
    }

    void SceneNode::set_position_without_children(const transform::UnitVector& position)
    {
        Movable::set_position(position);
    }

    void SceneNode::move_without_children(const transform::UnitVector& position)
    {
        Movable::move(position);
    }
} // namespace obe::scene
