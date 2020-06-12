#pragma once

#include <unordered_map>

#include <Component/Component.hpp>
#include <Transform/Polygon.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitVector.hpp>
#include <Types/Selectable.hpp>
#include <Types/Serializable.hpp>

namespace obe::Scene
{
    class Scene;
}

namespace obe::Collision
{
    /**
     * \brief Enum used when manipulating tags in the Collider
     * \bind{ColliderTagType}
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

    class PolygonalCollider;
    /**
    * \brief Struct containing data of a collision applied to a collider
    * \bind{CollisionData}
    */
    class CollisionData
    {
    public:
        /**
         * \briefColliders the collider touched during the collision (empty if no collision occurs)
         */
        std::vector<PolygonalCollider*> colliders;
        /**
         * \brief Maximum distance that can be traveled before collision
         */
        Transform::UnitVector offset;
    };

    /**
     * \brief Class used for all Collisions in the engine, it's a Polygon
     * containing n points
     * \bind{PolygonalCollider}
     */
    class PolygonalCollider : public Transform::Polygon,
                              public Types::Selectable,
                              public Component::Component<PolygonalCollider>
    {
    private:
        std::string m_parentId = "";

        std::unordered_map<ColliderTagType, std::vector<std::string>> m_tags {
            { ColliderTagType::Tag, {} },
            { ColliderTagType::Accepted, {} },
            { ColliderTagType::Rejected, {} },
        };

        void resetUnit(Transform::Units unit) override;
        [[nodiscard]] bool checkTags(const PolygonalCollider& collider) const;

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
        // Tags
        /**
         * \brief Adds a Tag to the Collider
         * \param tagType List where you want to add the Tag (Tag / Accepted /
         *        Rejected)
         * \param tag Name of the Tag you want to add
         */
        void addTag(ColliderTagType tagType, const std::string& tag);

        /**
         * \brief Clears Tags of the Collider
         * \param tagType List you want to clear (Tag / Accepted /Rejected)
         */
        void clearTags(ColliderTagType tagType);
        /**
         * \brief Checks if the collider is intersecting other colliders
         * \param offset The offset to apply to the source collider
         * \return CollisionData containing intersected colliders (offset doesn't change)
         */
        [[nodiscard]] CollisionData doesCollide(
            const Transform::UnitVector& offset) const;
        /**
         * \brief Checks if two polygons are intersecting
         * \param collider The other collider to test
         * \param offset The offset to apply to the source collider
         * \return true if the two polygons intersects, false otherwise
         */
        bool doesCollide(
            PolygonalCollider& collider, const Transform::UnitVector& offset) const;
        /**
         * \brief Check if the Collider contains one of the Tag in parameter
         * \param tagType List from where you want to check the Tags existence
         *        (Tag / Accepted / Rejected)
         * \param tags List of Tags you want to
         *        check the existence
         * \return true if at least one Tag has been found,
         *         false otherwise
         */
        [[nodiscard]] bool doesHaveAnyTag(
            ColliderTagType tagType, const std::vector<std::string>& tags) const;
        /**
         * \brief Checks if the Collider contains a Tag
         * \param tagType List from where you want to check the Tag existence
         *        (Tag / Accepted / Rejected)
         * \param tag Name of the Tag you want to
         *        check the existence
         * \return true if the Tag is found, false otherwise
         */
        bool doesHaveTag(ColliderTagType tagType, const std::string& tag);
        /**
         * \brief Dumps the content of the PolygonalCollider to a ComplexNode
         * \param target ComplexNode where to serialize the PolygonalCollider
         */
        vili::node dump() const override;
        /**
         * \brief Gets all the Tags from one of the Lists
         * \param tagType List where you want to get all the Tags from (Tag /
         *        Accepted / Rejected)
         * \return A std::vector containing all the Tags of
         *         the chosen List
         */
        [[nodiscard]] std::vector<std::string> getAllTags(ColliderTagType tagType) const;
        /**
         * \brief Gets the Maximum distance before Collision in all the
         *        Colliders of the Scene
         * \param offset Distance the Collider should
         *        move to (if nothing collides)
         * \return CollisionData struct containing the other colliders that had been
         *         met and the maximum distance the collider can travel before colliding
         */
        [[nodiscard]] CollisionData getMaximumDistanceBeforeCollision(
            const Transform::UnitVector& offset) const;
        /**
         * \brief Gets the Maximum distance before Collision with a specific
         *        Collider
         * \param collider Collider to check the Collision with
         * \param offset Distance the Collider should move to (if nothing collides)
         * \return The maximum distance the Collider can travel before colliding
         */
        Transform::UnitVector getMaximumDistanceBeforeCollision(
            PolygonalCollider& collider, const Transform::UnitVector& offset) const;
        /**
         * \brief Get the Id of the parent of the Collider (When used in a
         *        GameObject) \return A std::string containing the Id of the parent of
         *        the Collider
         */
        [[nodiscard]] std::string getParentId() const;
        /**
         * \brief Loads the PolygonalCollider from a ComplexNode
         * \param data ComplexNode containing the data of the PolygonalCollider
         */
        void load(vili::node& data) override;
        /**
         * \brief Removes a Tag of the Collider
         * \param tagType List you want to remove a Collider from (Tag /
         *        Accepted / Rejected) \param tag Name of the Tag you want to remove
         */
        void removeTag(ColliderTagType tagType, const std::string& tag);
        /**
         * \brief Set the Id of the parent of the Collider (When used in a
         *        GameObject)
         * \param parent A std::string containing the Id of the
         *        parent of the Collider
         */
        void setParentId(const std::string& parent);
        [[nodiscard]] std::string_view type() const override;
    };
} // namespace obe::Collision