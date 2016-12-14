//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

#include "clipper.hpp"
#include "Functions.hpp"


namespace mse
{
	namespace Script
	{
		class GameObject;
	}
	namespace Collision
	{
		void drawLine(sf::RenderWindow* surf, int x1, int y1, int x2, int y2, int w = 2, sf::Color col1 = sf::Color(255, 255, 255));
		bool pointsCompare(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt);
		double pointsDistance(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt);
		std::vector<ClipperLib::IntPoint*> convexHull(std::vector<ClipperLib::IntPoint*> points);
		int cross(ClipperLib::IntPoint* O, ClipperLib::IntPoint* A, ClipperLib::IntPoint* B);

		typedef std::pair<double, double> DoublePoint;
		class PolygonalCollider
		{
			private:
				std::string id;
				std::vector<std::string> excludedIds;
				std::vector<std::string> acceptedIds;

				//Tag System
				std::vector<std::string> tags;
				std::vector<std::string> excludedTags;
				std::vector<std::string> acceptedTags; //If not empty, will only accept tags from this

				int drOffX;
				int drOffY;
				long long int tX = 0;
				long long int tY = 0;
				long long int bX = 0;
				long long int bY = 0;
				DoublePoint masterPoint;
				std::vector<DoublePoint> allPoints;
				sf::ConvexShape drawShape;
				void calculateMasterPoint();
				bool selected;
				std::vector<int> highlightedPoints;
				std::vector<int> highlightedLines;
				Script::GameObject* parent = nullptr;
			public:
				PolygonalCollider(std::string id);
				std::string getID();
				int getPointsAmount();
				DoublePoint getPointPosition(int index);
				DoublePoint getPointRelativePosition(int index);
				DoublePoint getMasterPointPosition();
				void setSelected(bool sel);
				bool getSelected();
				void addPoint(double x, double y, int pointIndex = -1);
				void deletePoint(int pointIndex);
				double getDistanceFromPoint(int nodeIndex, double x, double y);
				int findClosestPoint(double x, double y, bool neighboor = false, std::vector<int> excludedNodes = std::vector<int>());
				bool doesCollide(PolygonalCollider* other, double offsetX = 0, double offsetY = 0);
				bool doesPathCollide(std::vector<PolygonalCollider*> others, double offsetX = 0, double offsetY = 0, double toX = 0, double toY = 0);
				int getSideContainingPoint(int x, int y);
				bool isPointInBoundingBox(int x, int y);
				int hasPoint(int x, int y, int toleranceX = 0, int toleranceY = 0);
				bool hasMasterPoint(int x, int y, int toleranceX = 0, int toleranceY = 0);
				DoublePoint getPosition();
				void move(double x, double y);
				void setPosition(double x, double y);
				void setPositionFromMaster(double x, double y);
				void movePoint(int index, double x, double y);
				void setPointPosition(int index, double x, double y);
				void setPointRelativePosition(int index, double x, double y);
				void setPointPositionFromMaster(int index, double x, double y);
				ClipperLib::Path getPath();
				std::vector<DoublePoint> getAllPoints();
				double getSideAngle(int side);
				double getSideLength(int side);
				Script::GameObject* getParent();
				void setParent(Script::GameObject* parent);
				Collision::PolygonalCollider joinPolygonalColliders(std::string joinID, Collision::PolygonalCollider* other);
				bool testAllColliders(std::vector<Collision::PolygonalCollider*> collidersList, double offx, double offy, bool opt = false);
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
				bool doesHaveTag(std::string tag);
				bool isTagExcluded(std::string tag);
				bool isTagAccepted(std::string tag);
				bool doesHaveAnyTag(std::vector<std::string>* tags);
				bool isATagExcluded(std::vector<std::string>* tags);
				bool isATagAccepted(std::vector<std::string>* tags);
				std::vector<std::string>* getAllTags();
				std::vector<std::string>* getAllExcludedTags();
				std::vector<std::string>* getAllAcceptedTags();
				bool doesCollideWithTags(std::vector<Collision::PolygonalCollider*> collidersList, std::vector<std::string> tags, double offx, double offy);
				//Debug
				void draw(sf::RenderWindow* surf, bool drawLines = true, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
				void highlightPoint(int pointIndex);
				void highlightLine(int pointIndex);
				void clearHighlights(bool points = true, bool lines = true);
				void setDrawOffset(int offx, int offy);
		};
	}
}