#define CUTE_C2_IMPLEMENTATION

#include <cute/cute_c2.h>

#include <Collision/CapsuleCollider.hpp>
#include <Collision/CircleCollider.hpp>
#include <Collision/Collider.hpp>
#include <Collision/Exceptions.hpp>
#include <Collision/PolygonCollider.hpp>
#include <Collision/RectangleCollider.hpp>

namespace obe::collision
{
    C2_TYPE collider_type_to_c2type(ColliderType collider_type)
    {
        switch (collider_type)
        {
        case ColliderType::Collider:
            return C2_TYPE_NONE;
        case ColliderType::Circle:
            return C2_TYPE_CIRCLE;
        case ColliderType::Rectangle:
            return C2_TYPE_AABB;
        case ColliderType::Capsule:
            return C2_TYPE_CAPSULE;
        case ColliderType::Polygon:
            return C2_TYPE_POLY;
        }
        return C2_TYPE_NONE;
    }

    ColliderType Collider::get_collider_type() const
    {
        return Collider::Type;
    }

    Collider::Collider(const transform::UnitVector& position)
        : Movable(position)
    {
    }

    void Collider::set_tag(const std::string& tag)
    {
        m_tag = tag;
    }

    std::string Collider::get_tag() const
    {
        return m_tag;
    }

    bool Collider::collides(const Collider& collider) const
    {
        const void* a_c2_shape = this->get_c2_shape();
        const void* b_c2_shape = collider.get_c2_shape();
        const C2_TYPE a_type = collider_type_to_c2type(this->get_collider_type());
        const C2_TYPE b_type = collider_type_to_c2type(collider.get_collider_type());
        const c2x* a_transform = this->get_c2_space_transform();
        const c2x* b_transform = collider.get_c2_space_transform();
        return c2Collided(a_c2_shape, a_transform, a_type, b_c2_shape, b_transform, b_type);
    }

    transform::UnitVector Collider::get_offset_before_collision(const Collider& collider,
        const transform::UnitVector& self_offset, const transform::UnitVector& other_offset) const
    {
        const void* a_c2_shape = this->get_c2_shape();
        const void* b_c2_shape = collider.get_c2_shape();
        const C2_TYPE a_type = collider_type_to_c2type(this->get_collider_type());
        const C2_TYPE b_type = collider_type_to_c2type(collider.get_collider_type());
        const c2v c2_self_offset
            = { static_cast<float>(self_offset.x), static_cast<float>(self_offset.y) };
        const c2v c2_other_offset
            = { static_cast<float>(other_offset.x), static_cast<float>(other_offset.y) };
        const c2x* a_transform = this->get_c2_space_transform();
        const c2x* b_transform = collider.get_c2_space_transform();
        const c2TOIResult result = c2TOI(a_c2_shape, a_type, a_transform, c2_self_offset,
            b_c2_shape, b_type, b_transform, c2_other_offset, 0);
        const auto final_offset = self_offset * result.toi;
        if (final_offset.x == 0 && final_offset.y == 0)
        {
            return self_offset;
        }
        if (final_offset == self_offset && this->collides(collider))
        {
            return transform::UnitVector(0, 0);
        }
        return final_offset;
    }

    std::unique_ptr<Collider> Collider::copy() const
    {
        switch (this->get_collider_type())
        {
        case ColliderType::Collider:
            throw exceptions::InvalidColliderType(
                ColliderTypeMeta::to_string(ColliderType::Collider));
        case ColliderType::Circle:
            return std::make_unique<CircleCollider>(static_cast<const CircleCollider&>(*this));
        case ColliderType::Rectangle:
            return std::make_unique<RectangleCollider>(
                static_cast<const RectangleCollider&>(*this));
        case ColliderType::Capsule:
            return std::make_unique<CapsuleCollider>(static_cast<const CapsuleCollider&>(*this));
        case ColliderType::Polygon:
            return std::make_unique<PolygonCollider>(static_cast<const PolygonCollider&>(*this));
        default:
            throw exceptions::InvalidColliderType("?");
        }
    }
}
