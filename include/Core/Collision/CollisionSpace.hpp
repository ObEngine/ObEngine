#pragma once

#include <unordered_map>

#include <Collision/Collider.hpp>
#include <Collision/Quadtree.hpp>

namespace obe::collision
{
    struct CollisionRejectionPair
    {
        const Collider* collider1 = nullptr;
        const Collider* collider2 = nullptr;

        bool operator()(CollisionRejectionPair const* lhs, CollisionRejectionPair const* rhs) const
        {
            return lhs->collider1 == rhs->collider1 && lhs->collider2 == rhs->collider2;
        }
    };

    struct ReachableCollider
    {
        const Collider* collider;
        transform::UnitVector offset;
    };

    class CollisionSpace
    {
    private:
        std::unordered_set<const Collider*> m_colliders;
        std::unordered_map<std::string, std::unordered_set<std::string>> m_tags_blacklists;
        Quadtree m_quadtree;

    protected:
        static bool matches_any_tag(const std::unordered_set<std::string>& input_tags,
            const std::unordered_set<std::string>& whitelist_or_blacklist);
        bool can_collide_with(const Collider& collider1, const Collider& collider2,
            bool check_both_directions = true) const;

    public:
        CollisionSpace();

        /**
         * \brief Adds a Collider in the CollisionSpace
         * \param collider Pointer to the collider to add to the CollisionSpace
         */
        void add_collider(const Collider* collider);
        /**
         * \brief Get how many Colliders are present in the Scene
         * \return The amount of Colliders present in the Scene
         */
        [[nodiscard]] std::size_t get_collider_amount() const;
        /**
         * \brief Get all the pointers of the Colliders in the Scene
         * \return A std::vector containing all the pointers of the Colliders
         *         present in the Scene
         */
        [[nodiscard]] std::unordered_set<const Collider*> get_all_colliders() const;
        /**
         * \brief Removes the Collider with the given Id from the Scene
         * \param collider Pointer to the collider to remove from the CollisionSpace
         */
        void remove_collider(const Collider* collider);
        void refresh_collider(const Collider* collider);

        void refresh_quadtree();

        [[nodiscard]] bool collides(const Collider& collider) const;
        [[nodiscard]] transform::UnitVector get_offset_before_collision(const Collider& collider,
            const transform::UnitVector& offset = transform::UnitVector(0, 0)) const;
        [[nodiscard]] transform::UnitVector get_offset_before_collision(const Collider& collider,
            const std::vector<ReachableCollider>& reachable_colliders,
            const transform::UnitVector& offset = transform::UnitVector(0, 0)) const;
        std::vector<ReachableCollider> get_reachable_colliders(const Collider& collider,
            const transform::UnitVector& offset = transform::UnitVector(0, 0)) const;

        void add_tag_to_blacklist(const std::string& source_tag, const std::string& rejected_tag);
        void remove_tag_to_blacklist(
            const std::string& source_tag, const std::string& rejected_tag);
        void clear_blacklist(const std::string& source_tag);
        [[nodiscard]] const std::unordered_set<std::string>& get_blacklist(
            const std::string& source_tag) const;
    };
}
