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

		typedef std::pair<double, double> DoublePoint;

		class PolygonalCollider //Polygon with collision methods
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
			DoublePoint m_masterPoint;
			std::vector<DoublePoint> m_allPoints;
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
			int getPointsAmount() const;
			DoublePoint getPointPosition(int index);
			DoublePoint getPointRelativePosition(int index);
			DoublePoint getMasterPointPosition() const;
			void setSelected(bool sel);
			bool getSelected() const;
			void addPoint(double x, double y, int pointIndex = -1);
			void deletePoint(int pointIndex);
			double getDistanceFromPoint(int nodeIndex, double x, double y);
			int findClosestPoint(double x, double y, bool neighboor = false, std::vector<int> excludedNodes = std::vector<int>());
			bool doesCollide(PolygonalCollider* other, double offsetX = 0, double offsetY = 0);
			bool doesPathCollide(std::vector<PolygonalCollider*> others, double offsetX = 0, double offsetY = 0, double toX = 0, double toY = 0);
			int getSideContainingPoint(int x, int y);
			bool isPointInBoundingBox(int x, int y) const;
			int hasPoint(int x, int y, int toleranceX = 0, int toleranceY = 0);
			bool hasMasterPoint(int x, int y, int toleranceX = 0, int toleranceY = 0) const;
			DoublePoint getPosition();
			void move(double x, double y);
			void setPosition(double x, double y);
			void setPositionFromMaster(double x, double y);
			void movePoint(int index, double x, double y);
			void setPointPosition(int index, double x, double y);
			void setPointRelativePosition(int index, double x, double y);
			void setPointPositionFromMaster(int index, double x, double y);
			ClipperLib::Path getPath();
			std::vector<DoublePoint> getAllPoints() const;
			double getSideAngle(int side);
			double getSideLength(int side);
			std::string getParentID() const;
			void setParentID(std::string parent);
			Collision::PolygonalCollider joinPolygonalColliders(std::string joinID, Collision::PolygonalCollider* other);
			bool testAllColliders(std::vector<Collision::PolygonalCollider*> collidersList, double offx, double offy, bool opt = false);
			std::vector<PolygonalCollider*> getAllCollidedColliders(std::vector<Collision::PolygonalCollider*> collidersList, double offx, double offy);
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
			bool doesCollideWithTags(std::vector<Collision::PolygonalCollider*> collidersList, std::vector<std::string> tags, double offx, double offy);
			std::vector<PolygonalCollider*> getCollidedCollidersWithTags(std::vector<Collision::PolygonalCollider*> collidersList, std::vector<std::string> tags, double offx, double offy);
			//Debug
			void draw(sf::RenderWindow* surf, bool drawLines = true, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
			void highlightPoint(int pointIndex);
			void highlightLine(int pointIndex);
			void clearHighlights(bool points = true, bool lines = true);
			void setDrawOffset(int offx, int offy);
		};
	}
}
