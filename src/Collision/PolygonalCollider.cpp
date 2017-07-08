#include <cmath>

#include <vili/ErrorHandler.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Types/Any.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Collision
    {
        bool pointsCompare(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt)
        {
            if (firstPt->X < secondPt->X)
                return true;
            if (firstPt->X == secondPt->X)
            {
                if (firstPt->Y <= secondPt->Y)
                    return false;
                return true;
            }
            return false;
        }

        double pointsDistance(const ClipperLib::IntPoint* firstPt, const ClipperLib::IntPoint* secondPt)
        {
            return std::sqrt(std::pow(secondPt->X - firstPt->X, 2) + std::pow(secondPt->Y - firstPt->Y, 2));
        }

        std::vector<ClipperLib::IntPoint*> convexHull(std::vector<ClipperLib::IntPoint*> points)
        {
            sort(points.begin(), points.end(), pointsCompare);
            if (points.size() <= 1)
                return points;
            std::vector<ClipperLib::IntPoint*> lowerHull;
            for (ClipperLib::IntPoint* point : points)
            {
                while (lowerHull.size() >= 2 && cross(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1], point) <= 0)
                    lowerHull.pop_back();
                lowerHull.push_back(point);
            }
            reverse(points.begin(), points.end());
            std::vector<ClipperLib::IntPoint*> upperHull;
            for (ClipperLib::IntPoint* point : points)
            {
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

        PolygonalCollider::PolygonalCollider(const std::string& id) : Selectable(false), Identifiable(id)
        {
        }

        PolygonalCollider::~PolygonalCollider()
        {
            this->clearOriginChildren();
            this->removeOrigin();
        }

        int PolygonalCollider::getPointsAmount() const
        {
            return m_allPoints.size();
        }

        ClipperLib::IntPoint PolygonalCollider::getPointPosition(int index)
        {
            return m_allPoints[index];
        }

        ClipperLib::IntPoint PolygonalCollider::getPointRelativePosition(int index)
        {
            return ClipperLib::IntPoint(m_allPoints[index].X - m_allPoints[0].X, m_allPoints[index].Y - m_allPoints[0].Y);
        }

        ClipperLib::IntPoint PolygonalCollider::getMasterPointPosition() const
        {
            return m_masterPoint;
        }

        void PolygonalCollider::calculateMasterPoint()
        {
            m_masterPoint = {0, 0};
            double signedArea = 0.0;
            double x0, y0, x1, y1, a;

            int i;
            for (i = 0; i < m_allPoints.size() - 1; ++i)
            {
                x0 = m_allPoints[i].X;
                y0 = m_allPoints[i].Y;
                x1 = m_allPoints[i + 1].X;
                y1 = m_allPoints[i + 1].Y;
                a = x0 * y1 - x1 * y0;
                signedArea += a;
                m_masterPoint.X += (x0 + x1) * a;
                m_masterPoint.Y += (y0 + y1) * a;
            }

            x0 = m_allPoints[i].X;
            y0 = m_allPoints[i].Y;
            x1 = m_allPoints[0].X;
            y1 = m_allPoints[0].Y;
            a = x0 * y1 - x1 * y0;
            signedArea += a;
            m_masterPoint.X += (x0 + x1) * a;
            m_masterPoint.Y += (y0 + y1) * a;

            signedArea *= 0.5;
            m_masterPoint.X /= (6.0 * signedArea);
            m_masterPoint.Y /= (6.0 * signedArea);
        }

        std::vector<std::string>& PolygonalCollider::retrieveTagVector(ColliderTagType tagType)
        {
            switch (tagType)
            {
            case ColliderTagType::Tag: return m_tags;
            case ColliderTagType::Accepted: return m_acceptedTags;
            case ColliderTagType::Rejected: return m_rejectedTags;
            default: ;
            }
        }

        void PolygonalCollider::addPoint(int x, int y, int pointIndex)
        {
            if (pointIndex == -1 || pointIndex == m_allPoints.size())
                m_allPoints.emplace_back(x, y);
            else if (pointIndex >= 0 && pointIndex < m_allPoints.size())
                m_allPoints.insert(m_allPoints.begin() + pointIndex, ClipperLib::IntPoint(x, y));
            if (m_allPoints.size() >= 3)
                calculateMasterPoint();
        }

        void PolygonalCollider::deletePoint(int pointIndex)
        {
            m_allPoints.erase(m_allPoints.begin() + pointIndex);
            this->calculateMasterPoint();
        }

        double PolygonalCollider::getDistanceFromPoint(int nodeIndex, int x, int y)
        {
            return std::sqrt(std::pow((x - m_allPoints[nodeIndex].X), 2) + std::pow((y - m_allPoints[nodeIndex].Y), 2));
        }

        int PolygonalCollider::findClosestPoint(int x, int y, bool neighboor, std::vector<int> excludedNodes)
        {
            if (m_allPoints.size() > 0)
            {
                int closestNode = 0;
                double currentPointDist;
                double tiniestDist = -1;
                for (unsigned int i = 0; i < m_allPoints.size(); i++)
                {
                    currentPointDist = this->getDistanceFromPoint(i, x, y);
                    if ((tiniestDist == -1 || tiniestDist > currentPointDist) && !Utils::Vector::isInList(static_cast<int>(i), excludedNodes))
                    {
                        closestNode = i;
                        tiniestDist = currentPointDist;
                    }
                }
                if (neighboor)
                {
                    int leftNeighbor = closestNode - 1;
                    int rightNeighbor = closestNode + 1;
                    if (leftNeighbor < 0)
                        leftNeighbor = m_allPoints.size() - 1;
                    if (rightNeighbor >= m_allPoints.size())
                        rightNeighbor = 0;
                    int leftNeighborDist = std::sqrt(std::pow((x - m_allPoints[leftNeighbor].X), 2) +
                        std::pow((y - m_allPoints[leftNeighbor].Y), 2));
                    int rightNeighborDist = std::sqrt(std::pow((x - m_allPoints[rightNeighbor].X), 2) +
                        std::pow((y - m_allPoints[rightNeighbor].Y), 2));
                    if (leftNeighborDist > rightNeighborDist)
                    {
                        closestNode++;
                        if (closestNode >= m_allPoints.size())
                            closestNode = 0;
                    }
                }
                return closestNode;
            }
            return -1;
        }

        bool PolygonalCollider::doesCollide(PolygonalCollider* other, int offsetX, int offsetY)
        {
            //std::cout << m_id << " Test collision with : " << other->getID() << std::endl;
            if (this->doesHaveAnyTag(ColliderTagType::Rejected, other->getAllTags(ColliderTagType::Tag)))
                return false;
            if (!this->doesHaveAnyTag(ColliderTagType::Accepted, other->getAllTags(ColliderTagType::Tag)))
                return false;

            ClipperLib::Path pPath = this->getAllPoints();
            //std::cout << "ME" << std::endl;
            for (int i = 0; i < m_allPoints.size(); i++)
            {
                pPath[i].X += offsetX;
                pPath[i].Y += offsetY;
                //std::cout << "Point : " << pPath[i].X << ", " << pPath[i].X << std::endl;
            }

            //std::cout << "OTHER" << std::endl;
            /*for (int i = 0; i < other->getAllPoints().size(); i++)
                std::cout << other->getAllPoints()[i].X << ", " << other->getAllPoints()[i].Y << std::endl;*/
            ClipperLib::Clipper clipper;
            clipper.AddPath(pPath, ClipperLib::ptSubject, true);
            clipper.AddPath(other->getAllPoints(), ClipperLib::ptClip, true);
            ClipperLib::Paths solution;
            clipper.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

            other->clearHighlights(false, true);
            if (solution.size() >= 1)
            {
                for (ClipperLib::Path& path : solution)
                {
                    for (ClipperLib::IntPoint& point : path)
                        other->highlightLine(other->getSideContainingPoint(point.X, point.Y));
                }
            }
            return (solution.size() >= 1);
        }

        bool PolygonalCollider::doesPathCollide(std::vector<PolygonalCollider*> others, int offsetX, int offsetY, int toX, int toY)
        {
            std::vector<PolygonalCollider*> toExclude;
            for (PolygonalCollider* other : others)
            {
                if (this->doesHaveAnyTag(ColliderTagType::Rejected, other->getAllTags(ColliderTagType::Tag)))
                {
                    toExclude.push_back(other);
                }
            }
            for (PolygonalCollider* exclCol : toExclude)
                Utils::Vector::eraseAll(others, exclCol);

            PolygonalCollider projection(m_id + "_proj");
            for (ClipperLib::IntPoint& point : m_allPoints)
                projection.addPoint(point.X + toX, point.Y + toY);
            this->move(offsetX, offsetY);
            PolygonalCollider fullPath = this->joinPolygonalColliders(m_id + "_path", &projection);
            this->move(-offsetX, -offsetY);

            ClipperLib::Clipper clipper;
            clipper.AddPath(fullPath.getAllPoints(), ClipperLib::ptSubject, true);
            for (PolygonalCollider* other : others)
            {
                if (other != this)
                    clipper.AddPath(other->getAllPoints(), ClipperLib::ptClip, true);
            }

            ClipperLib::Paths solution;
            clipper.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

            return (solution.size() >= 1);
        }

        int PolygonalCollider::getSideContainingPoint(int x, int y)
        {
            for (int i = 0; i < m_allPoints.size(); i++)
            {
                int nextNode = (i != m_allPoints.size() - 1) ? i + 1 : 0;
                double lineLength = this->getDistanceFromPoint(i, this->getPointPosition(nextNode).X, this->getPointPosition(nextNode).Y);
                double firstLength = this->getDistanceFromPoint(i, x, y);
                double secondLength = this->getDistanceFromPoint(nextNode, x, y);
                if (Utils::Math::isBetween(lineLength, firstLength + secondLength - 0.01, firstLength + secondLength + 0.01))
                    return i;
            }
            return -1;
        }

        ClipperLib::Path PolygonalCollider::getAllPoints() const
        {
            return m_allPoints;
        }

        int PolygonalCollider::hasPoint(int x, int y, int toleranceX, int toleranceY)
        {
            for (unsigned int i = 0; i < m_allPoints.size(); i++)
            {
                if (Utils::Math::isBetween(x, static_cast<int>(m_allPoints[i].X) - toleranceX, static_cast<int>(m_allPoints[i].X) + toleranceX))
                {
                    if (Utils::Math::isBetween(y, static_cast<int>(m_allPoints[i].Y) - toleranceY, static_cast<int>(m_allPoints[i].Y) + toleranceY))
                        return i;
                }
            }
            return -1;
        }

        bool PolygonalCollider::hasMasterPoint(int x, int y, int toleranceX, int toleranceY) const
        {
            if (Utils::Math::isBetween(x, static_cast<int>(m_masterPoint.X) - toleranceX, static_cast<int>(m_masterPoint.X) + toleranceX))
            {
                if (Utils::Math::isBetween(y, static_cast<int>(m_masterPoint.Y) - toleranceY, static_cast<int>(m_masterPoint.Y) + toleranceY))
                    return true;
            }
            return false;
        }

        void PolygonalCollider::movePoint(int index, int x, int y)
        {
            m_allPoints[index].X += x;
            m_allPoints[index].Y += y;
            calculateMasterPoint();
        }

        void PolygonalCollider::setPointPosition(int index, int x, int y)
        {
            m_allPoints[index].X = x;
            m_allPoints[index].Y = y;
            calculateMasterPoint();
        }

        void PolygonalCollider::setPointRelativePosition(int index, int x, int y)
        {
            m_allPoints[index].X = x + m_allPoints[0].X;
            m_allPoints[index].Y = y + m_allPoints[0].Y;
            calculateMasterPoint();
        }

        void PolygonalCollider::setPointPositionFromMaster(int index, int x, int y)
        {
            m_allPoints[index].X = x + m_masterPoint.X;
            m_allPoints[index].Y = y + m_masterPoint.Y;
            calculateMasterPoint();
        }

        void PolygonalCollider::u_move(const Transform::UnitVector& vec)
        {
            Transform::UnitVector pVec = vec.to<Transform::Units::WorldPixels>();
            this->move(pVec.x, pVec.y);
        }

        void PolygonalCollider::u_setPosition(const Transform::UnitVector& vec)
        {
            Transform::UnitVector pVec = vec.to<Transform::Units::WorldPixels>();
            this->setPosition(pVec.x, pVec.y);
        }

        void PolygonalCollider::u_setPositionFromMaster(const Transform::UnitVector& vec)
        {
            Transform::UnitVector pVec = vec.to<Transform::Units::WorldPixels>();
            this->setPositionFromMaster(pVec.x, pVec.y);
        }

        void PolygonalCollider::u_movePoint(int index, const Transform::UnitVector& vec)
        {
            Transform::UnitVector pVec = vec.to<Transform::Units::WorldPixels>();
            this->movePoint(index, pVec.x, pVec.y);
        }

        void PolygonalCollider::u_setPointPosition(int index, const Transform::UnitVector& vec)
        {
            Transform::UnitVector pVec = vec.to<Transform::Units::WorldPixels>();
            this->setPointPosition(index, pVec.x, pVec.y);
        }

        void PolygonalCollider::u_setPointRelativePosition(int index, const Transform::UnitVector& vec)
        {
            Transform::UnitVector pVec = vec.to<Transform::Units::WorldPixels>();
            this->setPointRelativePosition(index, pVec.x, pVec.y);
        }

        void PolygonalCollider::u_setPointPositionFromMaster(int index, const Transform::UnitVector& vec)
        {
            Transform::UnitVector pVec = vec.to<Transform::Units::WorldPixels>();
            this->setPointPositionFromMaster(index, pVec.x, pVec.y);
        }

        double PolygonalCollider::getSideAngle(int side)
        {
            int p1 = side;
            int p2 = side + 1;
            if (p1 == m_allPoints.size() - 1)
                p2 = 0;
            ClipperLib::IntPoint p1coords = this->getPointPosition(p1);
            ClipperLib::IntPoint p2coords = this->getPointPosition(p2);
            int deltaX = p2coords.X - p1coords.X;
            int deltaY = p2coords.Y - p1coords.Y;
            return (atan2(deltaY, deltaX) * 180 / Utils::Math::pi);
        }

        double PolygonalCollider::getSideLength(int side)
        {
            int p1 = side;
            int p2 = side + 1;
            if (p1 == m_allPoints.size() - 1)
                p2 = 0;
            ClipperLib::IntPoint p1coords = this->getPointPosition(p1);
            ClipperLib::IntPoint p2coords = this->getPointPosition(p2);
            return std::sqrt(std::pow(p1coords.X - p2coords.X, 2) + std::pow(p1coords.Y - p2coords.Y, 2));
        }

        void PolygonalCollider::draw(sf::RenderWindow& target, int offsetX, int offsetY, bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel)
        {
            if (m_allPoints.size() >= 1)
            {
                std::map<std::string, Types::Any> drawOptions;
                
                int r = 6;
                
                drawOptions["lines"] = drawLines;
                drawOptions["points"] = drawPoints;
                drawOptions["radius"] = r;
                drawOptions["point_color"] = sf::Color::White;

                std::vector<sf::Vector2i> drawPoints;

                for (int i = 0; i < m_allPoints.size(); i++)
                {
                    ClipperLib::IntPoint& point = m_allPoints[i];

                    if (Utils::Vector::isInList(i, m_highlightedPoints) && m_selected)
                        drawOptions["point_color_" + std::to_string(i)] = sf::Color(255, 0, 0);
                    else
                        drawOptions["point_color_" + std::to_string(i)] = sf::Color(255, 255, 255);
                    drawPoints.emplace_back(point.X + offsetX, point.Y + offsetY);
                }

                if (Utils::Vector::isInList(0, m_highlightedPoints) && m_selected)
                    drawOptions["point_color_0"] = sf::Color(255, 255, 0);
                else if (m_selected)
                    drawOptions["point_color_0"] = sf::Color(0, 255, 0);

                if (drawMasterPoint)
                {
                    sf::CircleShape polyPt;
                    polyPt.setPosition(sf::Vector2f(m_masterPoint.X + offsetX - r, m_masterPoint.Y + offsetY - r));
                    polyPt.setRadius(r);
                    sf::Color polyPtColor = m_selected ? sf::Color(0, 150, 255) : sf::Color(255, 150, 0);
                    polyPt.setFillColor(polyPtColor);
                    target.draw(polyPt);
                    if (drawSkel)
                    {
                        for (ClipperLib::IntPoint& point : m_allPoints)
                        {
                            sf::Color currentLineColor = m_selected ? sf::Color(0, 200, 255) : sf::Color(255, 200, 0);
                            Graphics::Utils::drawLine(target,
                                point.X + offsetX, point.Y + offsetY,
                                m_masterPoint.X + offsetX, m_masterPoint.Y + offsetY,
                                2, currentLineColor);
                        }
                    }
                }
                Graphics::Utils::drawPolygon(target, drawPoints, drawOptions);
            }
        }

        ClipperLib::IntPoint PolygonalCollider::getPosition()
        {
            return m_allPoints[0];
        }

        Transform::UnitVector PolygonalCollider::u_getPosition()
        {
            return Transform::UnitVector(m_allPoints[0].X, m_allPoints[0].Y, Transform::Units::WorldPixels).to(m_unit);
        }

        Transform::UnitVector PolygonalCollider::u_getPointPosition(int index)
        {
            return Transform::UnitVector(m_allPoints[index].X, m_allPoints[index].Y, Transform::Units::WorldPixels).to(m_unit);
        }

        Transform::UnitVector PolygonalCollider::u_getPointRelativePosition(int index)
        {
            return Transform::UnitVector(m_allPoints[index].X - m_allPoints[0].X, m_allPoints[index].Y - m_allPoints[0].Y, Transform::Units::WorldPixels).to(m_unit);
        }

        Transform::UnitVector PolygonalCollider::u_getMasterPointPosition() const
        {
            return Transform::UnitVector(m_masterPoint.X, m_masterPoint.Y, Transform::Units::WorldPixels).to(m_unit);
        }

        void PolygonalCollider::move(int x, int y)
        {
            for (PolygonalCollider* child : m_originChildren)
                child->move(x, y);
            if (m_allPoints.size() > 0)
            {
                m_masterPoint.X += x;
                m_masterPoint.Y += y;
                for (ClipperLib::IntPoint& point : m_allPoints)
                {
                    point.X += x;
                    point.Y += y;
                }
            }
        }

        void PolygonalCollider::setPosition(int x, int y)
        {
            if (m_allPoints.size() > 0)
            {
                double addX = x - m_allPoints[0].X;
                double addY = y - m_allPoints[0].Y;
                for (PolygonalCollider* child : m_originChildren)
                    child->move(addX, addY);
                m_masterPoint.X += addX;
                m_masterPoint.Y += addY;
                m_allPoints[0].X = x;
                m_allPoints[0].Y = y;
                for (int i = 1; i < m_allPoints.size(); i++)
                {
                    m_allPoints[i].X += addX;
                    m_allPoints[i].Y += addY;
                }
            }
        }

        void PolygonalCollider::setPositionFromMaster(int x, int y)
        {
            if (m_allPoints.size() > 0)
            {
                double addX = x - m_masterPoint.X;
                double addY = y - m_masterPoint.Y;
                for (PolygonalCollider* child : m_originChildren)
                    child->move(addX, addY);
                m_masterPoint.X = x;
                m_masterPoint.Y = y;
                for (ClipperLib::IntPoint& point : m_allPoints)
                {
                    point.X += addX;
                    point.Y += addY;
                }
            }
        }

        void PolygonalCollider::highlightPoint(int pointIndex)
        {
            m_highlightedPoints.push_back(pointIndex);
        }

        void PolygonalCollider::highlightLine(int pointIndex)
        {
            m_highlightedLines.push_back(pointIndex);
        }

        void PolygonalCollider::clearHighlights(bool points, bool lines)
        {
            if (points) m_highlightedPoints.clear();
            if (lines) m_highlightedLines.clear();
        }

        std::string PolygonalCollider::getParentID() const
        {
            return m_parentID;
        }

        void PolygonalCollider::setParentID(const std::string& parent)
        {
            m_parentID = parent;
        }

        PolygonalCollider PolygonalCollider::joinPolygonalColliders(std::string joinID, PolygonalCollider* other)
        {
            ClipperLib::Path polyAPath = this->getAllPoints();
            std::vector<ClipperLib::IntPoint*> polyA;
            for (int i = 0; i < polyAPath.size(); i++)
                polyA.push_back(&polyAPath.at(i));
            ClipperLib::Path polyBPath = other->getAllPoints();
            std::vector<ClipperLib::IntPoint*> polyB;
            for (int i = 0; i < polyBPath.size(); i++)
                polyB.push_back(&polyBPath.at(i));
            std::vector<std::vector<ClipperLib::IntPoint*>> polys = {polyA, polyB};
            auto findFromAddress = [polyA, polyB](ClipperLib::IntPoint* addr) -> int
            {
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
            PolygonalCollider result(joinID);
            for (int i = 0; i < conv.size(); i++)
            {
                ClipperLib::IntPoint *a, *b;
                a = conv[i];
                b = conv[(i + 1) % conv.size()];
                result.addPoint(a->X, a->Y);
                for (int poly = 0; poly < polys.size(); poly++)
                {
                    if (Utils::Vector::isInList(a, polys[poly]) && Utils::Vector::isInList(b, polys[poly]))
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

        bool PolygonalCollider::testAllColliders(std::vector<PolygonalCollider*> collidersList, int offx, int offy, bool opt)
        {
            for (PolygonalCollider* collider : collidersList)
            {
                if (collider != this)
                {
                    if (this->doesCollide(collider, offx, offy))
                    {
                        //if (opt && i != 0) std::swap(collidersList->at(0), collidersList->at(i)); //Won't work if sent by copy
                        return true;
                    }
                }
            }
            return false;
        }

        std::vector<PolygonalCollider*> PolygonalCollider::getAllCollidedColliders(std::vector<PolygonalCollider*> collidersList, int offx, int offy)
        {
            std::vector<PolygonalCollider*> collided;
            for (PolygonalCollider* collider : collidersList)
            {
                if (collider != this)
                {
                    if (this->doesCollide(collider, offx, offy))
                    {
                        //if (opt && i != 0) std::swap(collidersList->at(0), collidersList->at(i)); //Won't work if sent by copy
                        collided.push_back(collider);
                    }
                }
            }
            return collided;
        }

        void PolygonalCollider::addOriginChild(PolygonalCollider* child)
        {
            m_originChildren.push_back(child);
        }

        void PolygonalCollider::removeOriginChild(PolygonalCollider* child, bool trigger)
        {
            if (Utils::Vector::isInList(child, m_originChildren))
            {
                for (int i = 0; i < m_originChildren.size(); i++)
                {
                    if (child == m_originChildren[i])
                    {
                        if (trigger) m_originChildren[i]->removeOrigin();
                        m_originChildren.erase(m_originChildren.begin() + i);
                        break;
                    }
                }
            }
        }

        void PolygonalCollider::clearOriginChildren()
        {
            for (int i = 0; i < m_originChildren.size(); i++)
            {
                m_originChildren[i]->removeOrigin();
            }
            m_originChildren.clear();
        }

        void PolygonalCollider::setOrigin(PolygonalCollider* origin)
        {
            if (m_origin != nullptr)
                m_origin->removeOriginChild(this, false);
            m_origin = origin;
            m_origin->addOriginChild(this);
        }

        PolygonalCollider* PolygonalCollider::getOrigin() const
        {
            return m_origin;
        }

        void PolygonalCollider::removeOrigin()
        {
            if (m_origin != nullptr)
            {
                m_origin->removeOriginChild(this, false);
            }
            m_origin = nullptr;
        }

        void PolygonalCollider::addTag(ColliderTagType tagType, const std::string& tag)
        {
            if (!Utils::Vector::isInList(tag, this->retrieveTagVector(tagType)))
                this->retrieveTagVector(tagType).push_back(tag);
            else
                std::cout << "<Warning:Collisions:PolygonalCollider>[addTag] : Tag \'" << tag << "\" is already in PolygonalCollider \"" << m_id << "\"" << std::endl;
        }

        void PolygonalCollider::clearTags(ColliderTagType tagType)
        {
            this->retrieveTagVector(tagType).clear();
        }

        void PolygonalCollider::removeTag(ColliderTagType tagType, const std::string& tag)
        {
            Utils::Vector::eraseAll(this->retrieveTagVector(tagType), tag);
        }

        bool PolygonalCollider::doesHaveTag(ColliderTagType tagType, const std::string& tag)
        {
            return Utils::Vector::isInList(tag, this->retrieveTagVector(tagType));
        }

        bool PolygonalCollider::doesHaveAnyTag(ColliderTagType tagType, const std::vector<std::string>& tags)
        {
            if (m_tags.size() == 0) return false;
            for (std::string tag : tags)
            {
                if (Utils::Vector::isInList(tag, this->retrieveTagVector(tagType)))
                    return true;
            }
            return false;
        }

        std::vector<std::string> PolygonalCollider::getAllTags(ColliderTagType tagType)
        {
            return this->retrieveTagVector(tagType);
        }

        bool PolygonalCollider::doesCollideWithTags(std::vector<PolygonalCollider*> collidersList, std::vector<std::string> tags, int offx, int offy)
        {
            std::vector<std::string> acceptedTagsBuffer = m_acceptedTags;
            std::vector<std::string> rejectedTagsBuffer = m_rejectedTags;
            this->clearTags(ColliderTagType::Rejected);
            m_acceptedTags = tags;
            bool result = testAllColliders(collidersList, offx, offy, true);
            m_acceptedTags = acceptedTagsBuffer;
            m_rejectedTags = rejectedTagsBuffer;
            return result;
        }

        std::vector<PolygonalCollider*> PolygonalCollider::getCollidedCollidersWithTags(std::vector<PolygonalCollider*> collidersList, std::vector<std::string> tags, int offx, int offy)
        {
            std::vector<std::string> acceptedTagsBuffer = m_acceptedTags;
            std::vector<std::string> rejectedTagsBuffer = m_rejectedTags;
            clearTags(ColliderTagType::Rejected);
            m_acceptedTags = tags;
            std::vector<PolygonalCollider*> collided = getAllCollidedColliders(collidersList, offx, offy);
            m_acceptedTags = acceptedTagsBuffer;
            m_rejectedTags = rejectedTagsBuffer;
            return collided;
        }
    }
}
