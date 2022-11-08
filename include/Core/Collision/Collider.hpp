#pragma once

#include <unordered_set>

#include <cute/cute_c2.h>

#include <Transform/AABB.hpp>
#include <Types/SmartEnum.hpp>

namespace obe::collision
{
    class Collider;

    /**
     * \brief Struct containing data of a collision applied to a collider
     */
    class CollisionData
    {
    public:
        /**
     * \brief Colliders the collider touched during the collision (empty if no collision occurs)
     */
        std::vector<Collider*> colliders;
        /**
     * \brief Maximum distance that can be traveled before collision
     */
        transform::UnitVector offset;
    };

    enum class ColliderType
    {
        Collider,
        Circle,
        Rectangle,
        Capsule,
        Polygon,
    };
    using ColliderTypeMeta = types::SmartEnum<ColliderType>;

    C2_TYPE collider_type_to_c2type(ColliderType collider_type);

    /**
     * \brief Class used for all Collisions in the engine, it's a Polygon
     * containing n points
     */
    class Collider : public transform::Movable
    {
    private:
        std::string m_tag;

        friend class CollisionSpace;

    protected:
        [[nodiscard]] virtual const void* get_c2_shape() const = 0;
        [[nodiscard]] virtual const c2x* get_c2_space_transform() const = 0;

    public:
        /**
         * \nobind
         */
        static constexpr ColliderType Type = ColliderType::Collider;
        [[nodiscard]] virtual ColliderType get_collider_type() const;

        Collider() = default;
        explicit Collider(const transform::UnitVector& position);
        ~Collider() override = default;

        // Tags
        /**
         * \brief Sets a Tag to the Collider
         * \param tag Name of the Tag you want to set to the collider
         */
        void set_tag(const std::string& tag);
        /**
         * \brief Gets all the Tags from one of the Lists)
         * \return A std::vector containing all the Tags of
         *         the chosen List
         */
        [[nodiscard]] std::string get_tag() const;

        /**
         * \brief Checks if two polygons are intersecting
         * \param collider The other collider to test
         * \param offset The offset to apply to the source collider
         * \return true if the two polygons intersects, false otherwise
         */
        [[nodiscard]] bool collides(const Collider& collider) const;
        /**
         * \brief Gets the Maximum distance before Collision with a specific
         *        Collider
         * \param collider Collider to check the Collision with
         * \param offset Distance the Collider should move to (if nothing collides)
         * \return The maximum distance the Collider can travel before colliding
         */
        [[nodiscard]] transform::UnitVector get_offset_before_collision(const Collider& collider,
            const transform::UnitVector& self_offset = transform::UnitVector(0, 0),
            const transform::UnitVector& other_offset = transform::UnitVector(0, 0)) const;

        /*
         * \brief Returns the cached bounding box. Recalculates it if necessary.
         */
        [[nodiscard]] virtual transform::AABB get_bounding_box() const = 0;

        [[nodiscard]] std::unique_ptr<Collider> copy() const;
    };
}
