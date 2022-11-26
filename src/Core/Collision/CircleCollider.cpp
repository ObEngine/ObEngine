#include <Collision/CircleCollider.hpp>

namespace obe::collision
{
    const void* CircleCollider::get_c2_shape() const
    {
        return static_cast<const void*>(&m_shape);
    }

    const c2x* CircleCollider::get_c2_space_transform() const
    {
        return nullptr;
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

    transform::AABB CircleCollider::get_bounding_box() const
    {
        const transform::Vector2 position(m_position.x - m_shape.r, m_position.y - m_shape.r);
        const transform::Vector2 size(m_shape.r * 2, m_shape.r * 2);
        return transform::AABB(position, size);
    }

    transform::Vector2 CircleCollider::get_position() const
    {
        return m_position;
    }

    void CircleCollider::set_position(const transform::Vector2& position)
    {
        Movable::set_position(position);
        update_shape();
    }

    void CircleCollider::move(const transform::Vector2& position)
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
