#include <Collision/RectangleCollider.hpp>

namespace obe::collision
{
    void* RectangleCollider::get_c2_shape()
    {
        return static_cast<void*>(&m_shape);
    }

    void RectangleCollider::update_shape()
    {
        m_shape.min.x = m_position.x;
        m_shape.min.y = m_position.y;
        m_shape.max.x = m_position.x + m_size.x;
        m_shape.max.y = m_position.y + m_size.y;
    }

    ColliderType RectangleCollider::get_collider_type() const
    {
        return RectangleCollider::Type;
    }

    RectangleCollider::RectangleCollider()
        : m_size(1, 1)
    {
        update_shape();
    }

    RectangleCollider::RectangleCollider(const transform::UnitVector& size)
        : m_size(size)
    {
        update_shape();
    }

    RectangleCollider::RectangleCollider(const transform::UnitVector& position,
        const transform::UnitVector& size)
            : Collider(position)
            , m_size(size)
    {
        update_shape();
    }

    transform::Rect RectangleCollider::get_bounding_box() const
    {
        return transform::Rect(this->get_position(), this->get_size());
    }

    transform::UnitVector RectangleCollider::get_position() const
    {
        return transform::UnitVector(m_shape.min.x, m_shape.min.y);
    }

    transform::UnitVector RectangleCollider::get_size() const
    {
        return transform::UnitVector(
            m_shape.max.x - m_shape.min.x, m_shape.max.y - m_shape.min.y);
    }

    void RectangleCollider::set_size(const transform::UnitVector& size)
    {
        m_size = size;
        update_shape();
    }

    void RectangleCollider::set_position(const transform::UnitVector& position)
    {
        Movable::set_position(position);
        update_shape();
    }

    void RectangleCollider::move(const transform::UnitVector& position)
    {
        Movable::move(position);
        update_shape();
    }
}
