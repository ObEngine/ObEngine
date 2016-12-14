//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Collisions.hpp"

namespace mse
{
	namespace Collision
	{
		void drawLine(sf::RenderWindow* surf, int x1, int y1, int x2, int y2, int w, sf::Color col) 
		{
			sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(x1, y1), col),
				sf::Vertex(sf::Vector2f(x2, y2), col)
			};
			surf->draw(line, w, sf::Lines);
		}

		bool pointsCompare(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt) 
		{
			if (firstPt->X < secondPt->X)
				return true;
			else if (firstPt->X == secondPt->X) {
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
			for (ClipperLib::IntPoint* point : points) {
				while (lowerHull.size() >= 2 && cross(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1], point) <= 0)
					lowerHull.pop_back();
				lowerHull.push_back(point);
			}
			std::reverse(points.begin(), points.end());
			std::vector<ClipperLib::IntPoint*> upperHull;
			for (ClipperLib::IntPoint* point : points) {
				while (upperHull.size() >= 2 && cross(upperHull[upperHull.size() - 2], upperHull[upperHull.size() - 1], point) <= 0)
					upperHull.pop_back();
				upperHull.push_back(point);
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
		DoublePoint PolygonalCollider::getPointPosition(int index)
		{
			return allPoints[index];
		}
		DoublePoint PolygonalCollider::getPointRelativePosition(int index)
		{
			return DoublePoint(allPoints[index].first - allPoints[0].first, allPoints[index].second - allPoints[0].second);
		}
		DoublePoint PolygonalCollider::getMasterPointPosition()
		{
			return masterPoint;
		}
		void PolygonalCollider::calculateMasterPoint()
		{
			masterPoint = { 0, 0 };
			double signedArea = 0.0;
			double x0, y0, x1, y1, a = 0.0;

			int i;
			for (i = 0; i < allPoints.size() - 1; ++i) {
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
			masterPoint.first /= (6.0 * signedArea);
			masterPoint.second /= (6.0 * signedArea);
		}
		void PolygonalCollider::addPoint(double x, double y, int pointIndex)
		{
			if (pointIndex == -1 || pointIndex == allPoints.size())
				allPoints.push_back({ x, y });
			else if (pointIndex >= 0 && pointIndex < allPoints.size())
				allPoints.insert(allPoints.begin() + pointIndex, { x, y });
			if (allPoints.size() >= 3)
				calculateMasterPoint();
		}
		void PolygonalCollider::deletePoint(int pointIndex)
		{
			allPoints.erase(allPoints.begin() + pointIndex);
			this->calculateMasterPoint();
		}
		double PolygonalCollider::getDistanceFromPoint(int nodeIndex, double x, double y)
		{
			return std::sqrt(std::pow((x - allPoints[nodeIndex].first), 2) + std::pow((y - allPoints[nodeIndex].second), 2));
		}
		int PolygonalCollider::findClosestPoint(double x, double y, bool neighboor, std::vector<int> excludedNodes)
		{
			if (allPoints.size() > 0) {
				int closestNode = 0;
				double currentPointDist = 0;
				double tiniestDist = -1;
				for (unsigned int i = 0; i < allPoints.size(); i++) {
					currentPointDist = this->getDistanceFromPoint(i, x, y);
					if ((tiniestDist == -1 || tiniestDist > currentPointDist) && !Functions::Vector::isInList((int)i, excludedNodes)) {
						closestNode = i;
						tiniestDist = currentPointDist;
					}
				}
				if (neighboor) {
					int leftNeighbor = closestNode - 1;
					int rightNeighbor = closestNode + 1;
					if (leftNeighbor < 0)
						leftNeighbor = allPoints.size() - 1;
					if (rightNeighbor >= allPoints.size()) 
						rightNeighbor = 0;
					int leftNeighborDist = std::sqrt(std::pow((x - allPoints[leftNeighbor].first), 2) + 
						std::pow((y - allPoints[leftNeighbor].second), 2));
					int rightNeighborDist = std::sqrt(std::pow((x - allPoints[rightNeighbor].first), 2) + 
						std::pow((y - allPoints[rightNeighbor].second), 2));
					if (leftNeighborDist > rightNeighborDist) {
						closestNode++;
						if (closestNode >= allPoints.size())
							closestNode = 0;
					}
				}
				return closestNode;
			}
			return -1;
		}
		bool PolygonalCollider::doesCollide(PolygonalCollider* other, double offsetX, double offsetY)
		{
			if (isATagExcluded(other->getAllTags()))
				return false;
			if (!isATagAccepted(other->getAllTags()))
				return false;

			ClipperLib::Path pPath = this->getPath();
			for (int i = 0; i < allPoints.size(); i++) {
				pPath[i].X += offsetX; pPath[i].Y += offsetY;
			}
			ClipperLib::Clipper clipper;
			clipper.AddPath(pPath, ClipperLib::ptSubject, true);
			clipper.AddPath(other->getPath(), ClipperLib::ptClip, true);
			ClipperLib::Paths solution;
			clipper.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

			other->clearHighlights(false, true);
			if (solution.size() >= 1) {
				std::vector<int> sidesToHL;
				for (ClipperLib::Path& path : solution) {
					for (ClipperLib::IntPoint& point : path)
						other->highlightLine(other->getSideContainingPoint(point.X, point.Y));
				}
			}
			return (solution.size() >= 1);
		}
		bool PolygonalCollider::doesPathCollide(std::vector<PolygonalCollider*> others, double offsetX, double offsetY, double toX, double toY)
		{
			for (PolygonalCollider* other : others) {
				std::vector<PolygonalCollider*> toExclude;
				if (isATagExcluded(other->getAllTags()))
					toExclude.push_back(other);
				for (PolygonalCollider* exclCol : toExclude)
					Functions::Vector::eraseAll(others, exclCol);
			}

			Collision::PolygonalCollider projection(this->id + "_proj");
			for (DoublePoint point : allPoints)
				projection.addPoint(point.first + toX, point.second + toY);
			this->move(offsetX, offsetY);
			Collision::PolygonalCollider fullPath = this->joinPolygonalColliders(this->id + "_path", &projection);
			this->move(-offsetX, -offsetY);

			ClipperLib::Clipper clipper;
			clipper.AddPath(fullPath.getPath(), ClipperLib::ptSubject, true);
			for (PolygonalCollider* other : others) {
				if (other != this)
					clipper.AddPath(other->getPath(), ClipperLib::ptClip, true);
			}

			ClipperLib::Paths solution;
			clipper.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

			return (solution.size() >= 1);
		}
		int PolygonalCollider::getSideContainingPoint(int x, int y) {
			for (int i = 0; i < allPoints.size(); i++) {
				int nextNode = (i != allPoints.size() - 1) ? i + 1 : 0;
				double lineLength = this->getDistanceFromPoint(i, this->getPointPosition(nextNode).first, this->getPointPosition(nextNode).second);
				double firstLength = this->getDistanceFromPoint(i, x, y);
				double secondLength = this->getDistanceFromPoint(nextNode, x, y);
				if (Functions::Math::isBetween(lineLength, firstLength + secondLength - 0.01, firstLength + secondLength + 0.01))
					return i;
			}
			return -1;
		}
		ClipperLib::Path PolygonalCollider::getPath() {
			ClipperLib::Path buildPath;
			for (DoublePoint& point : allPoints)
				buildPath << ClipperLib::IntPoint(point.first, point.second);
			return buildPath;
		}
		std::vector<DoublePoint> PolygonalCollider::getAllPoints() {
			return allPoints;
		}
		int PolygonalCollider::hasPoint(int x, int y, int toleranceX, int toleranceY)
		{
			for (unsigned int i = 0; i < allPoints.size(); i++) {
				if (Functions::Math::isBetween(x, (int)allPoints[i].first - toleranceX, (int)allPoints[i].first + toleranceX)) {
					if (Functions::Math::isBetween(y, (int)allPoints[i].second - toleranceY, (int)allPoints[i].second + toleranceY))
						return i;
				}
			}
			return -1;
		}
		bool PolygonalCollider::hasMasterPoint(int x, int y, int toleranceX, int toleranceY)
		{
			if (Functions::Math::isBetween(x, (int)masterPoint.first - toleranceX, (int)masterPoint.first + toleranceX)) {
				if (Functions::Math::isBetween(y, (int)masterPoint.second - toleranceY, (int)masterPoint.second + toleranceY))
					return true;
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
				p2 = 0;
			std::pair<int, int> p1coords = this->getPointPosition(p1);
			std::pair<int, int> p2coords = this->getPointPosition(p2);
			int deltaX = p2coords.first - p1coords.first;
			int deltaY = p2coords.second - p1coords.second;
			return (std::atan2(deltaY, deltaX) * 180 / Functions::Math::pi);
		}
		double PolygonalCollider::getSideLength(int side)
		{
			int p1 = side;
			int p2 = side + 1;
			if (p1 == allPoints.size() - 1)
				p2 = 0;
			std::pair<int, int> p1coords = this->getPointPosition(p1);
			std::pair<int, int> p2coords = this->getPointPosition(p2);
			return std::sqrt(std::pow(p1coords.first - p2coords.first, 2) + std::pow(p1coords.second - p2coords.second, 2));
		}
		void PolygonalCollider::draw(sf::RenderWindow* surf, bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel)
		{
			if (allPoints.size() >= 1) {
				sf::CircleShape polyPt;
				int r = 6;
				polyPt.setRadius(r);
				polyPt.setPointCount(100);
				if (!selected) polyPt.setFillColor(sf::Color(255, 150, 0));
				if (selected) polyPt.setFillColor(sf::Color(0, 150, 255));
				if (drawMasterPoint) {
					polyPt.setPosition(sf::Vector2f(masterPoint.first + drOffX - r, masterPoint.second + drOffY - r));
					surf->draw(polyPt);
				}
				polyPt.setFillColor(sf::Color(255, 255, 255));
				for (int i = 0; i < allPoints.size(); i++) {
					int nextIndex = (i == allPoints.size() - 1) ? 0 : i + 1;

					int x1 = allPoints[i].first + drOffX;
					int y1 = allPoints[i].second + drOffY;
					if (drawSkel) {
						if (!selected) 
							Collision::drawLine(surf, x1, y1, masterPoint.first + drOffX, masterPoint.second + drOffY, 2, sf::Color(255, 200, 0));
						if (selected) 
							Collision::drawLine(surf, x1, y1, masterPoint.first + drOffX, masterPoint.second + drOffY, 2, sf::Color(0, 200, 255));
					}
					if (drawLines) {
						if (!Functions::Vector::isInList(i, highlightedLines)) {
							if (parent == nullptr)
								Collision::drawLine(surf, allPoints[i].first + drOffX, allPoints[i].second + drOffY, 
									allPoints[nextIndex].first + drOffX, allPoints[nextIndex].second + drOffY);
							else
								Collision::drawLine(surf, allPoints[i].first + drOffX, allPoints[i].second + drOffY, 
									allPoints[nextIndex].first + drOffX, allPoints[nextIndex].second + drOffY, 2, sf::Color(255, 0, 255));
						}
						else
							Collision::drawLine(surf, allPoints[i].first + drOffX, allPoints[i].second + drOffY, 
								allPoints[nextIndex].first + drOffX, allPoints[nextIndex].second + drOffY, 2, sf::Color(0, 255, 0));
					}
					if (drawPoints) {
						polyPt.setPosition(sf::Vector2f(allPoints[i].first + drOffX - r, allPoints[i].second + drOffY - r));
						if (i == 0 && Functions::Vector::isInList(i, highlightedPoints) && selected)
							polyPt.setFillColor(sf::Color(255, 255, 0));
						else if (i == 0 && selected)
							polyPt.setFillColor(sf::Color(0, 255, 0));
						else if (Functions::Vector::isInList(i, highlightedPoints) && selected)
							polyPt.setFillColor(sf::Color(255, 0, 0));
						else
							polyPt.setFillColor(sf::Color(255, 255, 255));
						surf->draw(polyPt);
					}
				}
			}
		}
		DoublePoint PolygonalCollider::getPosition()
		{
			return allPoints[0];
		}
		void PolygonalCollider::move(double x, double y)
		{
			if (allPoints.size() > 0) {
				masterPoint.first += x;
				masterPoint.second += y;
				for (DoublePoint& point : allPoints) {
					point.first += x; 
					point.second += y;
				}
			}
		}
		void PolygonalCollider::setPosition(double x, double y)
		{
			if (allPoints.size() > 0) {
				double addX = x - allPoints[0].first;
				double addY = y - allPoints[0].second;
				masterPoint.first += addX;
				masterPoint.second += addY;
				allPoints[0].first = x;
				allPoints[0].second = y;
				for (int i = 1; i < allPoints.size(); i++) {
					allPoints[i].first += addX; 
					allPoints[i].second += addY;
				}
			}
		}
		void PolygonalCollider::setPositionFromMaster(double x, double y)
		{
			if (allPoints.size() > 0) {
				double addX = x - masterPoint.first;
				double addY = y - masterPoint.second;
				masterPoint.first = x;
				masterPoint.second = y;
				for (DoublePoint& point : allPoints) {
					point.first += addX; 
					point.second += addY;
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

		Script::GameObject* PolygonalCollider::getParent()
		{
			return parent;
		}

		void PolygonalCollider::setParent(Script::GameObject* parent)
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
				for (int i = 0; i < polyA.size(); i++) {
					if (addr == polyA[i])
						return i;
				}
				for (int i = 0; i < polyB.size(); i++) {
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
			for (int i = 0; i < conv.size(); i++) {
				ClipperLib::IntPoint *a, *b;
				a = conv[i]; b = conv[(i + 1) % conv.size()];
				result.addPoint(a->X, a->Y);
				for (int poly = 0; poly < polys.size(); poly++) {
					if (Functions::Vector::isInList(a, polys[poly]) && Functions::Vector::isInList(b, polys[poly])) {
						int iA = findFromAddress(a);
						int iB = findFromAddress(b);
						int counter = 0;
						while ((iA + counter) % polys[poly].size() != iB) {
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
			for (PolygonalCollider* collider : collidersList) {
				if (collider != this) {
					if (this->doesCollide(collider, offx, offy)) {
						//if (opt && i != 0) std::swap(collidersList->at(0), collidersList->at(i)); //Won't work if sent by copy
						return true;
					}
				}
			}
			return false;
		}
		void PolygonalCollider::addTag(std::string tag)
		{
			if (!Functions::Vector::isInList(tag, tags))
				tags.push_back(tag);
			else
				std::cout << "<Warning:Collisions:PolygonalCollider>[addTag] : Tag \'" << tag << "\" is already in PolygonalCollider \"" << id << "\"" << std::endl;
		}
		void PolygonalCollider::addExcludedTag(std::string tag)
		{
			if (!Functions::Vector::isInList(tag, excludedTags))
				excludedTags.push_back(tag);
			else
				std::cout << "<Warning:Collisions:PolygonalCollider>[addExcludedTag] : Tag \'" << tag << "\" is already in PolygonalCollider \"" << id << "\"" << std::endl;
		}
		void PolygonalCollider::addAcceptedTag(std::string tag)
		{
			if (!Functions::Vector::isInList(tag, acceptedTags))
				acceptedTags.push_back(tag);
			else
				std::cout << "<Warning:Collisions:PolygonalCollider>[addAcceptedTag] : Tag \'" << tag << "\" is already in PolygonalCollider \"" << id << "\"" << std::endl;
		}
		void PolygonalCollider::clearTags()
		{
			tags.clear();
		}
		void PolygonalCollider::clearExcludedTags()
		{
			excludedTags.clear();
		}
		void PolygonalCollider::clearAcceptedTags()
		{
			acceptedTags.clear();
		}
		void PolygonalCollider::removeTag(std::string tag)
		{
			Functions::Vector::eraseAll(tags, tag);
		}
		void PolygonalCollider::removeExcludedTag(std::string tag)
		{
			Functions::Vector::eraseAll(excludedTags, tag);
		}
		void PolygonalCollider::removeAcceptedTag(std::string tag)
		{
			Functions::Vector::eraseAll(acceptedTags, tag);
		}
		bool PolygonalCollider::doesHaveTag(std::string tag)
		{
			return Functions::Vector::isInList(tag, tags);
		}
		bool PolygonalCollider::isTagExcluded(std::string tag)
		{
			return Functions::Vector::isInList(tag, excludedTags);
		}
		bool PolygonalCollider::isTagAccepted(std::string tag)
		{
			return Functions::Vector::isInList(tag, acceptedTags);
		}
		bool PolygonalCollider::doesHaveAnyTag(std::vector<std::string>* tags)
		{
			if (this->tags.size() == 0) return false;
			for (std::string tag : *tags)
			{
				if (Functions::Vector::isInList(tag, this->tags))
					return true;
			}
			return false;
		}
		bool PolygonalCollider::isATagExcluded(std::vector<std::string>* tags)
		{
			if (excludedTags.size() == 0) return false;
			for (std::string tag : *tags) 
			{
				if (Functions::Vector::isInList(tag, excludedTags))
					return true;
			}
			return false;
		}
		bool PolygonalCollider::isATagAccepted(std::vector<std::string>* tags)
		{
			if (acceptedTags.size() == 0) return true;
			for (std::string tag : *tags)
			{
				if (Functions::Vector::isInList(tag, acceptedTags)) 
					return true;
			}
			return false;
		}
		std::vector<std::string>* PolygonalCollider::getAllTags()
		{
			return &tags;
		}
		std::vector<std::string>* PolygonalCollider::getAllExcludedTags()
		{
			return &excludedTags;
		}
		std::vector<std::string>* PolygonalCollider::getAllAcceptedTags()
		{
			return &acceptedTags;
		}
		bool PolygonalCollider::doesCollideWithTags(std::vector<Collision::PolygonalCollider*> collidersList, std::vector<std::string> tags, double offx, double offy)
		{
			std::vector<std::string> acceptedTagsBuffer = acceptedTags;
			std::vector<std::string> excludedTagsBuffer = excludedTags;
			clearExcludedTags();
			acceptedTags = tags;
			bool result = testAllColliders(collidersList, offx, offy, true);
			acceptedTags = acceptedTagsBuffer;
			excludedTags = excludedTagsBuffer;
			return result;
		}
	}
}