#include <Scene/Exceptions.hpp>
#include <Scene/SceneNode.hpp>

#include <algorithm>

namespace obe::Scene
{
    void SceneNode::addChild(Movable& child)
    {
        m_children.push_back(&child);
    }

    void SceneNode::removeChild(Movable& child)
    {
        const auto childToRemove
            = std::remove(m_children.begin(), m_children.end(), &child);
        if (childToRemove == m_children.end())
            throw Exceptions::ChildNotInSceneNode(this, &child, EXC_INFO);
        m_children.erase(childToRemove, m_children.end());
    }

    void SceneNode::setPosition(const Transform::UnitVector& position)
    {
        for (auto& child : m_children)
        {
            Transform::UnitVector offset = position - m_position;
            child->move(offset);
        }
        Movable::setPosition(position);
    }

    void SceneNode::move(const Transform::UnitVector& position)
    {
        for (auto& child : m_children)
        {
            child->move(position);
        }
        Movable::move(position);
    }
} // namespace obe::Scene