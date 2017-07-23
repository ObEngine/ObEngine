#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitVector.hpp>
#include <Types/Identifiable.hpp>
#include <Types/Selectable.hpp>

namespace obe
{
    namespace Collision
    {
        bool pointsCompare(const Transform::UnitVector& first, const Transform::UnitVector& second);
        double pointsDistance(const Transform::UnitVector& first, const Transform::UnitVector& second);
        std::vector<Transform::UnitVector&> convexHull(std::vector<Transform::UnitVector&> points);
        double cross(const Transform::UnitVector& O, const Transform::UnitVector& A, const Transform::UnitVector& B);

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

        using PolygonPath = std::vector<Transform::UnitVector>;

        /**
         * \brief Class used for all Collisions in the engine, it's a Polygon containing n points
         * @Bind
         */
        class PolygonalCollider : public Transform::UnitBasedObject, public Types::Selectable, public Types::Identifiable
        {
        private:
            //Tag System
            std::vector<std::string> m_tags;
            std::vector<std::string> m_acceptedTags;
            std::vector<std::string> m_rejectedTags;

            Transform::UnitVector m_masterPoint;
            PolygonPath m_allPoints;

            std::vector<int> m_highlightedPoints;
            std::vector<int> m_highlightedLines;

            std::vector<PolygonalCollider*> m_originChildren;
            PolygonalCollider* m_origin = nullptr;
            std::string m_parentId = "";

            void calculateMasterPoint();
            std::vector<std::string>& retrieveTagVector(ColliderTagType tagType);
            void resetUnit(Transform::Units unit) override;
        public:
            /**
             * \brief Constructs a PolygonalCollider
             * \param id Id of the PolygonalCollider (Used to retrieve it for example)
             */
            explicit PolygonalCollider(const std::string& id);
            /**
             * \brief Destructor of PolygonalCollider, removes origins
             */
            ~PolygonalCollider();

            //Sides
            /**
             * \brief Get the angle of a side of the Polygon (0 to 360 degrees where 0 is the top)
             * \param side Index of the side you want to get the angle. \n
             *             For example index = 2 if the side from Point 2 to Point 3.
             * \return A double containing the side of the angle (From 0 to 360 degrees)
             */
            double getSideAngle(unsigned int side);
            /**
            * \brief Get the length of a side of the Polygon (Undefined Unit) <REVISION>
            * \param side Index of the side you want to get the length. \n
            *             For example index = 2 if the side from Point 2 to Point 3.
            * \return A double containing the length of the angle (Undefined Unit)
            */
            double getSideLength(unsigned int side);

            //Points
            /**
             * \brief Get the number of points in the Polygon
             * \return An unsigned int containing the number of points of the Polygon
             */
            unsigned int getPointsAmount() const;
            /**
             * \brief Get if the Position (x, y) is on one of the side of the Polygon
             * \param position Coordinate of the Position to test
             * \return An unsigned int containing the index of the side containing the position or -1 if not found
             */
            int getSideContainingPoint(const Transform::UnitVector& position);
            /**
             * \brief Check if a point of the Polygon is on Position (x - tolerance <= x <= x + tolerance, y - tolerance <= tolerance <= y + tolerance)
             * \param position Coordinate of the Position to test
             * \param tolerance Position tolerance, bigger number means less precise
             * \return An unsigned int containing the index of the point containing the position or -1 if not found
             */
            int hasPoint(const Transform::UnitVector& position, const Transform::UnitVector& tolerance);
            /**
             * \brief Check if the MasterPoint of the Polygon is on Position (x - tolerance <= x <= x + tolerance, y - tolerance <= tolerance <= y + tolerance)
             * \param position Coordinate of the Position to test
             * \param tolerance Position tolerance, bigger number means less precise
             * \return true if the MasterPoint is on the given Positon, false otherwise
             */
            bool hasMasterPoint(const Transform::UnitVector& position, const Transform::UnitVector& tolerance) const;
            /**
             * \brief Adds a new Point to the Polygon at Position (x, y)
             * \param point Coordinate of the Position where to add the new Point
             * \param pointIndex Index where to insert the new Point, Use pointIndex = -1 <DefaultArg> to insert at the end (between last and first Point)
             */
            void addPoint(const Transform::UnitVector& point, int pointIndex = -1);
            /**
             * \brief Deletes a Point of the Polygon
             * \param pointIndex Index of the Point to delete
             */
            void deletePoint(unsigned int pointIndex);
            /**
             * \brief Get the distance between a Point of the Polygon and the given Position(x, y)
             * \param pointIndex Index of the Point used to calculate the distance
             * \param position Coordinate of the Position used to calculate the distance
             * \return Distance between the given Position and the Point of the Polygon
             */
            double getDistanceFromPoint(unsigned int pointIndex, const Transform::UnitVector& position);
            /**
             * \brief Find the closest Point from the given Position(x, y)
             * \param position Coordinate of the Position used to get the closest Point
             * \param neighboor Get the closest neighboor of the closest Point instead of the Point
             * \param excludedPoints A std::vector containing points you want to exclude from the calculus (Not used in neighboor check step)
             * \return The index of the Point (or one of its neighboor) that is the closest one of the given Position
             */
            unsigned int findClosestPoint(const Transform::UnitVector& position, bool neighboor = false, std::vector<int> excludedPoints = {});
            unsigned int findClosestLine(const Transform::UnitVector& position);
            /**
             * \brief Get all the Points of the Polygon
             * \return A Path containing all the Points of the Polygon
             */
            PolygonPath getAllPoints() const;

            //Collision Tests
            //PolygonalCollider joinPolygonalColliders(std::string joinID, PolygonalCollider* other) const;

            Transform::UnitVector getMaximumDistanceBeforeCollision(const PolygonalCollider& collider, const Transform::UnitVector& offset) const;
            /**
             * \brief Checks if two polygons are intersecting
             * \param collider The other collider to test
             * \param offset The offset to apply to the source collider
             * \return true if the two polygons intersects, false otherwise
             */
            bool doesCollide(const PolygonalCollider& collider, const Transform::UnitVector& offset) const;

            //Parent
            /**
             * \brief Get the Id of the parent of the Collider (When used in a GameObject)
             * \return A std::string containing the Id of the parent of the Collider
             */
            std::string getParentId() const;
            /**
             * \brief Set the Id of the parent of the Collider (When used in a GameObject)
             * \param parent A std::string containing the Id of the parent of the Collider
             */
            void setParentId(const std::string& parent);

            //Position
            /**
             * \brief Get the Position of the first point (index 0) of the Polygon
             * \return An UnitVector containing the position of the first point of the Polygon
             */
            Transform::UnitVector getPosition();
            /**
             * \brief Get the Position of one of the points of the Polygon
             * \param index Index of the point to get the position
             * \return An UnitVector containing the position of one of the points of the Polygon
             */
            Transform::UnitVector getPointPosition(unsigned int index);
            /**
             * \brief Get the Position of one of the points of the Polygon relative to the Position of the point at index 0
             * \param index Index of the point to get the relative position
             * \return An UnitVector containing the position of one of the points of the Polygon relative to the Position of the point at index 0
             */
            Transform::UnitVector getPointRelativePosition(unsigned int index);
            /**
             * \brief Get the position of the Master Point (centroid) of the Polygon
             * \return An UnitVector containing the position of the Master Point (centroid) of the Polygon
             */
            Transform::UnitVector getMasterPointPosition() const;

            /**
             * \brief Moves the Polygon (relative to the current position)
             * \param vec UnitVector containing the offset to move the Polygon
             */
            void move(const Transform::UnitVector& vec);
            /**
             * \brief Sets the new position of the Polygon (using the point at index 0)
             * \param vec UnitVector containing the new Position of the Polygon
             */
            void setPosition(const Transform::UnitVector& vec);
            /**
             * \brief Sets the new position of the Polygon (using the centroid)
             * \param vec UnitVector containing the new Position of the Polygon
             */
            void setPositionFromMaster(const Transform::UnitVector& vec);
            /**
             * \brief Moves one of the points of the Polygons
             * \param index Index of the point to move
             * \param vec UnitVector containing the offset to move the point of the Polygon
             */
            void movePoint(unsigned int index, const Transform::UnitVector& vec);
            /**
             * \brief Sets the new Position of one of the points of the Polygon
             * \param index Index of the point to set the position
             * \param vec UnitVector containing the new position of the point
             */
            void setPointPosition(unsigned int index, const Transform::UnitVector& vec);
            /**
             * \brief Sets the position of one of the points of the Polygon relative to the Position of the point at index 0
             * \param index Index of the point to set the position
             * \param vec UnitVector containing the new position of one of the points of the Polygon relative to the Position of the point at index 0
             */
            void setPointRelativePosition(unsigned int index, const Transform::UnitVector& vec);
            /**
            * \brief Sets the position of one of the points of the Polygon relative to the Position of the centroid
            * \param index Index of the point to set the position
            * \param vec UnitVector containing the new position of one of the points of the Polygon relative to the Position of the centroid
            */
            void setPointPositionFromMaster(unsigned int index, const Transform::UnitVector& vec);

            //Origin
            /**
             * \brief Adds a new child which will take the Collider as origin
             * \param child The new child to add
             */
            void addOriginChild(PolygonalCollider* child);
            /**
             * \brief Removes a child Collider which use the current one as origin
             * \param child Adress of the child to remove
             * \param trigger Anti infinite recursion boolean
             */
            void removeOriginChild(PolygonalCollider* child, bool trigger = true);
            /**
             * \brief Removes all children of the Collider
             */
            void clearOriginChildren();
            /**
             * \brief Set a new origin for the Collider
             * \param origin Adress of the Collider you want to use as origin
             */
            void setOrigin(PolygonalCollider* origin);
            /**
             * \brief Get the origin of the Collider
             * \return Adress of the Collider used as origin
             */
            PolygonalCollider* getOrigin() const;
            /**
             * \brief Removes the origin reference of the Collider
             */
            void removeOrigin();

            //Tags
            /**
             * \brief Adds a Tag to the Collider
             * \param tagType List where you want to add the Tag (Tag / Accepted / Rejected)
             * \param tag Name of the Tag you want to add
             */
            void addTag(ColliderTagType tagType, const std::string& tag);
            /**
             * \brief Clears Tags of the Collider
             * \param tagType List you want to clear (Tag / Accepted /Rejected)
             */
            void clearTags(ColliderTagType tagType);
            /**
             * \brief Removes a Tag of the Collider
             * \param tagType List you want to remove a Collider from (Tag / Accepted / Rejected)
             * \param tag Name of the Tag you want to remove
             */
            void removeTag(ColliderTagType tagType, const std::string& tag);
            /**
             * \brief Checks if the Collider contains a Tag
             * \param tagType List from where you want to check the Tag existence (Tag / Accepted / Rejected)
             * \param tag Name of the Tag you want to check the existence
             * \return true if the Tag is found, false otherwise
             */
            bool doesHaveTag(ColliderTagType tagType, const std::string& tag);
            /**
             * \brief Check if the Collider contains one of the Tag in parameter
             * \param tagType List from where you want to check the Tags existence (Tag / Accepted / Rejected)
             * \param tags List of Tags you want to check the existence
             * \return true if at least one Tag has been found, false otherwise
             */
            bool doesHaveAnyTag(ColliderTagType tagType, const std::vector<std::string>& tags);
            /**
             * \brief Gets all the Tags from one of the Lists
             * \param tagType List where you want to get all the Tags from (Tag / Accepted / Rejected)
             * \return A std::vector containing all the Tags of the chosen List
             */
            std::vector<std::string> getAllTags(ColliderTagType tagType);

            //Debug
            /**
             * \brief Draws the Polygon on the screen
             * \param target sf::RenderWindow you want to draw the Polygon to
             * \param offsetX x Coordinate of the Offset of the Camera
             * \param offsetY y Coordinate of the Offset of the Camera
             * \param drawLines Draws the lines of the Polygon or not
             * \param drawPoints Draws the points of the Polygon or not
             * \param drawMasterPoint Draws the MasterPoint of the Polygon or not
             * \param drawSkel Draws the Skeleton (Lines to MasterPoint) of the Polygon or not
             */
            void draw(sf::RenderWindow& target, int offsetX, int offsetY, bool drawLines = true, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
            /**
             * \brief Highlight a Point of the Polygon (Changes its color when the Polygon is drawn)
             * \param pointIndex Index of the Point to highlight
             */
            void highlightPoint(unsigned int pointIndex);
            /**
            * \brief Highlight a Side of the Polygon (Changes its color when the Polygon is drawn)
            * \param pointIndex Index of the Side to highlight
            */
            void highlightLine(unsigned int pointIndex);
            /**
             * \brief Removes all Highlights
             * \param points Resets Points Highlights ?
             * \param lines Resets Lines Highlights ?
             */
            void clearHighlights(bool points = true, bool lines = true);
        };
    }
}
