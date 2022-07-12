#include <Collision/CircleCollider.hpp>

namespace obe::collision
{
    void* CircleCollider::get_c2_shape()
    {
        return static_cast<void*>(&m_shape);
    }

    void CircleCollider::update_shape()
    {
        m_shape.p.x = m_position.x;
        m_shape.p.y = m_position.y;
    }

    ColliderType CircleCollider::get_collider_type() const
    {
        return CircleCollider::Type;
    }

    CircleCollider::CircleCollider()
    {
        m_shape.p = c2v { 0, 0 };
        m_shape.r = 1;
    }

    transform::Rect CircleCollider::get_bounding_box() const
    {
        const transform::UnitVector position(m_position.x - m_shape.r, m_position.y - m_shape.r);
        const transform::UnitVector size(m_shape.r * 2, m_shape.r * 2);
        return transform::Rect(position, size);
    }

    transform::UnitVector CircleCollider::get_position() const
    {
        return m_position;
    }

    void CircleCollider::set_position(const transform::UnitVector& position)
    {
        Movable::set_position(position);
        update_shape();
    }

    void CircleCollider::move(const transform::UnitVector& position)
    {
        Movable::move(position);
        update_shape();
    }

    float CircleCollider::get_radius() const
    {
        return m_shape.r;
    }

    void CircleCollider::set_radius(const float radius)
    {
        m_shape.r = radius;
    }
}
