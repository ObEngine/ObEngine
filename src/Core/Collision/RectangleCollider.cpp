#include <Collision/RectangleCollider.hpp>

namespace obe::collision
{
    const void* RectangleCollider::get_c2_shape() const
    {
        return static_cast<const void*>(&m_shape);
    }

    const c2x* RectangleCollider::get_c2_space_transform() const
    {
        return nullptr;
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

    RectangleCollider::RectangleCollider(const transform::Vector2& size)
        : m_size(size)
    {
        update_shape();
    }

    RectangleCollider::RectangleCollider(
        const transform::Vector2& position, const transform::Vector2& size)
        : Collider(position)
        , m_size(size)
    {
        update_shape();
    }

    transform::AABB RectangleCollider::get_bounding_box() const
    {
        return transform::AABB(this->get_position(), this->get_size());
    }

    transform::Vector2 RectangleCollider::get_position() const
    {
        return transform::Vector2(m_shape.min.x, m_shape.min.y);
    }

    transform::Vector2 RectangleCollider::get_size() const
    {
        return transform::Vector2(m_shape.max.x - m_shape.min.x, m_shape.max.y - m_shape.min.y);
    }

    void RectangleCollider::set_size(const transform::Vector2& size)
    {
        m_size.set(size);
        update_shape();
    }

    void RectangleCollider::set_position(const transform::Vector2& position)
    {
        Movable::set_position(position);
        update_shape();
    }

    void RectangleCollider::move(const transform::Vector2& position)
    {
        Movable::move(position);
        update_shape();
    }
}
