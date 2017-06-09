//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <clipper/clipper.hpp>

#include "Functions.hpp"


namespace obe
{
    namespace Collision
    {
        void drawLine(sf::RenderWindow* surf, int x1, int y1, int x2, int y2, int w = 2, sf::Color col1 = sf::Color(255, 255, 255));
        bool pointsCompare(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt);
        double pointsDistance(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt);
        std::vector<ClipperLib::IntPoint*> convexHull(std::vector<ClipperLib::IntPoint*> points);
        int cross(ClipperLib::IntPoint* O, ClipperLib::IntPoint* A, ClipperLib::IntPoint* B);

        class PolygonalCollider : public Coord::UnitBasedObject //Polygon with collision methods
        {
        private:
            std::string m_id;
            std::vector<std::string> m_excludedIds;
            std::vector<std::string> m_acceptedIds;

            //Tag System
            std::vector<std::string> m_tags;
            std::vector<std::string> m_excludedTags;
            std::vector<std::string> m_acceptedTags; //If not empty, will only accept tags from this

            int m_drawOffsetX = 0;
            int m_drawOffsetY = 0;
            long long int m_boundingLeft = 0;
            long long int m_boundingTop = 0;
            long long int m_boundingRight = 0;
            long long int m_boundingBottom = 0;
            ClipperLib::IntPoint m_masterPoint;
            ClipperLib::Path m_allPoints;
            sf::ConvexShape m_drawShape;

            bool m_selected = false;
            std::vector<int> m_highlightedPoints;
            std::vector<int> m_highlightedLines;

            std::vector<PolygonalCollider*> m_originChildren;
            PolygonalCollider* m_origin = nullptr;
            std::string m_parentID = "";

            void calculateMasterPoint();
        public:
            explicit PolygonalCollider(std::string id);
            ~PolygonalCollider();
            std::string getID() const;

            //Sides
            double getSideAngle(int side);
            double getSideLength(int side);
            //Selection
            void setSelected(bool sel);
            bool getSelected() const;
            //Points
            int getPointsAmount() const;
            int getSideContainingPoint(int x, int y);
            bool isPointInBoundingBox(int x, int y) const;
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
            //Parent
            std::string getParentID() const;
            void setParentID(std::string parent);
            //Position
            ClipperLib::IntPoint getPosition();
            ClipperLib::IntPoint getPointPosition(int index);
            ClipperLib::IntPoint getPointRelativePosition(int index);
            ClipperLib::IntPoint getMasterPointPosition() const;

            Coord::UnitVector u_getPosition();
            Coord::UnitVector u_getPointPosition(int index);
            Coord::UnitVector u_getPointRelativePosition(int index);
            Coord::UnitVector u_getMasterPointPosition() const;

            void move(int x, int y);
            void setPosition(int x, int y);
            void setPositionFromMaster(int x, int y);
            void movePoint(int index, int x, int y);
            void setPointPosition(int index, int x, int y);
            void setPointRelativePosition(int index, int x, int y);
            void setPointPositionFromMaster(int index, int x, int y);

            void u_move(const Coord::UnitVector& vec);
            void u_setPosition(const Coord::UnitVector& vec);
            void u_setPositionFromMaster(const Coord::UnitVector& vec);
            void u_movePoint(int index, const Coord::UnitVector& vec);
            void u_setPointPosition(int index, const Coord::UnitVector& vec);
            void u_setPointRelativePosition(int index, const Coord::UnitVector& vec);
            void u_setPointPositionFromMaster(int index, const Coord::UnitVector& vec);

            //Origin
            void addOriginChild(PolygonalCollider* child);
            void removeOriginChild(PolygonalCollider* child, bool trigger = true);
            void clearOriginChildren();
            void setOrigin(PolygonalCollider* origin);
            PolygonalCollider* getOrigin() const;
            void removeOrigin();
            //Tags
            void addTag(std::string tag);
            void addExcludedTag(std::string tag);
            void addAcceptedTag(std::string tag);
            void clearTags();
            void clearExcludedTags();
            void clearAcceptedTags();
            void removeTag(std::string tag);
            void removeExcludedTag(std::string tag);
            void removeAcceptedTag(std::string tag);
            bool doesHaveTag(std::string tag) const;
            bool isTagExcluded(std::string tag) const;
            bool isTagAccepted(std::string tag) const;
            bool doesHaveAnyTag(std::vector<std::string>* tags) const;
            bool isATagExcluded(std::vector<std::string>* tags) const;
            bool isATagAccepted(std::vector<std::string>* tags) const;
            std::vector<std::string>* getAllTags();
            std::vector<std::string>* getAllExcludedTags();
            std::vector<std::string>* getAllAcceptedTags();
            bool doesCollideWithTags(std::vector<PolygonalCollider*> collidersList, std::vector<std::string> tags, int offx, int offy);
            std::vector<PolygonalCollider*> getCollidedCollidersWithTags(std::vector<PolygonalCollider*> collidersList, std::vector<std::string> tags, int offx, int offy);
            //Debug
            void draw(sf::RenderWindow* surf, bool drawLines = true, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
            void highlightPoint(int pointIndex);
            void highlightLine(int pointIndex);
            void clearHighlights(bool points = true, bool lines = true);
            void setDrawOffset(int offx, int offy);
        };
    }
}
