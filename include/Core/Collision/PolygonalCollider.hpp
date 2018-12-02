#pragma once

#include <Component/Component.hpp>
#include <Scene/Camera.hpp>
#include <Script/GlobalState.hpp>
#include <Transform/Polygon.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitVector.hpp>
#include <Types/Selectable.hpp>
#include <Types/Serializable.hpp>

#include <SFML/Graphics/Color.hpp>

namespace obe::Scene
{
    class Scene;
}

namespace obe::Collision
{
    std::vector<Transform::UnitVector&> convexHull(std::vector<Transform::UnitVector&> points);
    double cross(const Transform::UnitVector& O, const Transform::UnitVector& A, const Transform::UnitVector& B);
    bool pointsCompare(const Transform::UnitVector& first, const Transform::UnitVector& second);
    double pointsDistance(const Transform::UnitVector& first, const Transform::UnitVector& second);

    /**
    * \brief Enum used when manipulating tags in the Collider
    */
    enum class ColliderTagType
    {
        /**
        * \brief Tags of the Collider
        */
        Tag,
        /**
        * \brief Tags the Collider should accept (Will reject when tag is not in accepted list)
        */
        Accepted,
        /**
        * \brief Tags the Collider should reject
        */
        Rejected
    };

    /**
    * \brief Class used for all Collisions in the engine, it's a Polygon containing n points
    * @Bind
    */
    class PolygonalCollider :
        public Transform::Polygon,
        public Types::Selectable,
        public Component::Component<PolygonalCollider>
    {
    private:
        static std::map<std::string, sf::Color> TagsColor;
        sf::Color getTagColor();

        std::vector<std::string> m_acceptedTags;
        std::vector<int> m_highlightedLines;
        std::vector<int> m_highlightedPoints;
        PolygonalCollider* m_origin = nullptr;
        std::vector<PolygonalCollider*> m_originChildren;
        std::string m_parentId = "";
        std::vector<std::string> m_rejectedTags;
        std::vector<std::string> m_tags;

        void resetUnit(Transform::Units unit) override;
        std::vector<std::string> retrieveTagVector(ColliderTagType tagType) const;
        std::vector<std::string>& retrieveTagVector(ColliderTagType tagType);
    public:
        static constexpr std::string_view ComponentType = "PolygonalCollider";
        static void SetTagColor(const std::string& tag, sf::Color color);
        /**
        * \brief Constructs a PolygonalCollider
        * \param id Id of the PolygonalCollider (Used to retrieve it for example)
        */
        explicit PolygonalCollider(const std::string& id);
        /**
        * \brief Adds a new child which will take the Collider as origin
        * \param child The new child to add
        */
        void addOriginChild(PolygonalCollider* child);
        //Tags
        /**
        * \brief Adds a Tag to the Collider
        * \param tagType List where you want to add the Tag (Tag / Accepted / Rejected)
        * \param tag Name of the Tag you want to add
        */
        void addTag(ColliderTagType tagType, const std::string& tag);
        /**
        * \brief Removes all Highlights
        * \param points Resets Points Highlights ?
        * \param lines Resets Lines Highlights ?
        */
        void clearHighlights(bool points = true, bool lines = true);
        /**
        * \brief Removes all children of the Collider
        */
        void clearOriginChildren();
        /**
        * \brief Clears Tags of the Collider
        * \param tagType List you want to clear (Tag / Accepted /Rejected)
        */
        void clearTags(ColliderTagType tagType);
        bool doesCollide(const Transform::UnitVector& offset) const;
        /**
        * \brief Checks if two polygons are intersecting
        * \param collider The other collider to test
        * \param offset The offset to apply to the source collider
        * \return true if the two polygons intersects, false otherwise
        */
        bool doesCollide(PolygonalCollider& collider, const Transform::UnitVector& offset) const;
        /**
        * \brief Check if the Collider contains one of the Tag in parameter
        * \param tagType List from where you want to check the Tags existence (Tag / Accepted / Rejected)
        * \param tags List of Tags you want to check the existence
        * \return true if at least one Tag has been found, false otherwise
        */
        bool doesHaveAnyTag(ColliderTagType tagType, const std::vector<std::string>& tags) const;
        /**
        * \brief Checks if the Collider contains a Tag
        * \param tagType List from where you want to check the Tag existence (Tag / Accepted / Rejected)
        * \param tag Name of the Tag you want to check the existence
        * \return true if the Tag is found, false otherwise
        */
        bool doesHaveTag(ColliderTagType tagType, const std::string& tag);
        /**
        * \brief Draws the Polygon on the screen
        * \param camera Camera of the Scene (used for draw offset)
        * \param drawLines Draws the lines of the Polygon or not
        * \param drawPoints Draws the points of the Polygon or not
        * \param drawMasterPoint Draws the MasterPoint of the Polygon or not
        * \param drawSkel Draws the Skeleton (Lines to MasterPoint) of the Polygon or not
        */
        void draw(Scene::Camera& camera, bool drawLines = true, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
        /**
        * \brief Dumps the content of the PolygonalCollider to a ComplexNode
        * \param target ComplexNode where to serialize the PolygonalCollider
        */
        void dump(vili::ComplexNode& target) const override;
        /**
        * \brief Gets all the Tags from one of the Lists
        * \param tagType List where you want to get all the Tags from (Tag / Accepted / Rejected)
        * \return A std::vector containing all the Tags of the chosen List
        */
        std::vector<std::string> getAllTags(ColliderTagType tagType) const;
        /**
        * \brief Gets the Maximum distance before Collision in all the Colliders of the Scene
        * \param offset Distance the Collider should move to (if nothing collides)
        * \return The maximum distance the Collider can travel before colliding
        */
        Transform::UnitVector getMaximumDistanceBeforeCollision(const Transform::UnitVector& offset) const;
        /**
        * \brief Gets the Maximum distance before Collision with a specific Collider
        * \param collider Collider to check the Collsion with
        * \param offset Distance the Collider should move to (if nothing collides)
        * \return The maximum distance the Collider can travel before colliding
        */
        Transform::UnitVector getMaximumDistanceBeforeCollision(PolygonalCollider& collider, const Transform::UnitVector& offset) const;
        /**
        * \brief Get the origin of the Collider
        * \return Adress of the Collider used as origin
        */
        PolygonalCollider* getOrigin() const;
        /**
        * \brief Get the Id of the parent of the Collider (When used in a GameObject)
        * \return A std::string containing the Id of the parent of the Collider
        */
        std::string getParentId() const;
        /**
        * \brief Highlight a Side of the Polygon (Changes its color when the Polygon is drawn)
        * \param pointIndex Index of the Side to highlight
        */
        void highlightLine(unsigned int pointIndex);
        /**
        * \brief Highlight a Point of the Polygon (Changes its color when the Polygon is drawn)
        * \param pointIndex Index of the Point to highlight
        */
        void highlightPoint(unsigned int pointIndex);
        //PolygonalCollider joinPolygonalColliders(std::string joinID, PolygonalCollider* other) const;
        /**
        * \brief Loads the PolygonalCollider from a ComplexNode
        * \param data ComplexNode containing the data of the PolygonalCollider
        */
        void load(vili::ComplexNode& data) override;
        /**
        * \brief Removes the origin reference of the Collider
        */
        void removeOrigin();
        /**
        * \brief Removes a child Collider which use the current one as origin
        * \param child Adress of the child to remove
        * \param trigger Anti infinite recursion boolean
        */
        void removeOriginChild(PolygonalCollider* child, bool trigger = true);
        /**
        * \brief Removes a Tag of the Collider
        * \param tagType List you want to remove a Collider from (Tag / Accepted / Rejected)
        * \param tag Name of the Tag you want to remove
        */
        void removeTag(ColliderTagType tagType, const std::string& tag);
        /**
        * \brief Set a new origin for the Collider
        * \param origin Adress of the Collider you want to use as origin
        */
        void setOrigin(PolygonalCollider* origin);
        /**
        * \brief Set the Id of the parent of the Collider (When used in a GameObject)
        * \param parent A std::string containing the Id of the parent of the Collider
        */
        void setParentId(const std::string& parent);
        bool checkTags(const PolygonalCollider& collider) const;
        /**
        * \brief Destructor of PolygonalCollider, removes origins
        */
        ~PolygonalCollider();

        std::string_view type() const override;
    };
}