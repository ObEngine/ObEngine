#include <Collision/CapsuleCollider.hpp>

namespace obe::collision
{
    const void* CapsuleCollider::get_c2_shape() const
    {
        return static_cast<const void*>(&m_shape);
    }

    const c2x* CapsuleCollider::get_c2_space_transform() const
    {
        return nullptr;
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

    transform::AABB CapsuleCollider::get_bounding_box() const
    {
        return transform::AABB();
    }

    transform::Vector2 CapsuleCollider::get_position() const
    {
        return Collider::get_position();
    }

    void CapsuleCollider::set_position(const transform::Vector2& position)
    {
        Collider::set_position(position);
    }

    void CapsuleCollider::move(const transform::Vector2& position)
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
