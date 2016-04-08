//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

#include "clipper.hpp"
#include "Functions.hpp"


namespace Collision
{
	void drawLine(sf::RenderWindow* surf, int x1, int y1, int x2, int y2, int w = 2, sf::Color col1 = sf::Color(255, 255, 255));
	class PolygonalCollider
	{
	private:
		std::string id;
		int offxd;
		int offyd;
		long long int tX = 0;
		long long int tY = 0;
		long long int bX = 0;
		long long int bY = 0;
		ClipperLib::IntPoint masterPoint;
		ClipperLib::Paths subj;
		ClipperLib::Path pPath;
		sf::ConvexShape drawShape;
		void calculateMasterPoint();
		bool selected;
		bool solid = true;
		std::vector<int> highlightedPoints;
		std::vector<int> highlightedLines;
	public:
		PolygonalCollider(std::string id);
		std::string getID();
		void setSolid(bool state);
		bool getSolid();
		int getPointsAmount();
		int getSidesAmount();
		std::pair<int, int> getPointCoordinates(int index);
		std::pair<int, int> getMasterPointCoordinates(int index);
		void setSelected(bool sel);
		bool getSelected();
		void addPoint(int x, int y, int pointIndex = -1);
		void deletePoint(int pointIndex);
		double getNodeDistance(int nodeIndex, int x, int y);
		int findClosestNode(int x, int y, bool neighboor = false, std::vector<int> excludedNodes = std::vector<int>());
		std::vector<int> getSortedNodesByDistance(int x, int y, bool neighboor = false);
		bool doesCollide(PolygonalCollider* other, int offsetX = 0, int offsetY = 0, bool mustBeSolid = true);
		std::vector<sf::RectangleShape> returnCollisionSolution(PolygonalCollider* other, int offsetX = 0, int offsetY = 0);
		int getSideContainingPoint(int x, int y);
		void move(int x, int y);
		void setPosition(int x, int y);
		void setPositionFromMaster(int x, int y);
		bool isPointInBoundingBox(int x, int y);
		int hasPoint(int x, int y, int toleranceX = 0, int toleranceY = 0);
		bool hasMasterPoint(int x, int y, int toleranceX = 0, int toleranceY = 0);
		void movePoint(int index, int x, int y);
		ClipperLib::Path* getPath();
		void setDrawOffset(int offx, int offy);
		double getSideAngle(int side);
		double getSideLength(int side);
		void draw(sf::RenderWindow* surf, bool drawLines = true, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
		void highlightPoint(int pointIndex);
		void highlightLine(int pointIndex);
		void clearHighlights(bool points = true, bool lines = true);
	};
	
	bool testAllColliders(Collision::PolygonalCollider* collider, std::vector<Collision::PolygonalCollider*>* collidersList, int offx, int offy, bool opt = false);
}