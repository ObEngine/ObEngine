#include <cmath>
#include <complex>
#include <limits>
#include <functional>

#include <SFML/Graphics/CircleShape.hpp>
#include <vili/ErrorHandler.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Types/Any.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Scene/Scene.hpp>
#include <Script/Script.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Collision
    {
        bool pointsCompare(const Transform::UnitVector& first, const Transform::UnitVector& second)
        {
            if (first.x < second.x)
                return true;
            if (first.x == second.x)
            {
                if (first.y <= second.y)
                    return false;
                return true;
            }
            return false;
        }

        double pointsDistance(const Transform::UnitVector& first, const Transform::UnitVector& second)
        {
            return std::sqrt(std::pow(second.x - first.x, 2) + std::pow(second.y - first.y, 2));
        }

        std::vector<Transform::UnitVector> convexHull(std::vector<Transform::UnitVector> points)
        {
            sort(points.begin(), points.end(), pointsCompare);
            if (points.size() <= 1)
                return points;
            std::vector<Transform::UnitVector> lowerHull;
            for (Transform::UnitVector& point : points)
            {
                while (lowerHull.size() >= 2 && cross(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1], point) <= 0)
                    lowerHull.pop_back();
                lowerHull.push_back(point);
            }
            reverse(points.begin(), points.end());
            std::vector<Transform::UnitVector> upperHull;
            for (Transform::UnitVector& point : points)
            {
                while (upperHull.size() >= 2 && cross(upperHull[upperHull.size() - 2], upperHull[upperHull.size() - 1], point) <= 0)
                    upperHull.pop_back();
                upperHull.push_back(point);
            }
            std::vector<Transform::UnitVector> fullHull;
            fullHull.reserve(lowerHull.size() + upperHull.size() - 2);
            fullHull.insert(fullHull.end(), lowerHull.begin(), lowerHull.end() - 1);
            fullHull.insert(fullHull.end(), upperHull.begin(), upperHull.end() - 1);
            return fullHull;
        }

        double cross(const Transform::UnitVector& O, const Transform::UnitVector& A, const Transform::UnitVector& B)
        {
            return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
        }

        PolygonalCollider::PolygonalCollider(const std::string& id) : Selectable(false), Identifiable(id)
        {
        }

        PolygonalCollider::~PolygonalCollider()
        {
            this->clearOriginChildren();
            this->removeOrigin();
        }

        void PolygonalCollider::resetUnit(Transform::Units unit)
        {
            for (Transform::UnitVector& point : m_allPoints)
            {
                point = point.to(unit);
            }
            std::cout << "Converted all Points" << std::endl;
        }

        unsigned int PolygonalCollider::getPointsAmount() const
        {
            return m_allPoints.size();
        }

        void PolygonalCollider::calculateMasterPoint()
        {
            m_masterPoint = {0, 0};
            double signedArea = 0.0;
            double x0, y0, x1, y1, a;

            int i;
            for (i = 0; i < m_allPoints.size() - 1; ++i)
            {
                x0 = m_allPoints[i].x;
                y0 = m_allPoints[i].y;
                x1 = m_allPoints[i + 1].x;
                y1 = m_allPoints[i + 1].y;
                a = x0 * y1 - x1 * y0;
                signedArea += a;
                m_masterPoint.x += (x0 + x1) * a;
                m_masterPoint.y += (y0 + y1) * a;
            }

            x0 = m_allPoints[i].x;
            y0 = m_allPoints[i].y;
            x1 = m_allPoints[0].x;
            y1 = m_allPoints[0].y;
            a = x0 * y1 - x1 * y0;
            signedArea += a;
            m_masterPoint.x += (x0 + x1) * a;
            m_masterPoint.y += (y0 + y1) * a;

            signedArea *= 0.5;
            m_masterPoint.x /= (6.0 * signedArea);
            m_masterPoint.y /= (6.0 * signedArea);
        }

        std::vector<std::string>& PolygonalCollider::retrieveTagVector(ColliderTagType tagType)
        {
            switch (tagType)
            {
            case ColliderTagType::Tag: return m_tags;
            case ColliderTagType::Accepted: return m_acceptedTags;
            case ColliderTagType::Rejected: return m_rejectedTags;
            }
        }

        void PolygonalCollider::addPoint(const Transform::UnitVector& position, int pointIndex)
        {
            Transform::UnitVector pVec = position.to(m_unit);
            if (pointIndex == -1 || pointIndex == m_allPoints.size())
                m_allPoints.push_back(pVec);
            else if (pointIndex >= 0 && pointIndex < m_allPoints.size())
                m_allPoints.insert(m_allPoints.begin() + pointIndex, pVec);
            if (m_allPoints.size() >= 3)
                calculateMasterPoint();
        }

        void PolygonalCollider::deletePoint(unsigned int pointIndex)
        {
            m_allPoints.erase(m_allPoints.begin() + pointIndex);
            this->calculateMasterPoint();
        }

        double PolygonalCollider::getDistanceFromPoint(unsigned int pointIndex, const Transform::UnitVector& position)
        {
            Transform::UnitVector pVec = position.to(m_unit);
            return std::sqrt(std::pow((pVec.x - m_allPoints[pointIndex].x), 2) + std::pow((pVec.y - m_allPoints[pointIndex].y), 2));
        }

        unsigned int PolygonalCollider::findClosestPoint(const Transform::UnitVector& position, bool neighboor, std::vector<int> excludedNodes)
        {
            if (m_allPoints.size() > 0)
            {
                Transform::UnitVector pVec = position.to(m_unit);
                int closestNode = 0;
                double tiniestDist = -1;
                for (unsigned int i = 0; i < m_allPoints.size(); i++)
                {
                    double currentPointDist = this->getDistanceFromPoint(i, pVec);
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
                    int leftNeighborDist = std::sqrt(std::pow((position.x - m_allPoints[leftNeighbor].x), 2) +
                        std::pow((position.y - m_allPoints[leftNeighbor].y), 2));
                    int rightNeighborDist = std::sqrt(std::pow((position.x - m_allPoints[rightNeighbor].x), 2) +
                        std::pow((position.y - m_allPoints[rightNeighbor].y), 2));
                    if (leftNeighborDist > rightNeighborDist)
                    {
                        closestNode++;
                        if (closestNode >= m_allPoints.size())
                            closestNode = 0;
                    }
                }
                return closestNode;
            }
        }

        unsigned int PolygonalCollider::findClosestLine(const Transform::UnitVector& position)
        {
            Transform::UnitVector p3 = position.to(m_unit);
            auto distanceLineFromPoint = [](const Transform::UnitVector& point, const Transform::UnitVector& lineP1, const Transform::UnitVector& lineP2)
            {
                Transform::UnitVector lineDiff = lineP2 - lineP1;
                if (lineDiff.x == 0 && lineDiff.y == 0)
                {
                    lineDiff = point - lineP1;
                    return sqrt(lineDiff.x * lineDiff.x + lineDiff.y * lineDiff.y);
                }

                double t = ((point.x - lineP1.x) * lineDiff.x + (point.y - lineP1.y) * lineDiff.y) / (lineDiff.x * lineDiff.x + lineDiff.y * lineDiff.y);

                if (t < 0)
                {
                    //point is nearest to the first point i.e x1 and y1
                    lineDiff = point - lineP1;
                }
                else if (t > 1)
                {
                    //point is nearest to the end point i.e x2 and y2
                    lineDiff = point - lineP2;
                }
                else
                {
                    //if perpendicular line intersect the line segment.
                    lineDiff.x = point.x - (lineP1.x + t * lineDiff.x);
                    lineDiff.y = point.y - (lineP1.y + t * lineDiff.y);
                }

                //returning shortest distance
                return sqrt(lineDiff.x * lineDiff.x + lineDiff.y * lineDiff.y);
            };
            double shortestDistance = -1;
            unsigned int shortestIndex;
            for (unsigned int i = 0, j = getAllPoints().size() - 1; i < getAllPoints().size(); j = i++)
            {
                Transform::UnitVector p1 = m_allPoints[i];
                Transform::UnitVector p2 = m_allPoints[j];
                std::complex<double> a(p2.x - p1.x, p2.y - p1.y);
                double currentDistance = distanceLineFromPoint(p3, p1, p2);
                if (shortestDistance == -1 || currentDistance < shortestDistance)
                {
                    shortestDistance = currentDistance;
                    shortestIndex = i;
                }
            }
            return shortestIndex;
        }

        int PolygonalCollider::getSideContainingPoint(const Transform::UnitVector& position)
        {
            double tolerance = 0.01;
            for (int i = 0; i < m_allPoints.size(); i++)
            {
                int nextNode = (i != m_allPoints.size() - 1) ? i + 1 : 0;
                double lineLength = this->getDistanceFromPoint(i, m_allPoints[nextNode]);
                double firstLength = this->getDistanceFromPoint(i, position);
                double secondLength = this->getDistanceFromPoint(nextNode, position);
                if (Utils::Math::isBetween(lineLength, firstLength + secondLength - tolerance, firstLength + secondLength + tolerance))
                    return i;
            }
            return -1;
        }

        std::vector<Transform::UnitVector> PolygonalCollider::getAllPoints() const
        {
            return m_allPoints;
        }

        int PolygonalCollider::hasPoint(const Transform::UnitVector& position, const Transform::UnitVector& tolerance)
        {
            Transform::UnitVector pVec = position.to(m_unit);
            Transform::UnitVector pTolerance = tolerance.to(m_unit);
            for (unsigned int i = 0; i < m_allPoints.size(); i++)
            {
                if (Utils::Math::isBetween(pVec.x, m_allPoints[i].x - pTolerance.x, m_allPoints[i].x + pTolerance.x))
                {
                    if (Utils::Math::isBetween(pVec.y, m_allPoints[i].y - pTolerance.y, m_allPoints[i].y + pTolerance.y))
                        return i;
                }
            }
            return -1;
        }

        bool PolygonalCollider::hasMasterPoint(const Transform::UnitVector& position, const Transform::UnitVector& tolerance) const
        {
            Transform::UnitVector pVec = position.to(m_unit);
            Transform::UnitVector pTolerance = tolerance.to(m_unit);
            if (Utils::Math::isBetween(pVec.x, m_masterPoint.x - pTolerance.x, m_masterPoint.x + pTolerance.x))
            {
                if (Utils::Math::isBetween(pVec.y, m_masterPoint.y - pTolerance.x, m_masterPoint.y + pTolerance.y))
                    return true;
            }
            return false;
        }

        void PolygonalCollider::movePoint(unsigned int index, const Transform::UnitVector& vec)
        {
            m_allPoints[index] += vec;
            calculateMasterPoint();
        }

        void PolygonalCollider::setPointPosition(unsigned int index, const Transform::UnitVector& vec)
        {
            m_allPoints[index] = vec.to(m_unit);
            calculateMasterPoint();
        }

        void PolygonalCollider::setPointRelativePosition(unsigned int index, const Transform::UnitVector& vec)
        {
            m_allPoints[index] = vec.to(m_unit) + m_allPoints[0];
            calculateMasterPoint();
        }

        void PolygonalCollider::setPointPositionFromMaster(unsigned int index, const Transform::UnitVector& vec)
        {
            m_allPoints[index] = vec.to(m_unit) + m_masterPoint;
            calculateMasterPoint();
        }

        double PolygonalCollider::getSideAngle(unsigned int side)
        {
            int p1 = side;
            int p2 = side + 1;
            if (p1 == m_allPoints.size() - 1)
                p2 = 0;
            Transform::UnitVector p1coords = this->getPointPosition(p1);
            Transform::UnitVector p2coords = this->getPointPosition(p2);
            double deltaX = p2coords.x - p1coords.x;
            double deltaY = p2coords.y - p1coords.y;
            return (atan2(deltaY, deltaX) * 180.0 / Utils::Math::pi);
        }

        double PolygonalCollider::getSideLength(unsigned int side)
        {
            int p1 = side;
            int p2 = side + 1;
            if (p1 == m_allPoints.size() - 1)
                p2 = 0;
            Transform::UnitVector p1coords = this->getPointPosition(p1);
            Transform::UnitVector p2coords = this->getPointPosition(p2);
            return std::sqrt(std::pow(p1coords.x - p2coords.x, 2) + std::pow(p1coords.y - p2coords.y, 2));
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
                    Transform::UnitVector point = m_allPoints[i].to<Transform::Units::WorldPixels>();

                    if (Utils::Vector::isInList(i, m_highlightedPoints) && m_selected)
                        drawOptions["point_color_" + std::to_string(i)] = sf::Color(255, 0, 0);
                    if (Utils::Vector::isInList((i != m_allPoints.size() - 1) ? i + 1 : 0, m_highlightedLines) && m_selected)
                        drawOptions["line_color_" + std::to_string(i)] = sf::Color(0, 255, 0);

                    drawPoints.emplace_back(point.x + offsetX, point.y + offsetY);
                }

                if (Utils::Vector::isInList(0, m_highlightedPoints) && m_selected)
                    drawOptions["point_color_0"] = sf::Color(255, 255, 0);
                else if (m_selected)
                    drawOptions["point_color_0"] = sf::Color(0, 255, 0);

                if (drawMasterPoint)
                {
                    sf::CircleShape polyPt;
                    Transform::UnitVector pMaster = m_masterPoint.to<Transform::Units::WorldPixels>();
                    polyPt.setPosition(sf::Vector2f(pMaster.x + offsetX - r, pMaster.y + offsetY - r));
                    polyPt.setRadius(r);
                    sf::Color polyPtColor = m_selected ? sf::Color(0, 150, 255) : sf::Color(255, 150, 0);
                    polyPt.setFillColor(polyPtColor);
                    target.draw(polyPt);
                    if (drawSkel)
                    {
                        for (int i = 0; i < m_allPoints.size(); i++)
                        {
                            Transform::UnitVector point = m_allPoints[i].to<Transform::Units::WorldPixels>();
                            sf::Color currentLineColor = m_selected ? sf::Color(0, 200, 255) : sf::Color(255, 200, 0);
                            Graphics::Utils::drawLine(target,
                                                      point.x + offsetX, point.y + offsetY,
                                                      pMaster.x + offsetX, pMaster.y + offsetY,
                                                      2, currentLineColor);
                        }
                    }
                }
                Graphics::Utils::drawPolygon(target, drawPoints, drawOptions);
            }
        }

        Transform::UnitVector PolygonalCollider::getPosition()
        {
            return m_allPoints[0];
        }

        Transform::UnitVector PolygonalCollider::getPointPosition(unsigned int index)
        {
            return m_allPoints[index];
        }

        Transform::UnitVector PolygonalCollider::getPointRelativePosition(unsigned int index)
        {
            return m_allPoints[index] - m_allPoints[0];
        }

        Transform::UnitVector PolygonalCollider::getMasterPointPosition() const
        {
            return m_masterPoint;
        }

        void PolygonalCollider::move(const Transform::UnitVector& position)
        {
            for (PolygonalCollider* child : m_originChildren)
                child->move(position);
            if (m_allPoints.size() > 0)
            {
                m_masterPoint += position;
                for (Transform::UnitVector& point : m_allPoints)
                {
                    point += position;
                }
            }
        }

        void PolygonalCollider::setPosition(const Transform::UnitVector& position)
        {
            if (m_allPoints.size() > 0)
            {
                const Transform::UnitVector pVec = position.to(m_unit);
                const Transform::UnitVector addPosition = pVec - m_allPoints[0];
                for (PolygonalCollider* child : m_originChildren)
                    child->move(addPosition);
                m_masterPoint += addPosition;
                m_allPoints[0] = pVec;
                for (int i = 1; i < m_allPoints.size(); i++)
                {
                    m_allPoints[i] += addPosition;
                }
            }
        }

        void PolygonalCollider::setPositionFromMaster(const Transform::UnitVector& position)
        {
            if (m_allPoints.size() > 0)
            {
                const Transform::UnitVector pVec = position.to(m_unit);
                const Transform::UnitVector addPosition = pVec - m_masterPoint;
                for (PolygonalCollider* child : m_originChildren)
                    child->move(addPosition);
                m_masterPoint = pVec;
                for (Transform::UnitVector& point : m_allPoints)
                {
                    point += addPosition;
                }
            }
        }

        void PolygonalCollider::highlightPoint(unsigned int pointIndex)
        {
            m_highlightedPoints.push_back(pointIndex);
        }

        void PolygonalCollider::highlightLine(unsigned int pointIndex)
        {
            m_highlightedLines.push_back(pointIndex);
        }

        void PolygonalCollider::clearHighlights(bool points, bool lines)
        {
            if (points) m_highlightedPoints.clear();
            if (lines) m_highlightedLines.clear();
        }

        std::string PolygonalCollider::getParentId() const
        {
            return m_parentId;
        }

        void PolygonalCollider::setParentId(const std::string& parent)
        {
            m_parentId = parent;
        }

        /*PolygonalCollider PolygonalCollider::joinPolygonalColliders(std::string joinID, PolygonalCollider* other) const
        {
            /*std::vector<Transform::UnitVector> polyAPath = this->getAllPoints();
            std::vector<Transform::UnitVector> polyA;
            for (int i = 0; i < polyAPath.size(); i++)
                polyA.push_back(polyAPath.at(i));
            std::vector<Transform::UnitVector> polyBPath = other->getAllPoints();
            std::vector<Transform::UnitVector> polyB;
            for (int i = 0; i < polyBPath.size(); i++)
                polyB.push_back(polyBPath.at(i));
            std::vector<std::vector<Transform::UnitVector*>> polys = {polyA, polyB};
            auto findFromAddress = [polyA, polyB](Transform::UnitVector* addr) -> int
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
            std::vector<Transform::UnitVector> allPoints;
            allPoints.reserve(polyA.size() + polyB.size());
            allPoints.insert(allPoints.end(), polyA.begin(), polyA.end());
            allPoints.insert(allPoints.end(), polyB.begin(), polyB.end());
            std::vector<Transform::UnitVector*> conv = convexHull(allPoints);
            PolygonalCollider result(joinID);
            std::vector<Transform::UnitVector> finalPath;
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
                        int counter = 1;
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
        }*/

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


        Transform::UnitVector PolygonalCollider::getMaximumDistanceBeforeCollision(const PolygonalCollider& collider, const Transform::UnitVector& offset) const
        {
            if (/*!doesCollide(collider, Transform::UnitVector(0, 0))*/true)
            {
                std::cout << "Accept Chall ===============================>" << std::endl;
                const Transform::UnitVector tOffset = offset.to(m_unit);
                bool inFront = false;
                Transform::UnitVector minDep;
                auto calcMinDistanceDep = [this](PolygonPath& sol1, PolygonPath& sol2, const Transform::UnitVector& tOffset) -> std::tuple<double, Transform::UnitVector, bool>
                {
                    double minDistance = -1;
                    bool inFront = false;
                    Transform::UnitVector minDeplacement(m_unit);
                    Transform::UnitVector point1(m_unit);
                    Transform::UnitVector point2(m_unit);
                    Transform::UnitVector point3(m_unit);
                    Transform::UnitVector s1(m_unit);
                    Transform::UnitVector s2(m_unit);
                    Transform::UnitVector ip(m_unit);
                    double s, t, distance;
                    for (Transform::UnitVector& point0 : sol1)
                    {
                        for (int i = 0; i < sol2.size(); i++)
                        {
                            point1 = point0 + tOffset;
                            point2 = sol2[i];
                            point3 = sol2[(i == sol2.size() - 1) ? 0 : i + 1];

                            s1 = point1 - point0;
                            s2 = point3 - point2;

                            s = (-s1.y * (point0.x - point2.x) + s1.x * (point0.y - point2.y)) / (-s2.x * s1.y + s1.x * s2.y);
                            t = (s2.x * (point0.y - point2.y) - s2.y * (point0.x - point2.x)) / (-s2.x * s1.y + s1.x * s2.y);

                            //std::cout << "S/T : " << s << ", " << t << std::endl;

                            if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
                            {
                                inFront = true;
                                ip = point0 + (s1 * Transform::UnitVector(t, t, s1.unit));

                                distance = std::sqrt(std::pow((point0.x - ip.x), 2) + std::pow((point0.y - ip.y), 2));
                                if (distance < minDistance || minDistance == -1)
                                {
                                    minDistance = distance;
                                    minDeplacement.set((t * s1.x), (t * s1.y));
                                }
                            }
                        }
                    }
                    std::cout << minDistance << ", " << minDeplacement << ", " << inFront << std::endl;
                    return std::make_tuple(minDistance, minDeplacement, inFront);
                };
                PolygonPath fPath = this->getAllPoints();
                PolygonPath sPath = collider.getAllPoints();

                auto tdm1 = calcMinDistanceDep(fPath, sPath, tOffset);
                std::cout << "TDM1 : " << std::get<1>(tdm1) << std::endl;
                auto tdm2 = calcMinDistanceDep(sPath, fPath, tOffset * Transform::UnitVector(-1.0, -1.0, tOffset.unit));
                std::cout << "TDM2 : " << std::get<1>(tdm2) << std::endl;
                std::get<1>(tdm2).x = -std::get<1>(tdm2).x;
                std::get<1>(tdm2).y = -std::get<1>(tdm2).y;
                if (std::get<2>(tdm1) || std::get<2>(tdm2))
                    inFront = true;


                std::cout << "NONZERO : " << (std::get<0>(tdm1) > 0) << ", " << (std::get<0>(tdm2) > 0) << std::endl;
                std::cout << "tdm1 less or equal : " << (std::get<0>(tdm1) <= std::get<0>(tdm2)) << std::endl;

                if (!inFront)
                    minDep = tOffset;
                else if (std::get<0>(tdm1) == 0 || std::get<0>(tdm2) == 0)
                {
                    std::cout << "Accept Zero Binary Branch" << std::endl;
                    return Transform::UnitVector(0, 0, m_unit);
                }
                else if (std::get<0>(tdm1) > 0 && (std::get<0>(tdm1) <= std::get<0>(tdm2) || std::get<0>(tdm2) == -1))
                {
                    std::cout << "Accept first choice" << std::endl;
                    minDep = std::get<1>(tdm1);
                }
                else if (std::get<0>(tdm2) > 0)
                {
                    std::cout << "Accept second choice" << std::endl;
                    minDep = std::get<1>(tdm2);
                }
                else
                {
                    std::cout << "Accept none" << std::endl;
                    return Transform::UnitVector(0, 0, m_unit);
                }

                std::cout << "MIN DEP IS : " << minDep << std::endl;
                return minDep;
            }
            std::cout << "Ew Shit" << std::endl;
            return Transform::UnitVector(0, 0, m_unit);
        }

        bool PolygonalCollider::doesCollide(const PolygonalCollider& collider, const Transform::UnitVector& offset) const
        {
            PolygonPath pSet1 = this->getAllPoints();
            PolygonPath pSet2 = collider.getAllPoints();
            for (Transform::UnitVector& applyOffset : pSet1)
                applyOffset += offset;
            auto pointInPolygon = [](const PolygonPath& poly, Transform::UnitVector& pTest) -> bool
            {
                int i, j, c = 0;
                unsigned int nPt = poly.size();
                for (i = 0 , j = nPt - 1; i < nPt; j = i++)
                {
                    if (((poly[i].y > pTest.y) != (poly[j].y > pTest.y)) &&
                        (pTest.x < (poly[j].x - poly[i].x) * (pTest.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x))
                        c = !c;
                }
                return c;
            };
            for (Transform::UnitVector& pTest : pSet1)
            {
                if (pointInPolygon(pSet2, pTest))
                    return true;
            }
            for (Transform::UnitVector& pTest : pSet2)
            {
                if (pointInPolygon(pSet1, pTest))
                    return true;
            }
            return false;
        }

        void mergePolygons(std::vector<PolygonalCollider*> colliders)
        {
            ClipperLib::Paths subj(colliders.size()), solution;

            unsigned int index = 0;
            for (PolygonalCollider* collider : colliders)
            {
                for (Transform::UnitVector& pt : collider->getAllPoints())
                {
                    Transform::UnitVector pxPt = pt.to<Transform::Units::WorldPixels>();
                    subj[index] << ClipperLib::IntPoint(pxPt.x, pxPt.y);
                }
                index++;
            }

            ClipperLib::Clipper c;
            for (unsigned int i = 0; i < colliders.size(); i++)
            {
                c.AddPath(subj[0], ClipperLib::ptSubject, true);
            }
            
            c.Execute(ClipperLib::ctUnion, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

            for (PolygonalCollider* collider : colliders)
            {
                Script::hookCore.getPointer("Scene")->as<Scene::Scene*>()->removeColliderById(collider->getId());
            }
            
            for (ClipperLib::Path& sol : solution)
            {
                PolygonalCollider* newCol = Script::hookCore.getPointer("Scene")->as<Scene::Scene*>()->createCollider(
                    Utils::String::getRandomKey(Utils::String::Alphabet + Utils::String::Numbers, 10)
                );
                for (ClipperLib::IntPoint& pt : sol)
                {
                    newCol->addPoint(Transform::UnitVector(pt.X, pt.Y, Transform::Units::WorldPixels));
                }
            }
        }
    }
}
