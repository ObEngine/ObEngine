//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Collisions.hpp"

namespace Collision
{
	void drawLine(sf::RenderWindow* surf, int x1, int y1, int x2, int y2, int w, sf::Color col)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x1, y1), col),
			sf::Vertex(sf::Vector2f(x2, y2), col)
		};
		surf->draw(line, w, sf::Lines);
	}

	bool pointsCompare(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt)
	{
		if (firstPt->X < secondPt->X)
			return true;
		else if (firstPt->X == secondPt->X)
		{
			if (firstPt->Y <= secondPt->Y)
				return false;
			else
				return true;
		}
		else
			return false;
	}

	double pointsDistance(const ClipperLib::IntPoint * firstPt, const ClipperLib::IntPoint * secondPt)
	{
		return std::sqrt(std::pow(secondPt->X - firstPt->X, 2) + std::pow(secondPt->Y - firstPt->Y, 2));
	}

	std::vector<ClipperLib::IntPoint*> convexHull(std::vector<ClipperLib::IntPoint*> points)
	{
		std::sort(points.begin(), points.end(), pointsCompare);
		if (points.size() <= 1)
			return points;
		std::vector<ClipperLib::IntPoint*> lowerHull;
		for (int i = 0; i < points.size(); i++)
		{
			while (lowerHull.size() >= 2 && cross(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1], points[i]) <= 0)
				lowerHull.pop_back();
			lowerHull.push_back(points[i]);
		}
		std::reverse(points.begin(), points.end());
		std::vector<ClipperLib::IntPoint*> upperHull;
		for (int i = 0; i < points.size(); i++)
		{
			while (upperHull.size() >= 2 && cross(upperHull[upperHull.size() - 2], upperHull[upperHull.size() - 1], points[i]) <= 0)
				upperHull.pop_back();
			upperHull.push_back(points[i]);
		}
		std::vector<ClipperLib::IntPoint*> fullHull;
		fullHull.reserve(lowerHull.size() + upperHull.size() - 2);
		fullHull.insert(fullHull.end(), lowerHull.begin(), lowerHull.end() - 1);
		fullHull.insert(fullHull.end(), upperHull.begin(), upperHull.end() - 1);
		return fullHull;
	}

	int cross(ClipperLib::IntPoint* O, ClipperLib::IntPoint* A, ClipperLib::IntPoint* B)
	{
		return (A->X - O->X) * (B->Y - O->Y) - (A->Y - O->Y) * (B->X - O->X);
	}

	PolygonalCollider::PolygonalCollider(std::string id)
	{
		this->id = id;
	}
	std::string PolygonalCollider::getID()
	{
		return id;
	}
	void PolygonalCollider::setSolid(bool state)
	{
		solid = state;
	}
	bool PolygonalCollider::getSolid()
	{
		return solid;
	}
	int PolygonalCollider::getPointsAmount()
	{
		return allPoints.size();
	}
	void PolygonalCollider::setSelected(bool sel)
	{
		selected = sel;
	}
	bool PolygonalCollider::getSelected()
	{
		return selected;
	}
	std::pair<double, double> PolygonalCollider::getPointCoordinates(int index)
	{
		return allPoints[index];
	}
	std::pair<double, double> PolygonalCollider::getMasterPointCoordinates()
	{
		return masterPoint;
	}
	void PolygonalCollider::calculateMasterPoint()
	{
		masterPoint.first = 0;
		masterPoint.second = 0;
		double signedArea = 0.0;
		double x0 = 0.0;
		double y0 = 0.0;
		double x1 = 0.0;
		double y1 = 0.0;
		double a = 0.0;

		int i;
		for (i = 0; i < allPoints.size() - 1; ++i)
		{
			x0 = allPoints[i].first;
			y0 = allPoints[i].second;
			x1 = allPoints[i + 1].first;
			y1 = allPoints[i + 1].second;
			a = x0 * y1 - x1 * y0;
			signedArea += a;
			masterPoint.first += (x0 + x1) * a;
			masterPoint.second += (y0 + y1) * a;
		}

		x0 = allPoints[i].first;
		y0 = allPoints[i].second;
		x1 = allPoints[0].first;
		y1 = allPoints[0].second;
		a = x0 * y1 - x1 * y0;
		signedArea += a;
		masterPoint.first += (x0 + x1) * a;
		masterPoint.second += (y0 + y1) * a;

		signedArea *= 0.5;
		masterPoint.first /= (6.0*signedArea);
		masterPoint.second /= (6.0*signedArea);
	}
	void PolygonalCollider::addPoint(double x, double y, int pointIndex)
	{
		if (pointIndex == -1 || pointIndex == allPoints.size())
			allPoints.push_back(std::pair<double, double>(x, y));
		else if (pointIndex >= 0 && pointIndex < allPoints.size())
			allPoints.insert(allPoints.begin() + pointIndex, std::pair<double, double>(x, y));
		if (allPoints.size() >= 3) { calculateMasterPoint(); }
	}
	void PolygonalCollider::deletePoint(int pointIndex)
	{
		allPoints.erase(allPoints.begin() + pointIndex);
	}
	double PolygonalCollider::getDistanceFromPoint(int nodeIndex, double x, double y)
	{
		return std::sqrt(std::pow((x - allPoints[nodeIndex].first), 2) + std::pow((y - allPoints[nodeIndex].second), 2));
	}
	int PolygonalCollider::findClosestPoint(double x, double y, bool neighboor, std::vector<int> excludedNodes)
	{
		if (allPoints.size() > 0)
		{
			int clNode = 0;
			double ndDist = 0;
			double tnDist = -1;
			for (unsigned int i = 0; i < allPoints.size(); i++)
			{
				ndDist = this->getDistanceFromPoint(i, x, y);
				if ((tnDist == -1 || tnDist > ndDist) && !fn::Vector::isInList((int)i, excludedNodes))
				{
					clNode = i;
					tnDist = ndDist;
				}
			}
			if (neighboor)
			{
				int lnghb = clNode - 1;
				int rnghb = clNode + 1;
				if (lnghb < 0) { lnghb = allPoints.size() - 1; }
				if (rnghb >= allPoints.size()) { rnghb = 0; }
				int lnghbDist = std::sqrt(std::pow((x - allPoints[lnghb].first), 2) + std::pow((y - allPoints[lnghb].second), 2));
				int rnghbDist = std::sqrt(std::pow((x - allPoints[rnghb].first), 2) + std::pow((y - allPoints[rnghb].second), 2));
				if (lnghbDist > rnghbDist)
				{
					clNode++;
					if (clNode >= allPoints.size())
					{
						clNode = 0;
					}
				}
			}
			return clNode;
		}
		return -1;
	}
	bool PolygonalCollider::doesCollide(PolygonalCollider* other, double offsetX, double offsetY, bool mustBeSolid)
	{
		if (mustBeSolid)
		{
			if (!solid) return false;
			if (!other->getSolid()) return false;
		}
		ClipperLib::Path pPath = this->getPath();
		for (int i = 0; i < allPoints.size(); i++)
		{
			pPath.at(i).X += offsetX; pPath.at(i).Y += offsetY;
		}
		ClipperLib::Clipper clipper;
		clipper.AddPath(pPath, ClipperLib::ptSubject, true);
		clipper.AddPath(other->getPath(), ClipperLib::ptClip, true);
		ClipperLib::Paths solution;
		clipper.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

		other->clearHighlights(false, true);
		if (solution.size() >= 1)
		{
			std::vector<int> sidesToHL;
			for (int j = 0; j < solution.size(); j++)
			{
				for (int k = 0; k < solution[j].size(); k++)
				{
					other->highlightLine(other->getSideContainingPoint(solution[j][k].X, solution[j][k].Y));
				}
			}
		}
		
		return (solution.size() >= 1);
	}
	bool PolygonalCollider::doesPathCollide(std::vector<PolygonalCollider*> others, double offsetX, double offsetY, double toX, double toY, bool mustBeSolid)
	{
		if (mustBeSolid)
		{
			if (!solid) return false;
			bool allImmaterial = true;
			for (int i = 0; i < others.size(); i++)
			{
				if (others[i]->getSolid())
					allImmaterial = false;
			}
			if (allImmaterial) return false;
		}
		std::cout << "Recv : Path Collider With AddTOXY : " << toX << "," << toY << std::endl;
		Collision::PolygonalCollider projection(this->id + "_proj");
		for (int i = 0; i < allPoints.size(); i++)
			projection.addPoint(allPoints[i].first + toX, allPoints[i].second + toY);
		this->move(offsetX, offsetY);
		Collision::PolygonalCollider fullPath = this->joinPolygonalColliders(this->id + "_path", &projection);
		this->move(-offsetX, -offsetY);

		ClipperLib::Clipper clipper;
		clipper.AddPath(fullPath.getPath(), ClipperLib::ptSubject, true);
		for (int i = 0; i < others.size(); i++)
		{
			if (others[i] != this)
				clipper.AddPath(others[i]->getPath(), ClipperLib::ptClip, true);
		}
			
		ClipperLib::Paths solution;
		clipper.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

		return (solution.size() >= 1);
	}
	int PolygonalCollider::getSideContainingPoint(int x, int y)
	{
		for (int i = 0; i < allPoints.size(); i++)
		{
			int nextNode = (i != allPoints.size() - 1) ? i + 1 : 0;
			double lineLgt = this->getDistanceFromPoint(i, this->getPointCoordinates(nextNode).first, this->getPointCoordinates(nextNode).second);
			double frstLgt = this->getDistanceFromPoint(i, x, y);
			double scndLgt = this->getDistanceFromPoint(nextNode, x, y);
			if (fn::Math::isBetween(lineLgt, frstLgt + scndLgt - 0.01, frstLgt + scndLgt + 0.01))
			{
				return i;
			}
		}
		return -1;
	}
	ClipperLib::Path PolygonalCollider::getPath()
	{
		ClipperLib::Path buildPath;
		for (int i = 0; i < allPoints.size(); i++)
			buildPath << ClipperLib::IntPoint(allPoints[i].first, allPoints[i].second);
		return buildPath;
	}
	std::vector<std::pair<double, double>> PolygonalCollider::getAllPoints()
	{
		return allPoints;
	}
	int PolygonalCollider::hasPoint(int x, int y, int toleranceX, int toleranceY)
	{
		for (unsigned int i = 0; i < allPoints.size(); i++)
		{
			if (fn::Math::isBetween(x, (int)allPoints[i].first - toleranceX, (int)allPoints[i].first + toleranceX))
			{
				if (fn::Math::isBetween(y, (int)allPoints[i].second - toleranceY, (int)allPoints[i].second + toleranceY))
				{
					return i;
				}
					
			}
		}
		return -1;
	}
	bool PolygonalCollider::hasMasterPoint(int x, int y, int toleranceX, int toleranceY)
	{
		if (fn::Math::isBetween(x, (int)masterPoint.first - toleranceX, (int)masterPoint.first + toleranceX))
		{
			if (fn::Math::isBetween(y, (int)masterPoint.second - toleranceY, (int)masterPoint.second + toleranceY))
			{
				return true;
			}

		}
		return false;
	}
	bool PolygonalCollider::isPointInBoundingBox(int x, int y)
	{
		return (x >= tX && x <= bX && y >= tY && y <= bY);
	}
	void PolygonalCollider::movePoint(int index, double x, double y)
	{
		allPoints[index].first += x;
		allPoints[index].second += y;
		calculateMasterPoint();
	}
	void PolygonalCollider::setPointPosition(int index, double x, double y)
	{
		allPoints[index].first = x;
		allPoints[index].second = y;
		calculateMasterPoint();
	}
	void PolygonalCollider::setPointRelativePosition(int index, double x, double y)
	{
		allPoints[index].first = x + allPoints[0].first;
		allPoints[index].second = y + allPoints[0].second;
		calculateMasterPoint();
	}
	void PolygonalCollider::setPointPositionFromMaster(int index, double x, double y)
	{
		allPoints[index].first = x + masterPoint.first;
		allPoints[index].second = y + masterPoint.second;
		calculateMasterPoint();
	}
	void PolygonalCollider::setDrawOffset(int offx, int offy)
	{
		drOffX = offx;
		drOffY = offy;
	}
	double PolygonalCollider::getSideAngle(int side)
	{
		int p1 = side;
		int p2 = side + 1;
		if (p1 == allPoints.size() - 1)
		{
			p2 = 0;
		}
		std::pair<int, int> p1coords = this->getPointCoordinates(p1);
		std::pair<int, int> p2coords = this->getPointCoordinates(p2);
		int deltaX = p2coords.first - p1coords.first;
		int deltaY = p2coords.second - p1coords.second;
		return (std::atan2(deltaY, deltaX) * 180 / fn::Math::pi);
	}
	double PolygonalCollider::getSideLength(int side)
	{
		int p1 = side;
		int p2 = side + 1;
		if (p1 == allPoints.size() - 1)
		{
			p2 = 0;
		}
		std::pair<int, int> p1coords = this->getPointCoordinates(p1);
		std::pair<int, int> p2coords = this->getPointCoordinates(p2);
		return std::sqrt(std::pow(p1coords.first - p2coords.first, 2) + std::pow(p1coords.second - p2coords.second, 2));
	}
	void PolygonalCollider::draw(sf::RenderWindow* surf, bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel)
	{
		if (allPoints.size() >= 1)
		{
			sf::CircleShape polyPt;
			int r = 6;
			polyPt.setRadius(r);
			polyPt.setPointCount(100);
			if (!selected) polyPt.setFillColor(sf::Color(255, 150, 0));
			if (selected) polyPt.setFillColor(sf::Color(0, 150, 255));
			if (drawMasterPoint)
			{
				polyPt.setPosition(sf::Vector2f(masterPoint.first + drOffX - r, masterPoint.second + drOffY - r));
				surf->draw(polyPt);
			}
			polyPt.setFillColor(sf::Color(255, 255, 255));
			for (int i = 0; i < allPoints.size() - 1; i++)
			{
				int x1 = allPoints[i].first + drOffX;
				int y1 = allPoints[i].second + drOffY;
				if (drawSkel)
				{
					if (!selected) Collision::drawLine(surf, x1, y1, masterPoint.first + drOffX, masterPoint.second + drOffY, 2, sf::Color(255, 200, 0));
					if (selected) Collision::drawLine(surf, x1, y1, masterPoint.first + drOffX, masterPoint.second + drOffY, 2, sf::Color(0, 200, 255));
				}
				if (drawLines)
				{
					if (!fn::Vector::isInList(i, highlightedLines)) 
						Collision::drawLine(surf, allPoints[i].first + drOffX, allPoints[i].second + drOffY, allPoints[i + 1].first + drOffX, allPoints[i + 1].second + drOffY);
					else 
						Collision::drawLine(surf, allPoints[i].first + drOffX, allPoints[i].second + drOffY, allPoints[i + 1].first + drOffX, allPoints[i + 1].second + drOffY, 2, sf::Color(0, 255, 0));
				}
				if (drawPoints)
				{
					polyPt.setPosition(sf::Vector2f(allPoints[i].first + drOffX - r, allPoints[i].second + drOffY - r));
					if (i == 0 && fn::Vector::isInList(i, highlightedPoints) && selected)
					{
						polyPt.setFillColor(sf::Color(255, 255, 0));
					}
					else if (i == 0 && selected)
					{
						polyPt.setFillColor(sf::Color(0, 255, 0));
					}
					else if (fn::Vector::isInList(i, highlightedPoints) && selected)
					{
						polyPt.setFillColor(sf::Color(255, 0, 0));
					}
					else
					{
						polyPt.setFillColor(sf::Color(255, 255, 255));
					}
					surf->draw(polyPt);
				}
			}
			if (drawPoints)
			{
				int x1 = allPoints[allPoints.size() - 1].first + drOffX - r;
				int y1 = allPoints[allPoints.size() - 1].second + drOffY - r;
				polyPt.setPosition(sf::Vector2f(x1, y1));
				if (drawSkel)
				{
					if (!selected) Collision::drawLine(surf, x1 + r, y1 + r, masterPoint.first + drOffX, masterPoint.second + drOffY, 2, sf::Color(255, 200, 0));
					if (selected) Collision::drawLine(surf, x1 + r, y1 + r, masterPoint.first + drOffX, masterPoint.second + drOffY, 2, sf::Color(0, 200, 255));
				}
				if (fn::Vector::isInList((int)(allPoints.size() - 1), highlightedPoints))
				{
					polyPt.setFillColor(sf::Color(255, 0, 0));
				}
				else
				{
					polyPt.setFillColor(sf::Color(255, 255, 255));
				}
				if (drawPoints) surf->draw(polyPt);
			}
			if (drawLines)
			{
				if (!fn::Vector::isInList((int)allPoints.size() - 1, highlightedLines)) 
					Collision::drawLine(surf, allPoints[allPoints.size() - 1].first + drOffX, allPoints[allPoints.size() - 1].second + drOffY, allPoints[0].first + drOffX, allPoints[0].second + drOffY);
				else 
					Collision::drawLine(surf, allPoints[allPoints.size() - 1].first + drOffX, allPoints[allPoints.size() - 1].second + drOffY, allPoints[0].first + drOffX, allPoints[0].second + drOffY, 2, sf::Color(0, 255, 0));
			}
		}
	}
	std::pair<double, double> PolygonalCollider::getPosition()
	{
		return allPoints[0];
	}
	void PolygonalCollider::move(double x, double y)
	{
		if (allPoints.size() > 0)
		{
			masterPoint.first += x;
			masterPoint.second += y;
			for (int i = 0; i < allPoints.size(); i++)
			{
				allPoints.at(i).first += x; allPoints.at(i).second += y;
			}
		}
	}
	void PolygonalCollider::setPosition(double x, double y)
	{
		if (allPoints.size() > 0)
		{
			double addX = x - allPoints[0].first;
			double addY = y - allPoints[0].second;
			masterPoint.first += addX;
			masterPoint.second += addY;
			allPoints[0].first = x;
			allPoints[0].second = y;
			for (int i = 1; i < allPoints.size(); i++)
			{
				allPoints.at(i).first += addX; allPoints.at(i).second += addY;
			}
		}
	}
	void PolygonalCollider::setPositionFromMaster(double x, double y)
	{
		if (allPoints.size() > 0)
		{
			double addX = x - masterPoint.first;
			double addY = y - masterPoint.second;
			masterPoint.first = x;
			masterPoint.second = y;
			for (int i = 0; i < allPoints.size(); i++)
			{
				allPoints.at(i).first += addX; allPoints.at(i).second += addY;
			}
		}
	}
	void PolygonalCollider::highlightPoint(int pointIndex)
	{
		highlightedPoints.push_back(pointIndex);
	}
	void PolygonalCollider::highlightLine(int pointIndex)
	{
		highlightedLines.push_back(pointIndex);
	}
	void PolygonalCollider::clearHighlights(bool points, bool lines)
	{
		if (points) highlightedPoints.clear();
		if (lines) highlightedLines.clear();
	}

	GameObject* PolygonalCollider::getParent()
	{
		return parent;
	}

	void PolygonalCollider::setParent(GameObject* parent)
	{
		this->parent = parent;
	}

	Collision::PolygonalCollider PolygonalCollider::joinPolygonalColliders(std::string joinID, Collision::PolygonalCollider* other)
	{
		ClipperLib::Path polyAPath = this->getPath();
		std::vector<ClipperLib::IntPoint*> polyA;
		for (int i = 0; i < polyAPath.size(); i++)
			polyA.push_back(&polyAPath.at(i));
		ClipperLib::Path polyBPath = other->getPath();
		std::vector<ClipperLib::IntPoint*> polyB;
		for (int i = 0; i < polyBPath.size(); i++)
			polyB.push_back(&polyBPath.at(i));
		std::vector<std::vector<ClipperLib::IntPoint*>> polys = { polyA, polyB };
		auto findFromAddress = [polyA, polyB](ClipperLib::IntPoint* addr) -> int {
			for (int i = 0; i < polyA.size(); i++)
			{
				if (addr == polyA[i])
					return i;
			}
			for (int i = 0; i < polyB.size(); i++)
			{
				if (addr == polyB[i])
					return i;
			}
			return -1;
		};
		std::vector<ClipperLib::IntPoint*> allPoints;
		allPoints.reserve(polyA.size() + polyB.size());
		allPoints.insert(allPoints.end(), polyA.begin(), polyA.end());
		allPoints.insert(allPoints.end(), polyB.begin(), polyB.end());
		std::vector<ClipperLib::IntPoint*> conv = convexHull(allPoints);
		Collision::PolygonalCollider result(joinID);
		for (int i = 0; i < conv.size(); i++)
		{
			ClipperLib::IntPoint *a, *b;
			a = conv[i]; b = conv[(i + 1) % conv.size()];
			result.addPoint(a->X, a->Y);
			for (int poly = 0; poly < polys.size(); poly++)
			{
				if (fn::Vector::isInList(a, polys[poly]) && fn::Vector::isInList(b, polys[poly]))
				{
					int iA = findFromAddress(a);
					int iB = findFromAddress(b);
					int counter = 0;
					while ((iA + counter) % polys[poly].size() != iB)
					{
						int index = (iA + counter) % polys[poly].size();
						result.addPoint(polys[poly][index]->X, polys[poly][index]->Y);
						counter++;
					}
				}
			}
		}
		return result;
	}

	bool Collision::PolygonalCollider::testAllColliders(std::vector<Collision::PolygonalCollider*> collidersList, double offx, double offy, bool opt)
	{
		for (int i = 0; i < collidersList.size(); i++)
		{
			if (this != collidersList.at(i))
			{
				if (this->doesCollide(collidersList.at(i), offx, offy, true))
				{
					if (opt && i != 0) std::swap(collidersList.at(0), collidersList.at(i));
					return true;
				}
			}
		}
		return false;
	}
}
