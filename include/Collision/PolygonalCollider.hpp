#pragma once

#include <clipper/clipper.hpp>
#include <SFML/Graphics.hpp>

#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitVector.hpp>
#include <Types/Identifiable.hpp>
#include <Types/Selectable.hpp>

namespace obe
{
    namespace Collision
    {
        bool pointsCompare(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt);
        double pointsDistance(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt);
        std::vector<ClipperLib::IntPoint*> convexHull(std::vector<ClipperLib::IntPoint*> points);
        int cross(ClipperLib::IntPoint* O, ClipperLib::IntPoint* A, ClipperLib::IntPoint* B);

        enum class ColliderTagType
        {
            Tag,
            Accepted,
            Rejected
        };

        class PolygonalCollider : public Transform::UnitBasedObject, public Types::Selectable, public Types::Identifiable
        {
        private:
            //Tag System
            std::vector<std::string> m_tags;
            std::vector<std::string> m_acceptedTags;
            std::vector<std::string> m_rejectedTags;

            ClipperLib::IntPoint m_masterPoint;
            ClipperLib::Path m_allPoints;

            std::vector<int> m_highlightedPoints;
            std::vector<int> m_highlightedLines;

            std::vector<PolygonalCollider*> m_originChildren;
            PolygonalCollider* m_origin = nullptr;
            std::string m_parentID = "";

            void calculateMasterPoint();
            std::vector<std::string>& retrieveTagVector(ColliderTagType tagType);
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
            double getSideAngle(int side);
            double getSideLength(int side);

            //Points
            int getPointsAmount() const;
            int getSideContainingPoint(int x, int y);
            int hasPoint(int x, int y, int toleranceX = 0, int toleranceY = 0);
            bool hasMasterPoint(int x, int y, int toleranceX = 0, int toleranceY = 0) const;
            void addPoint(int x, int y, int pointIndex = -1);
            void deletePoint(int pointIndex);
            double getDistanceFromPoint(int nodeIndex, int x, int y);
            int findClosestPoint(int x, int y, bool neighboor = false, std::vector<int> excludedNodes = std::vector<int>());
            ClipperLib::Path getAllPoints() const;

            //Collision Tests
            PolygonalCollider joinPolygonalColliders(std::string joinID, PolygonalCollider* other);
            bool testAllColliders(std::vector<PolygonalCollider*> collidersList, int offx, int offy, bool opt = false);
            std::vector<PolygonalCollider*> getAllCollidedColliders(std::vector<PolygonalCollider*> collidersList, int offx, int offy);
            bool doesCollide(PolygonalCollider* other, int offsetX = 0, int offsetY = 0);
            bool doesPathCollide(std::vector<PolygonalCollider*> others, int offsetX = 0, int offsetY = 0, int toX = 0, int toY = 0);
            bool doesCollideWithTags(std::vector<PolygonalCollider*> collidersList, std::vector<std::string> tags, int offx, int offy);
            std::vector<PolygonalCollider*> getCollidedCollidersWithTags(std::vector<PolygonalCollider*> collidersList, std::vector<std::string> tags, int offx, int offy);

            //Parent
            std::string getParentID() const;
            void setParentID(const std::string& parent);

            //Position
            ClipperLib::IntPoint getPosition();
            ClipperLib::IntPoint getPointPosition(int index);
            ClipperLib::IntPoint getPointRelativePosition(int index);
            ClipperLib::IntPoint getMasterPointPosition() const;

            Transform::UnitVector u_getPosition();
            Transform::UnitVector u_getPointPosition(int index);
            Transform::UnitVector u_getPointRelativePosition(int index);
            Transform::UnitVector u_getMasterPointPosition() const;

            void move(int x, int y);
            void setPosition(int x, int y);
            void setPositionFromMaster(int x, int y);
            void movePoint(int index, int x, int y);
            void setPointPosition(int index, int x, int y);
            void setPointRelativePosition(int index, int x, int y);
            void setPointPositionFromMaster(int index, int x, int y);

            void u_move(const Transform::UnitVector& vec);
            void u_setPosition(const Transform::UnitVector& vec);
            void u_setPositionFromMaster(const Transform::UnitVector& vec);
            void u_movePoint(int index, const Transform::UnitVector& vec);
            void u_setPointPosition(int index, const Transform::UnitVector& vec);
            void u_setPointRelativePosition(int index, const Transform::UnitVector& vec);
            void u_setPointPositionFromMaster(int index, const Transform::UnitVector& vec);

            //Origin
            void addOriginChild(PolygonalCollider* child);
            void removeOriginChild(PolygonalCollider* child, bool trigger = true);
            void clearOriginChildren();
            void setOrigin(PolygonalCollider* origin);
            PolygonalCollider* getOrigin() const;
            void removeOrigin();

            //Tags
            void addTag(ColliderTagType tagType, const std::string& tag);
            void clearTags(ColliderTagType tagType);
            void removeTag(ColliderTagType tagType, const std::string& tag);
            bool doesHaveTag(ColliderTagType tagType, const std::string& tag);
            bool doesHaveAnyTag(ColliderTagType tagType, const std::vector<std::string>& tags);
            std::vector<std::string> getAllTags(ColliderTagType tagType);

            //Debug
            void draw(sf::RenderWindow& target, int offsetX, int offsetY, bool drawLines = true, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
            void highlightPoint(int pointIndex);
            void highlightLine(int pointIndex);
            void clearHighlights(bool points = true, bool lines = true);
        };
    }
}
