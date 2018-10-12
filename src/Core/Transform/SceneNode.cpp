#include <Transform/SceneNode.hpp>

namespace obe::Transform
{
    SceneNode::SceneNode() : Movable(MovableType::SceneNode)
    {
    }

    void SceneNode::addChild(Movable* child)
    {
        m_children.push_back(child);
    }

    void SceneNode::setPosition(const UnitVector& position)
    {
        for (auto& child : m_children)
        {
            UnitVector offset = position - m_position;
            child->move(offset);
        }
        Movable::setPosition(position);
    }

    void SceneNode::move(const UnitVector& position)
    {
        for (auto& child : m_children)
        {
            child->move(position);
        }
        Movable::move(position);
    }
}