#include <Scene/SceneNode.hpp>

namespace obe::Scene
{
    void SceneNode::addChild(Movable* child)
    {
        m_children.push_back(child);
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
}