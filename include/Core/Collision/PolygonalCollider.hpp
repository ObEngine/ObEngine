#pragma once

#include <Component/Component.hpp>
#include <Transform/Polygon.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitVector.hpp>
#include <Types/Selectable.hpp>
#include <Types/Serializable.hpp>
#include <unordered_map>

namespace obe::scene
{
    class Scene;
}

namespace obe::collision
{
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

    class PolygonalCollider;
    /**
    * \brief Struct containing data of a collision applied to a collider
    */
    class CollisionData
    {
    public:
        /**
         * \brief Colliders the collider touched during the collision (empty if no collision occurs)
         */
        std::vector<PolygonalCollider*> colliders;
        /**
         * \brief Maximum distance that can be traveled before collision
         */
        transform::UnitVector offset;
    };

    /**
     * \brief Class used for all Collisions in the engine, it's a Polygon
     * containing n points
     */
    class PolygonalCollider : public transform::Polygon,
                              public types::Selectable,
                              public component::Component<PolygonalCollider>
    {
    private:
        std::string m_parent_id = "";

        std::unordered_map<ColliderTagType, std::vector<std::string>> m_tags {
            { ColliderTagType::Tag, {} },
            { ColliderTagType::Accepted, {} },
            { ColliderTagType::Rejected, {} },
        };

        /*
        * \brief Cached bounding box, used for AABB filtering
        */
        mutable transform::Rect m_bounding_box;
        /*
        * \brief If true, the bounding box is recalculated at next get_bounding_box() call
        */
        mutable bool m_update_bounding_box = true;

        void reset_unit(transform::Units unit) override;
        [[nodiscard]] bool check_tags(const PolygonalCollider& collider) const;

    public:
        /**
         * \nobind
         */
        static constexpr std::string_view ComponentType = "PolygonalCollider";
        /**
         * \brief Constructs a PolygonalCollider
         * \param id Id of the PolygonalCollider (Used to retrieve it for
         *        example)
         */
        explicit PolygonalCollider(const std::string& id);
        explicit PolygonalCollider(const PolygonalCollider& collider);
        PolygonalCollider& operator=(const PolygonalCollider& collider);
        // Tags
        /**
         * \brief Adds a Tag to the Collider
         * \param tag_type List where you want to add the Tag (Tag / Accepted /
         *        Rejected)
         * \param tag Name of the Tag you want to add
         */
        void add_tag(ColliderTagType tag_type, const std::string& tag);

        /**
         * \brief Clears Tags of the Collider
         * \param tag_type List you want to clear (Tag / Accepted /Rejected)
         */
        void clear_tags(ColliderTagType tag_type);
        /**
         * \brief Checks if the collider is intersecting other colliders
         * \param offset The offset to apply to the source collider
         * \return CollisionData containing intersected colliders (offset doesn't change)
         */
        [[nodiscard]] CollisionData does_collide(const transform::UnitVector& offset) const;
        /**
         * \brief Checks if two polygons are intersecting
         * \param collider The other collider to test
         * \param offset The offset to apply to the source collider
         * \param perform_aabb_filter whether or not, the collider should perform a quick AABB filter before checking for full collision
         * \return true if the two polygons intersects, false otherwise
         */
        bool does_collide(PolygonalCollider& collider, const transform::UnitVector& offset,
            const bool perform_aabb_filter = true) const;
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
            ColliderTagType tag_type, const std::vector<std::string>& tags) const;
        /**
         * \brief Checks if the Collider contains a Tag
         * \param tag_type List from where you want to check the Tag existence
         *        (Tag / Accepted / Rejected)
         * \param tag Name of the Tag you want to
         *        check the existence
         * \return true if the Tag is found, false otherwise
         */
        bool contains_tag(ColliderTagType tag_type, const std::string& tag) const;
        /**
         * \brief Gets all the Tags from one of the Lists
         * \param tag_type List where you want to get all the Tags from (Tag /
         *        Accepted / Rejected)
         * \return A std::vector containing all the Tags of
         *         the chosen List
         */
        [[nodiscard]] std::vector<std::string> get_all_tags(ColliderTagType tag_type) const;
        /**
         * \brief Gets the Maximum distance before Collision in all the
         *        Colliders of the Scene
         * \param offset Distance the Collider should
         *        move to (if nothing collides)
         * \return CollisionData struct containing the other colliders that had been
         *         met and the maximum distance the collider can travel before colliding
         */
        [[nodiscard]] CollisionData get_distance_before_collision(
            const transform::UnitVector& offset) const;
        /**
         * \brief Gets the Maximum distance before Collision with a specific
         *        Collider
         * \param collider Collider to check the Collision with
         * \param offset Distance the Collider should move to (if nothing collides)
         * \return The maximum distance the Collider can travel before colliding
         */
        transform::UnitVector get_distance_before_collision(PolygonalCollider& collider,
            const transform::UnitVector& offset, const bool perform_aabb_filter = true) const;
        /**
         * \brief Get the Id of the parent of the Collider (When used in a
         *        GameObject) \return A std::string containing the Id of the parent of
         *        the Collider
         */
        [[nodiscard]] std::string get_parent_id() const;
        [[nodiscard]] vili::node schema() const override;
        /**
         * \brief Dumps the content of the PolygonalCollider
         * \return vili::node containing the PolygonalCollider details
         */
        vili::node dump() const override;
        /**
         * \brief Loads the PolygonalCollider from a ComplexNode
         * \param data ComplexNode containing the data of the PolygonalCollider
         */
        void load(const vili::node& data) override;
        /**
         * \brief Removes a Tag of the Collider
         * \param tag_type List you want to remove a Collider from (Tag /
         *        Accepted / Rejected) \param tag Name of the Tag you want to remove
         */
        void remove_tag(ColliderTagType tag_type, const std::string& tag);
        /**
         * \brief Set the Id of the parent of the Collider (When used in a
         *        GameObject)
         * \param parent A std::string containing the Id of the
         *        parent of the Collider
         */
        void set_parent_id(const std::string& parent);
        [[nodiscard]] std::string_view type() const override;
        /*
        * \brief Returns the cached bounding box. Recalculates it if necessary.
        */
        [[nodiscard]] transform::Rect get_bounding_box() const override;
        void add_point(const transform::UnitVector& position, int point_index = -1) override;
        void move(const transform::UnitVector& position) override;
        void rotate(float angle, transform::UnitVector origin) override;
        void set_position(const transform::UnitVector& position) override;
        void set_rotation(float angle, transform::UnitVector origin) override;
        void set_position_from_centroid(const transform::UnitVector& position) override;
    };
} // namespace obe::collision
