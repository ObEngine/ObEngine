#include <Collision/CollisionSpace.hpp>

namespace obe::collision
{
    void CollisionSpace::add_collider(Collider* collider)
    {
        m_colliders.insert(collider);
    }

    std::size_t CollisionSpace::get_collider_amount() const
    {
        return m_colliders.size();
    }

    std::unordered_set<Collider*> CollisionSpace::get_all_colliders() const
    {
        return m_colliders;
    }

    void CollisionSpace::remove_collider(Collider* collider)
    {
        m_colliders.erase(collider);
    }

    bool CollisionSpace::collides(const Collider& collider) const
    {
        for (const auto& space_collider : m_colliders)
        {
            if (&collider != space_collider && collider.collides(*space_collider))
            {
                return true;
            }
        }
        return false;
    }

    transform::UnitVector CollisionSpace::get_offset_before_collision(const Collider& collider,
        const transform::UnitVector& offset) const
    {
        std::vector<std::pair<Collider*, transform::UnitVector>> reachable_colliders;

        transform::UnitVector max_offset = offset;

        for (auto& space_collider : m_colliders)
        {
            if (&collider != space_collider && collider.can_collide_with(*space_collider))
            {
                const transform::UnitVector max_distance
                    = collider.get_offset_before_collision(*space_collider, offset);
                if (max_distance != offset)
                    reachable_colliders.emplace_back(space_collider, max_distance);
            }
        }

        if (!reachable_colliders.empty())
        {
            // Get lowest offset between this collider and a reachable collider
            for (auto& reachable : reachable_colliders)
            {
                if (reachable.second.magnitude()
                    < max_offset.to(transform::Units::ScenePixels).magnitude())
                {
                    max_offset = reachable.second;
                }
            }
        }

        return max_offset;
    }
}
