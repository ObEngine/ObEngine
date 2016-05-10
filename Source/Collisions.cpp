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
		return pPath.size();
	}
	void PolygonalCollider::setSelected(bool sel)
	{
		selected = sel;
	}
	bool PolygonalCollider::getSelected()
	{
		return selected;
	}
	std::pair<int, int> PolygonalCollider::getPointCoordinates(int index)
	{
		return std::pair<int, int>(pPath[index].X, pPath[index].Y);
	}
	std::pair<int, int> PolygonalCollider::getMasterPointCoordinates(int index)
	{
		return std::pair<int, int>(masterPoint.X, masterPoint.Y);
	}
	void PolygonalCollider::calculateMasterPoint()
	{
		masterPoint.X = 0;
		masterPoint.Y = 0;
		double signedArea = 0.0;
		double x0 = 0.0;
		double y0 = 0.0;
		double x1 = 0.0;
		double y1 = 0.0;
		double a = 0.0;

		int i;
		for (i = 0; i < pPath.size() - 1; ++i)
		{
			x0 = pPath[i].X;
			y0 = pPath[i].Y;
			x1 = pPath[i + 1].X;
			y1 = pPath[i + 1].Y;
			a = x0 * y1 - x1 * y0;
			signedArea += a;
			masterPoint.X += (x0 + x1) * a;
			masterPoint.Y += (y0 + y1) * a;
		}

		x0 = pPath[i].X;
		y0 = pPath[i].Y;
		x1 = pPath[0].X;
		y1 = pPath[0].Y;
		a = x0 * y1 - x1 * y0;
		signedArea += a;
		masterPoint.X += (x0 + x1) * a;
		masterPoint.Y += (y0 + y1) * a;

		signedArea *= 0.5;
		masterPoint.X /= (6.0*signedArea);
		masterPoint.Y /= (6.0*signedArea);
	}
	void PolygonalCollider::addPoint(int x, int y, int pointIndex)
	{
		if (pointIndex == -1 || pointIndex == pPath.size())
		{
			pPath << ClipperLib::IntPoint(x, y);
		}
		else if (pointIndex >= 0 && pointIndex < pPath.size())
		{
			ClipperLib::Path nPath;
			for (unsigned int i = 0; i < pointIndex; i++)
			{
				nPath << pPath[i];
			}
			nPath << ClipperLib::IntPoint(x, y);
			for (unsigned int i = pointIndex; i < pPath.size(); i++)
			{
				nPath << pPath[i];
			}
			pPath = nPath;
		}
		if (pPath.size() >= 3) { calculateMasterPoint(); }
	}
	void PolygonalCollider::deletePoint(int pointIndex)
	{
		pPath.erase(pPath.begin() + pointIndex);
	}
	double PolygonalCollider::getNodeDistance(int nodeIndex, int x, int y)
	{
		return std::sqrt(std::pow((x - pPath[nodeIndex].X), 2) + std::pow((y - pPath[nodeIndex].Y), 2));
	}
	int PolygonalCollider::findClosestNode(int x, int y, bool neighboor, std::vector<int> excludedNodes)
	{
		if (pPath.size() > 0)
		{
			int clNode = 0;
			double ndDist = 0;
			double tnDist = -1;
			for (unsigned int i = 0; i < pPath.size(); i++)
			{
				ndDist = this->getNodeDistance(i, x, y);
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
				if (lnghb < 0) { lnghb = pPath.size() - 1; }
				if (rnghb >= pPath.size()) { rnghb = 0; }
				int lnghbDist = std::sqrt(std::pow((x - pPath[lnghb].X), 2) + std::pow((y - pPath[lnghb].Y), 2));
				int rnghbDist = std::sqrt(std::pow((x - pPath[rnghb].X), 2) + std::pow((y - pPath[rnghb].Y), 2));
				if (lnghbDist > rnghbDist)
				{
					clNode++;
					if (clNode >= pPath.size())
					{
						clNode = 0;
					}
				}
			}
			return clNode;
		}
		return -1;
	}
	std::vector<int> PolygonalCollider::getSortedNodesByDistance(int x, int y, bool neighboor)
	{
		return std::vector<int>();
	}
	bool PolygonalCollider::doesCollide(PolygonalCollider* other, int offsetX, int offsetY, bool mustBeSolid)
	{
		if (mustBeSolid)
		{
			if (!solid) return false;
			if (!other->getSolid()) return false;
		}
		if (offsetX != 0 || offsetY != 0)
		{
			for (int i = 0; i < pPath.size(); i++)
			{
				pPath.at(i).X += offsetX; pPath.at(i).Y += offsetY;
			}
				
		}
		ClipperLib::Clipper clipper;
		clipper.AddPath(this->pPath, ClipperLib::ptSubject, true);
		clipper.AddPath(*other->getPath(), ClipperLib::ptClip, true);
		ClipperLib::Paths solution;
		clipper.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);
		
		if (offsetX != 0 || offsetY != 0)
		{
			for (int i = 0; i < pPath.size(); i++)
			{
				pPath.at(i).X -= offsetX; pPath.at(i).Y -= offsetY;
			}
		}
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
	std::vector<sf::RectangleShape> PolygonalCollider::returnCollisionSolution(PolygonalCollider* other, int offsetX, int offsetY)
	{
		if (offsetX != 0 || offsetY != 0)
		{
			for (int i = 0; i < pPath.size(); i++)
			{
				pPath.at(i).X += offsetX; pPath.at(i).Y += offsetY;
			}

		}
		ClipperLib::Clipper clipper;
		clipper.AddPath(this->pPath, ClipperLib::ptSubject, true);
		clipper.AddPath(*other->getPath(), ClipperLib::ptClip, true);
		ClipperLib::Paths solution;
		clipper.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

		if (offsetX != 0 || offsetY != 0)
		{
			for (int i = 0; i < pPath.size(); i++)
			{
				pPath.at(i).X -= offsetX; pPath.at(i).Y -= offsetY;
			}
		}
		std::vector<sf::RectangleShape> rvector;
		for (int j = 0; j < solution.size(); j++)
		{
			for (int k = 0; k < solution[j].size(); k++)
			{
				sf::RectangleShape trs = sf::RectangleShape(sf::Vector2f(5, 5));
				trs.setFillColor(sf::Color::Red);
				trs.setPosition(solution[j][k].X, solution[j][k].Y);
				rvector.push_back(trs);
			}
		}
		return rvector;
	}
	int PolygonalCollider::getSideContainingPoint(int x, int y)
	{
		for (int i = 0; i < pPath.size(); i++)
		{
			int nextNode = (i != pPath.size() - 1) ? i + 1 : 0;
			double lineLgt = this->getNodeDistance(i, this->getPointCoordinates(nextNode).first, this->getPointCoordinates(nextNode).second);
			double frstLgt = this->getNodeDistance(i, x, y);
			double scndLgt = this->getNodeDistance(nextNode, x, y);
			if (fn::Math::isBetween(lineLgt, frstLgt + scndLgt - 0.01, frstLgt + scndLgt + 0.01))
			{
				return i;
			}
		}
		return -1;
	}
	ClipperLib::Path* PolygonalCollider::getPath()
	{
		return &pPath;
	}
	int PolygonalCollider::hasPoint(int x, int y, int toleranceX, int toleranceY)
	{
		for (unsigned int i = 0; i < pPath.size(); i++)
		{
			if (fn::Math::isBetween(x, (int)pPath[i].X - toleranceX, (int)pPath[i].X + toleranceX))
			{
				if (fn::Math::isBetween(y, (int)pPath[i].Y - toleranceY, (int)pPath[i].Y + toleranceY))
				{
					return i;
				}
					
			}
		}
		return -1;
	}
	bool PolygonalCollider::hasMasterPoint(int x, int y, int toleranceX, int toleranceY)
	{
		if (fn::Math::isBetween(x, (int)masterPoint.X - toleranceX, (int)masterPoint.X + toleranceX))
		{
			if (fn::Math::isBetween(y, (int)masterPoint.Y - toleranceY, (int)masterPoint.Y + toleranceY))
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
	void PolygonalCollider::movePoint(int index, int x, int y)
	{
		pPath[index].X += x;
		pPath[index].Y += y;
		calculateMasterPoint();
	}
	void PolygonalCollider::setPointPosition(int index, int x, int y)
	{
		pPath[index].X = x;
		pPath[index].Y = y;
		calculateMasterPoint();
	}
	void PolygonalCollider::setPointRelativePosition(int index, int x, int y)
	{
		pPath[index].X = x + pPath[0].X;
		pPath[index].Y = y + pPath[0].Y;
		calculateMasterPoint();
	}
	void PolygonalCollider::setPointPositionFromMaster(int index, int x, int y)
	{
		pPath[index].X = x + masterPoint.X;
		pPath[index].Y = y + masterPoint.Y;
		calculateMasterPoint();
	}
	void PolygonalCollider::setDrawOffset(int offx, int offy)
	{
		drOffX = offx;
		drOffY = offy;
	}
	void PolygonalCollider::setPositionOffset(int offx, int offy)
	{
		pOffX = offx;
		pOffY = offy;
	}
	int PolygonalCollider::getPositionOffsetX()
	{
		return pOffX;
	}
	int PolygonalCollider::getPositionOffsetY()
	{
		return pOffY;
	}
	double PolygonalCollider::getSideAngle(int side)
	{
		int p1 = side;
		int p2 = side + 1;
		if (p1 == pPath.size() - 1)
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
		if (p1 == pPath.size() - 1)
		{
			p2 = 0;
		}
		std::pair<int, int> p1coords = this->getPointCoordinates(p1);
		std::pair<int, int> p2coords = this->getPointCoordinates(p2);
		return std::sqrt(std::pow(p1coords.first - p2coords.first, 2) + std::pow(p1coords.second - p2coords.second, 2));
	}
	int PolygonalCollider::getSidesAmount()
	{
		return pPath.size();
	}
	void PolygonalCollider::draw(sf::RenderWindow* surf, bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel)
	{
		if (pPath.size() >= 1)
		{
			sf::CircleShape polyPt;
			int r = 6;
			polyPt.setRadius(r);
			polyPt.setPointCount(100);
			if (!selected) polyPt.setFillColor(sf::Color(255, 150, 0));
			if (selected) polyPt.setFillColor(sf::Color(0, 150, 255));
			if (drawMasterPoint)
			{
				polyPt.setPosition(sf::Vector2f(masterPoint.X + drOffX - r, masterPoint.Y + drOffY - r));
				surf->draw(polyPt);
			}
			polyPt.setFillColor(sf::Color(255, 255, 255));
			for (int i = 0; i < pPath.size() - 1; i++)
			{
				int x1 = pPath[i].X + drOffX;
				int y1 = pPath[i].Y + drOffY;
				if (drawSkel)
				{
					if (!selected) Collision::drawLine(surf, x1, y1, masterPoint.X + drOffX, masterPoint.Y + drOffY, 2, sf::Color(255, 200, 0));
					if (selected) Collision::drawLine(surf, x1, y1, masterPoint.X + drOffX, masterPoint.Y + drOffY, 2, sf::Color(0, 200, 255));
				}
				if (drawLines)
				{
					if (!fn::Vector::isInList(i, highlightedLines)) Collision::drawLine(surf, pPath[i].X + drOffX, pPath[i].Y + drOffY, pPath[i + 1].X + drOffX, pPath[i + 1].Y + drOffY);
					else Collision::drawLine(surf, pPath[i].X + drOffX, pPath[i].Y + drOffY, pPath[i + 1].X + drOffX, pPath[i + 1].Y + drOffY, 2, sf::Color(0, 255, 0));
				}
				if (drawPoints)
				{
					polyPt.setPosition(sf::Vector2f(pPath[i].X + drOffX - r, pPath[i].Y + drOffY - r));
					if (fn::Vector::isInList(i, highlightedPoints))
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
				int x1 = pPath[pPath.size() - 1].X + drOffX - r;
				int y1 = pPath[pPath.size() - 1].Y + drOffY - r;
				polyPt.setPosition(sf::Vector2f(x1, y1));
				if (drawSkel)
				{
					if (!selected) Collision::drawLine(surf, x1 + r, y1 + r, masterPoint.X + drOffX, masterPoint.Y + drOffY, 2, sf::Color(255, 200, 0));
					if (selected) Collision::drawLine(surf, x1 + r, y1 + r, masterPoint.X + drOffX, masterPoint.Y + drOffY, 2, sf::Color(0, 200, 255));
				}
				if (fn::Vector::isInList((int)(pPath.size() - 1), highlightedPoints))
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
				if (!fn::Vector::isInList((int)pPath.size() - 1, highlightedLines)) Collision::drawLine(surf, pPath[pPath.size() - 1].X + drOffX, pPath[pPath.size() - 1].Y + drOffY, pPath[0].X + drOffX, pPath[0].Y + drOffY);
				else Collision::drawLine(surf, pPath[pPath.size() - 1].X + drOffX, pPath[pPath.size() - 1].Y + drOffY, pPath[0].X + drOffX, pPath[0].Y + drOffY, 2, sf::Color(0, 255, 0));
			}
		}
	}
	void PolygonalCollider::move(int x, int y)
	{
		masterPoint.X += x;
		masterPoint.Y += y;
		for (int i = 0; i < pPath.size(); i++)
		{
			pPath.at(i).X += x; pPath.at(i).Y += y;
		}
	}
	void PolygonalCollider::setPosition(int x, int y, int offsetMode)
	{
		if (pPath.size() > 0)
		{
			int addX = x - pPath[0].X + (offsetMode == 1 ? pOffX : 0);
			int addY = y - pPath[0].Y + (offsetMode == 1 ? pOffY : 0);
			masterPoint.X += addX;
			masterPoint.Y += addY;
			pPath[0].X = x + (offsetMode == 1 ? pOffX : 0);
			pPath[0].Y = y + (offsetMode == 1 ? pOffY : 0);
			for (int i = 1; i < pPath.size(); i++)
			{
				pPath.at(i).X += addX; pPath.at(i).Y += addY;
			}
			if (offsetMode == 2)
			{
				pOffX = addX;
				pOffY = addY;
			}
		}
	}
	void PolygonalCollider::setPositionFromMaster(int x, int y, int offsetMode)
	{
		if (pPath.size() > 0)
		{
			int addX = x - masterPoint.X + (offsetMode == 1 ? pOffX : 0);
			int addY = y - masterPoint.Y + (offsetMode == 1 ? pOffY : 0);
			masterPoint.X = x + (offsetMode == 1 ? pOffX : 0);
			masterPoint.Y = y + (offsetMode == 1 ? pOffY : 0);
			for (int i = 0; i < pPath.size(); i++)
			{
				pPath.at(i).X += addX; pPath.at(i).Y += addY;
			}
			if (offsetMode == 2)
			{
				pOffX = addX;
				pOffY = addY;
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

	bool testAllColliders(Collision::PolygonalCollider* collider, std::vector<Collision::PolygonalCollider*>* collidersList, int offx, int offy, bool opt)
	{
		for (int i = 0; i < collidersList->size(); i++)
		{
			if (collider->doesCollide(collidersList->at(i), offx, offy))
			{
				if (opt && i != 0) std::swap(collidersList->at(0), collidersList->at(i));
				return true;
			}
		}
		return false;
	}
}

