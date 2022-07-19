#pragma once

#include <Collision/Collider.hpp>

namespace obe::collision
{
    class CollisionSpace
    {
    private:
        std::unordered_set<Collider*> m_colliders;
    public:
        CollisionSpace() = default;

        /**
         * \brief Adds a Collider in the CollisionSpace
         * \param collider Pointer to the collider to add to the CollisionSpace
         */
        void add_collider(Collider* collider);
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
        [[nodiscard]] std::unordered_set<Collider*> get_all_colliders() const;
        /**
         * \brief Removes the Collider with the given Id from the Scene
         * \param collider Pointer to the collider to remove from the CollisionSpace
         */
        void remove_collider(Collider* collider);

        [[nodiscard]] bool collides(const Collider& collider) const;
        [[nodiscard]] transform::UnitVector get_offset_before_collision(const Collider& collider,
            const transform::UnitVector& offset = transform::UnitVector(0, 0)) const;
    };
}
