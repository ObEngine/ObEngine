#include <Collision/CollisionSpace.hpp>

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
        std::vector<std::pair<Collider*, transform::UnitVector>> reachable_colliders;

        transform::UnitVector max_offset = offset;

        for (auto& space_collider : m_colliders)
        {
            if (&collider != space_collider && can_collide_with(collider, *space_collider))
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
