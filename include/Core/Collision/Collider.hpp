#pragma once

#include <unordered_set>

#include <cute/cute_c2.h>

#include <Transform/Rect.hpp>
#include <Types/SmartEnum.hpp>

namespace obe::collision
{
    class Collider;
    /**
     * \brief Enum used when manipulating tags in the Collider
     */
    enum class ColliderTagType
    {
        // Tags of the Collider
        Tag,
        // Tags the Collider should accept (Will reject when tag is not in accepted list)
        Accepted,
        // Tags the Collider should reject
        Rejected
    };
    using ColliderTagTypeMeta = types::SmartEnum<ColliderTagType>;


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
        std::unordered_set<std::string> m_tags;
        std::unordered_set<std::string> m_accepted_tags;
        std::unordered_set<std::string> m_rejected_tags;

    protected:
        const std::unordered_set<std::string>& get_tag_set(ColliderTagType tag_type) const;
        std::unordered_set<std::string>& get_tag_set(ColliderTagType tag_type);

        [[nodiscard]] virtual void* get_c2_shape() = 0;

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
         * \brief Adds a Tag to the Collider
         * \param tag_type List where you want to add the Tag (Tag / Accepted /
         *        Rejected)
         * \param tag Name of the Tag you want to add
         */
        void add_tag(ColliderTagType tag_type, const std::string& tag);
        /**
         * \brief Removes a Tag from the Collider
         * \param tag_type List where you want to add the Tag (Tag / Accepted /
         *        Rejected)
         * \param tag Name of the Tag you want to remove
         */
        void remove_tag(ColliderTagType tag_type, const std::string& tag);
        /**
         * \brief Clears Tags of the Collider
         * \param tag_type List you want to clear (Tag / Accepted /Rejected)
         */
        void clear_tags(ColliderTagType tag_type);
        /**
         * \brief Check if the Collider contains one of the Tag in parameter
         * \param tag_type List from where you want to check the Tags existence
         *        (Tag / Accepted / Rejected)
         * \param tags List of Tags you want to
         *        check the existence
         * \return true if at least one Tag has been found,
         *         false otherwise
         */
        [[nodiscard]] bool matches_any_tag(
            ColliderTagType tag_type, const std::unordered_set<std::string>& tags) const;
        /**
         * \brief Checks if the Collider contains a Tag
         * \param tag_type List from where you want to check the Tag existence
         *        (Tag / Accepted / Rejected)
         * \param tag Name of the Tag you want to
         *        check the existence
         * \return true if the Tag is found, false otherwise
         */
        [[nodiscard]] bool contains_tag(ColliderTagType tag_type, const std::string& tag) const;
        /**
         * \brief Gets all the Tags from one of the Lists
         * \param tag_type List where you want to get all the Tags from (Tag /
         *        Accepted / Rejected)
         * \return A std::vector containing all the Tags of
         *         the chosen List
         */
        [[nodiscard]] std::unordered_set<std::string> get_all_tags(ColliderTagType tag_type) const;

        /**
         * \brief Checks if two polygons are intersecting
         * \param collider The other collider to test
         * \param offset The offset to apply to the source collider
         * \return true if the two polygons intersects, false otherwise
         */
        [[nodiscard]] bool collides(
            const Collider& collider, const transform::UnitVector& offset) const;
        /**
         * \brief Gets the Maximum distance before Collision with a specific
         *        Collider
         * \param collider Collider to check the Collision with
         * \param offset Distance the Collider should move to (if nothing collides)
         * \return The maximum distance the Collider can travel before colliding
         */
        [[nodiscard]] transform::UnitVector get_offset_before_collision(
            const Collider& collider,
            const transform::UnitVector& offset) const;

        /*
         * \brief Returns the cached bounding box. Recalculates it if necessary.
         */
        [[nodiscard]] virtual transform::Rect get_bounding_box() const = 0;
    };
}
