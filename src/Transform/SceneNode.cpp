#include <Transform/SceneNode.hpp>

namespace obe
{
    namespace Transform
    {
        SceneNode::SceneNode(const std::string& id) : Movable(MovableType::SceneNode, id)
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
        }

        void SceneNode::move(const UnitVector& position)
        {
            for (auto& child : m_children)
            {
                child->move(position);
            }
        }
    }
}
