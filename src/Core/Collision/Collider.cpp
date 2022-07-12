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

    bool Collider::collides(const Collider& collider, const transform::UnitVector& offset) const
    {
        const void* a_c2_shape = this->get_c2_shape();
        const void* b_c2_shape = collider.get_c2_shape();
        const C2_TYPE a_type = collider_type_to_c2type(this->get_collider_type());
        const C2_TYPE b_type = collider_type_to_c2type(collider.get_collider_type());
        c2x shape_transform;
        shape_transform.p.x = offset.x;
        shape_transform.p.y = offset.y;
        return c2Collided(a_c2_shape, &shape_transform, a_type, b_c2_shape, nullptr, b_type);
    }

    transform::UnitVector Collider::get_offset_before_collision(const Collider& collider,
        const transform::UnitVector& offset) const
    {
        const void* a_c2_shape = this->get_c2_shape();
        const void* b_c2_shape = collider.get_c2_shape();
        const C2_TYPE a_type = collider_type_to_c2type(this->get_collider_type());
        const C2_TYPE b_type = collider_type_to_c2type(collider.get_collider_type());
        c2v output;
        c2GJK(a_c2_shape, a_type, nullptr, b_c2_shape, b_type, nullptr, &output, nullptr, 1, nullptr, nullptr);
        return transform::UnitVector(output.x, output.y);
    }
}
