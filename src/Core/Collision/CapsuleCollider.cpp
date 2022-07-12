#include <Collision/CapsuleCollider.hpp>

namespace obe::collision
{
    void* CapsuleCollider::get_c2_shape()
    {
        return static_cast<void*>(&m_shape);
    }

    void CapsuleCollider::update_shape()
    {
        // TODO
    }

    ColliderType CapsuleCollider::get_collider_type() const
    {
        return ColliderType::Capsule;
    }

    CapsuleCollider::CapsuleCollider()
    {
        update_shape();
    }

    transform::Rect CapsuleCollider::get_bounding_box() const
    {
        return transform::Rect();
    }

    transform::UnitVector CapsuleCollider::get_position() const
    {
        return Collider::get_position();
    }

    void CapsuleCollider::set_position(const transform::UnitVector& position)
    {
        Collider::set_position(position);
    }

    void CapsuleCollider::move(const transform::UnitVector& position)
    {
        Collider::move(position);
    }

    float CapsuleCollider::get_radius() const
    {
        return m_shape.r;
    }

    void CapsuleCollider::set_radius(float radius)
    {
        m_shape.r = radius;
    }
}
