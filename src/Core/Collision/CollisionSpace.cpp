#include <Collision/CollisionSpace.hpp>
#include <Time/TimeUtils.hpp>

namespace obe::collision
{
    bool CollisionSpace::matches_any_tag(const std::unordered_set<std::string>& input_tags,
        const std::unordered_set<std::string>& blacklist)
    {
        for (const auto& tag : input_tags)
        {
            if (blacklist.contains(tag))
            {
                return true;
            }
        }
        return false;
    }

    bool CollisionSpace::can_collide_with(
        const Collider& collider1, const Collider& collider2, bool check_both_directions) const
    {
        const std::string tag = collider1.get_tag();
        if (m_tags_blacklists.contains(tag))
        {
            const auto& tag_blacklist = m_tags_blacklists.at(tag);
            if (tag_blacklist.contains(collider2.get_tag()))
            {
                return false;
            }
        }

        const bool is_valid
            = (!check_both_directions || can_collide_with(collider2, collider1, false));

            
        // if true, check if we need to check for tags on collider2 -> collider1
        return is_valid;
    }

    constexpr double COLLISION_SPACE_SIZE = 100000000;

    CollisionSpace::CollisionSpace()
        : m_quadtree(
            transform::AABB(
                transform::UnitVector(-COLLISION_SPACE_SIZE, -COLLISION_SPACE_SIZE),
                transform::UnitVector(2 * COLLISION_SPACE_SIZE, 2 * COLLISION_SPACE_SIZE)
            )
        )
    {
    }

    void CollisionSpace::add_collider(const Collider* collider)
    {
        m_colliders.insert(collider);
        m_quadtree.add(collider);
    }

    std::size_t CollisionSpace::get_collider_amount() const
    {
        return m_colliders.size();
    }

    std::unordered_set<const Collider*> CollisionSpace::get_all_colliders() const
    {
        return m_colliders;
    }

    void CollisionSpace::remove_collider(const Collider* collider)
    {
        m_colliders.erase(collider);
        m_quadtree.remove(collider);
    }

    void CollisionSpace::refresh_collider(const Collider* collider)
    {
        m_quadtree.remove(collider);
        m_quadtree.add(collider);
    }

    void CollisionSpace::refresh_quadtree()
    {
        m_quadtree.clear();
        for (const Collider* collider : m_colliders)
        {
            m_quadtree.add(collider);
        }
    }

    bool CollisionSpace::collides(const Collider& collider) const
    {
        std::vector<const Collider*> possible_collisions
            = m_quadtree.query(collider.get_bounding_box());

        for (const Collider* space_collider : possible_collisions)
        {
            if (&collider != space_collider && can_collide_with(collider, *space_collider)
                && collider.collides(*space_collider))
            {
                return true;
            }
        }
        return false;
    }

    transform::UnitVector CollisionSpace::get_offset_before_collision(const Collider& collider,
        const transform::UnitVector& offset) const
    {
        const std::vector<ReachableCollider> reachable_colliders = this->get_reachable_colliders(collider, offset);
        return this->get_offset_before_collision(collider, reachable_colliders, offset);
    }

    transform::UnitVector CollisionSpace::get_offset_before_collision(const Collider& collider,
        const std::vector<ReachableCollider>& reachable_colliders,
        const transform::UnitVector& offset) const
    {
        transform::UnitVector max_offset = offset;

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

    std::vector<ReachableCollider> CollisionSpace::get_reachable_colliders(
        const Collider& collider, const transform::UnitVector& offset) const
    {
        const transform::AABB bbox = collider.get_bounding_box();
        transform::AABB translated_bbox = collider.get_bounding_box();
        translated_bbox.move(offset);

        const double min_left = std::min(bbox.get_position().x, translated_bbox.get_position().x);
        const double max_right = std::max(
            bbox.get_position().x + bbox.width(), translated_bbox.get_position().x + bbox.width());
        const double min_top = std::min(bbox.get_position().y, translated_bbox.get_position().y);
        const double max_bottom = std::max(bbox.get_position().y + bbox.height(),
            translated_bbox.get_position().y + bbox.height());

        transform::AABB trajectory_bbox(transform::UnitVector(min_left, min_top),
            transform::UnitVector(max_right - min_left, max_bottom - min_top));

        std::vector<const Collider*> quadtree_query_results = m_quadtree.query(trajectory_bbox);

        std::vector<ReachableCollider> reachable_colliders;

        for (const Collider* space_collider : quadtree_query_results)
        {
            if (&collider != space_collider && can_collide_with(collider, *space_collider))
            {
                const transform::UnitVector max_distance
                    = collider.get_offset_before_collision(*space_collider, offset);
                if (max_distance != offset)
                    reachable_colliders.emplace_back(space_collider, max_distance);
            }
        }

        return reachable_colliders;
    }

    void CollisionSpace::add_tag_to_blacklist(const std::string& source_tag,
        const std::string& rejected_tag)
    {
        if (!m_tags_blacklists.contains(source_tag))
        {
            m_tags_blacklists.insert({ source_tag, {} });
        }
        m_tags_blacklists.at(source_tag).insert(rejected_tag);
    }

    void CollisionSpace::remove_tag_to_blacklist(const std::string& source_tag,
        const std::string& rejected_tag)
    {
        if (m_tags_blacklists.contains(source_tag))
        {
            m_tags_blacklists.at(source_tag).erase(rejected_tag);
        }
    }

    void CollisionSpace::clear_blacklist(const std::string& source_tag)
    {
        if (m_tags_blacklists.contains(source_tag))
        {
            m_tags_blacklists.at(source_tag).clear();
        }
    }

    const std::unordered_set<std::string>& CollisionSpace::get_blacklist(
        const std::string& source_tag) const
    {
        if (!m_tags_blacklists.contains(source_tag))
        {
            static const std::unordered_set<std::string> EMPTY_SET;
            return EMPTY_SET;
        }
        return m_tags_blacklists.at(source_tag);
    }
}
