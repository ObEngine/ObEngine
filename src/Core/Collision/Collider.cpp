#define CUTE_C2_IMPLEMENTATION

#include <cute/cute_c2.h>

#include <Collision/Collider.hpp>

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

    const std::unordered_set<std::string>& Collider::get_tag_set(ColliderTagType tag_type) const
    {
        switch (tag_type)
        {
        case ColliderTagType::Tag:
            return m_tags;
        case ColliderTagType::Accepted:
            return m_accepted_tags;
        case ColliderTagType::Rejected:
            return m_rejected_tags;
        }
        return m_tags;
    }

    std::unordered_set<std::string>& Collider::get_tag_set(ColliderTagType tag_type)
    {
        switch (tag_type)
        {
        case ColliderTagType::Tag:
            return m_tags;
        case ColliderTagType::Accepted:
            return m_accepted_tags;
        case ColliderTagType::Rejected:
            return m_rejected_tags;
        }
        return m_tags;
    }

    ColliderType Collider::get_collider_type() const
    {
        return Collider::Type;
    }

    Collider::Collider(const transform::UnitVector& position)
        : Movable(position)
    {
    }

    void Collider::add_tag(ColliderTagType tag_type, const std::string& tag)
    {
        get_tag_set(tag_type).insert(tag);
    }

    void Collider::remove_tag(ColliderTagType tag_type, const std::string& tag)
    {
        get_tag_set(tag_type).erase(tag);
    }

    void Collider::clear_tags(ColliderTagType tag_type)
    {
        get_tag_set(tag_type).clear();
    }

    bool Collider::matches_any_tag(
        ColliderTagType tag_type, const std::unordered_set<std::string>& tags) const
    {
        const std::unordered_set<std::string> collider_tags = get_tag_set(tag_type);
        for (const auto& tag : tags)
        {
            if (collider_tags.contains(tag))
            {
                return true;
            }
        }
        return false;
    }

    bool Collider::contains_tag(ColliderTagType tag_type, const std::string& tag) const
    {
        return get_tag_set(tag_type).contains(tag);
    }

    std::unordered_set<std::string> Collider::get_all_tags(ColliderTagType tag_type) const
    {
        return get_tag_set(tag_type);
    }

    bool Collider::can_collide_with(const Collider& collider) const
    {
        if (this->matches_any_tag(
                ColliderTagType::Rejected, collider.get_all_tags(ColliderTagType::Tag)))
            return false;
        if (!get_tag_set(ColliderTagType::Accepted).empty()
            && !this->matches_any_tag(
                ColliderTagType::Accepted, collider.get_all_tags(ColliderTagType::Tag)))
            return false;
        return true;
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
        const transform::UnitVector& self_offset,
        const transform::UnitVector& other_offset) const
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
}
