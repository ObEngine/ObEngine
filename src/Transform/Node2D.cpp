#include <Transform/Node2D.hpp>

namespace obe
{
    namespace Transform
    {
        Node2D::Node2D(const std::string& id) : Movable(MovableType::Node2D, id)
        {
        }

        void Node2D::addChild(Movable* child)
        {
            m_children.push_back(child);
        }

        void Node2D::setPosition(const UnitVector& position)
        {
            for (auto& child : m_children)
            {
                UnitVector offset = position - m_position;
                child->move(offset);
            }
        }

        void Node2D::move(const UnitVector& position)
        {
            for (auto& child : m_children)
            {
                child->move(position);
            }
        }
    }
}
