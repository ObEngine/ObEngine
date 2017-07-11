#include <cmath>
#include <functional>

#include <SFML/Graphics/CircleShape.hpp>
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

        unsigned int PolygonalCollider::getPointsAmount() const
        {
            return m_allPoints.size();
        }

        Transform::UnitVector PolygonalCollider::getPointPosition(int index)
        {
            return m_allPoints[index];
        }

        Transform::UnitVector PolygonalCollider::getPointRelativePosition(int index)
        {
            return m_allPoints[index] - m_allPoints[0];
        }

        Transform::UnitVector PolygonalCollider::getMasterPointPosition() const
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
            default: ;
            }
        }

        void PolygonalCollider::addPoint(int x, int y, int pointIndex)
        {
            if (pointIndex == -1 || pointIndex == m_allPoints.size())
                m_allPoints.emplace_back(x, y);
            else if (pointIndex >= 0 && pointIndex < m_allPoints.size())
                m_allPoints.insert(m_allPoints.begin() + pointIndex, Transform::UnitVector(x, y));
            if (m_allPoints.size() >= 3)
                calculateMasterPoint();
        }

        void PolygonalCollider::deletePoint(unsigned int pointIndex)
        {
            m_allPoints.erase(m_allPoints.begin() + pointIndex);
            this->calculateMasterPoint();
        }

        double PolygonalCollider::getDistanceFromPoint(unsigned int pointIndex, int x, int y)
        {
            return std::sqrt(std::pow((x - m_allPoints[pointIndex].x), 2) + std::pow((y - m_allPoints[pointIndex].y), 2));
        }

        unsigned int PolygonalCollider::findClosestPoint(int x, int y, bool neighboor, std::vector<int> excludedNodes)
        {
            if (m_allPoints.size() > 0)
            {
                int closestNode = 0;
                double tiniestDist = -1;
                for (unsigned int i = 0; i < m_allPoints.size(); i++)
                {
                    double currentPointDist = this->getDistanceFromPoint(i, x, y);
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
                    int leftNeighborDist = std::sqrt(std::pow((x - m_allPoints[leftNeighbor].x), 2) +
                        std::pow((y - m_allPoints[leftNeighbor].y), 2));
                    int rightNeighborDist = std::sqrt(std::pow((x - m_allPoints[rightNeighbor].x), 2) +
                        std::pow((y - m_allPoints[rightNeighbor].y), 2));
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

        int PolygonalCollider::getSideContainingPoint(int x, int y)
        {
            double tolerance = 0.01;
            for (int i = 0; i < m_allPoints.size(); i++)
            {
                int nextNode = (i != m_allPoints.size() - 1) ? i + 1 : 0;
                double lineLength = this->getDistanceFromPoint(i, this->getPointPosition(nextNode).x, this->getPointPosition(nextNode).y);
                double firstLength = this->getDistanceFromPoint(i, x, y);
                double secondLength = this->getDistanceFromPoint(nextNode, x, y);
                if (Utils::Math::isBetween(lineLength, firstLength + secondLength - tolerance, firstLength + secondLength + tolerance))
                    return i;
            }
            return -1;
        }

        std::vector<Transform::UnitVector> PolygonalCollider::getAllPoints() const
        {
            return m_allPoints;
        }

        int PolygonalCollider::hasPoint(int x, int y, int tolerance)
        {
            for (unsigned int i = 0; i < m_allPoints.size(); i++)
            {
                if (Utils::Math::isBetween(x, static_cast<int>(m_allPoints[i].x) - tolerance, static_cast<int>(m_allPoints[i].x) + tolerance))
                {
                    if (Utils::Math::isBetween(y, static_cast<int>(m_allPoints[i].y) - tolerance, static_cast<int>(m_allPoints[i].y) + tolerance))
                        return i;
                }
            }
            return -1;
        }

        bool PolygonalCollider::hasMasterPoint(int x, int y, int tolerance) const
        {
            if (Utils::Math::isBetween(x, static_cast<int>(m_masterPoint.x) - tolerance, static_cast<int>(m_masterPoint.x) + tolerance))
            {
                if (Utils::Math::isBetween(y, static_cast<int>(m_masterPoint.y) - tolerance, static_cast<int>(m_masterPoint.y) + tolerance))
                    return true;
            }
            return false;
        }

        void PolygonalCollider::movePoint(int index, int x, int y)
        {
            m_allPoints[index].x += x;
            m_allPoints[index].y += y;
            calculateMasterPoint();
        }

        void PolygonalCollider::setPointPosition(int index, int x, int y)
        {
            m_allPoints[index].x = x;
            m_allPoints[index].y = y;
            calculateMasterPoint();
        }

        void PolygonalCollider::setPointRelativePosition(int index, int x, int y)
        {
            m_allPoints[index].x = x + m_allPoints[0].x;
            m_allPoints[index].y = y + m_allPoints[0].y;
            calculateMasterPoint();
        }

        void PolygonalCollider::setPointPositionFromMaster(int index, int x, int y)
        {
            m_allPoints[index].x = x + m_masterPoint.x;
            m_allPoints[index].y = y + m_masterPoint.y;
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

        double PolygonalCollider::getSideAngle(unsigned int side)
        {
            int p1 = side;
            int p2 = side + 1;
            if (p1 == m_allPoints.size() - 1)
                p2 = 0;
            Transform::UnitVector p1coords = this->getPointPosition(p1);
            Transform::UnitVector p2coords = this->getPointPosition(p2);
            int deltaX = p2coords.x - p1coords.x;
            int deltaY = p2coords.y - p1coords.y;
            return (atan2(deltaY, deltaX) * 180 / Utils::Math::pi);
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
                    Transform::UnitVector& point = m_allPoints[i];

                    if (Utils::Vector::isInList(i, m_highlightedPoints) && m_selected)
                        drawOptions["point_color_" + std::to_string(i)] = sf::Color(255, 0, 0);
                    else
                        drawOptions["point_color_" + std::to_string(i)] = sf::Color(255, 255, 255);
                    drawPoints.emplace_back(point.x + offsetX, point.y + offsetY);
                }

                if (Utils::Vector::isInList(0, m_highlightedPoints) && m_selected)
                    drawOptions["point_color_0"] = sf::Color(255, 255, 0);
                else if (m_selected)
                    drawOptions["point_color_0"] = sf::Color(0, 255, 0);

                if (drawMasterPoint)
                {
                    sf::CircleShape polyPt;
                    polyPt.setPosition(sf::Vector2f(m_masterPoint.x + offsetX - r, m_masterPoint.y + offsetY - r));
                    polyPt.setRadius(r);
                    sf::Color polyPtColor = m_selected ? sf::Color(0, 150, 255) : sf::Color(255, 150, 0);
                    polyPt.setFillColor(polyPtColor);
                    target.draw(polyPt);
                    if (drawSkel)
                    {
                        for (Transform::UnitVector& point : m_allPoints)
                        {
                            sf::Color currentLineColor = m_selected ? sf::Color(0, 200, 255) : sf::Color(255, 200, 0);
                            Graphics::Utils::drawLine(target,
                                point.x + offsetX, point.y + offsetY,
                                m_masterPoint.x + offsetX, m_masterPoint.y + offsetY,
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

        Transform::UnitVector PolygonalCollider::u_getPosition()
        {
            return Transform::UnitVector(m_allPoints[0].x, m_allPoints[0].y, Transform::Units::WorldPixels).to(m_unit);
        }

        Transform::UnitVector PolygonalCollider::u_getPointPosition(int index)
        {
            return Transform::UnitVector(m_allPoints[index].x, m_allPoints[index].y, Transform::Units::WorldPixels).to(m_unit);
        }

        Transform::UnitVector PolygonalCollider::u_getPointRelativePosition(int index)
        {
            return Transform::UnitVector(m_allPoints[index].x - m_allPoints[0].x, m_allPoints[index].y - m_allPoints[0].y, Transform::Units::WorldPixels).to(m_unit);
        }

        Transform::UnitVector PolygonalCollider::u_getMasterPointPosition() const
        {
            return Transform::UnitVector(m_masterPoint.x, m_masterPoint.y, Transform::Units::WorldPixels).to(m_unit);
        }

        void PolygonalCollider::move(int x, int y)
        {
            for (PolygonalCollider* child : m_originChildren)
                child->move(x, y);
            if (m_allPoints.size() > 0)
            {
                m_masterPoint.x += x;
                m_masterPoint.y += y;
                for (Transform::UnitVector& point : m_allPoints)
                {
                    point.x += x;
                    point.y += y;
                }
            }
        }

        void PolygonalCollider::setPosition(int x, int y)
        {
            if (m_allPoints.size() > 0)
            {
                double addX = x - m_allPoints[0].x;
                double addY = y - m_allPoints[0].y;
                for (PolygonalCollider* child : m_originChildren)
                    child->move(addX, addY);
                m_masterPoint.x += addX;
                m_masterPoint.y += addY;
                m_allPoints[0].x = x;
                m_allPoints[0].y = y;
                for (int i = 1; i < m_allPoints.size(); i++)
                {
                    m_allPoints[i].x += addX;
                    m_allPoints[i].y += addY;
                }
            }
        }

        void PolygonalCollider::setPositionFromMaster(int x, int y)
        {
            if (m_allPoints.size() > 0)
            {
                double addX = x - m_masterPoint.x;
                double addY = y - m_masterPoint.y;
                for (PolygonalCollider* child : m_originChildren)
                    child->move(addX, addY);
                m_masterPoint.x = x;
                m_masterPoint.y = y;
                for (Transform::UnitVector& point : m_allPoints)
                {
                    point.x += addX;
                    point.y += addY;
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
            return m_parentID;
        }

        void PolygonalCollider::setParentId(const std::string& parent)
        {
            m_parentID = parent;
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


        std::pair<double, double> PolygonalCollider::getMaximumDistanceBeforeCollision(PolygonalCollider* collider, int offX, int offY) const
        {
            bool inFront = false;
            std::pair<double, double> minDep;
            auto calcMinDistanceDep = [](PolygonPath& sol1, PolygonPath& sol2, double offX, double offY) -> std::tuple<double, std::pair<double, double>, bool> {
                double minDistance = -1;
                bool inFront = false;
                std::pair<double, double> minDeplacement;
                Transform::UnitVector point1, point2, point3;
                int i_x, i_y, s1_x, s1_y, s2_x, s2_y;
                double s, t, distance;
                for (Transform::UnitVector& point0 : sol1)
                {
                    for (int i = 0; i < sol2.size(); i++)
                    {
                        point1.x = point0.x + offX;
                        point1.y = point0.y + offY;
                        point2 = sol2[i];
                        point3 = sol2[(i == sol2.size() - 1) ? 0 : i + 1];

                        s1_x = point1.x - point0.x;
                        s1_y = point1.y - point0.y;
                        s2_x = point3.x - point2.x;
                        s2_y = point3.y - point2.y;

                        s = double((-s1_y * (point0.x - point2.x) + s1_x * (point0.y - point2.y))) / double((-s2_x * s1_y + s1_x * s2_y));
                        t = double((s2_x * (point0.y - point2.y) - s2_y * (point0.x - point2.x))) / double((-s2_x * s1_y + s1_x * s2_y));

                        if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
                        {
                            inFront = true;
                            i_x = point0.x + (t * s1_x);
                            i_y = point0.y + (t * s1_y);

                            distance = std::sqrt(std::pow((point0.x - i_x), 2) + std::pow((point0.y - i_y), 2));
                            if (distance < minDistance || minDistance == -1)
                            {
                                minDistance = distance;
                                minDeplacement = std::make_pair<double, double>((t * s1_x), (t * s1_y));
                            }

                        }
                    }
                }
                return std::make_tuple(minDistance, minDeplacement, inFront);
            };
            PolygonPath fPath = this->getAllPoints();
            PolygonPath sPath = collider->getAllPoints();

            auto tdm1 = calcMinDistanceDep(fPath, sPath, offX, offY);
            auto tdm2 = calcMinDistanceDep(sPath, fPath, -offX, -offY);
            std::get<1>(tdm2).first = -std::get<1>(tdm2).first;
            std::get<1>(tdm2).second = -std::get<1>(tdm2).second;
            if (std::get<2>(tdm1))
                inFront = std::get<2>(tdm1);
            if (std::get<2>(tdm2))
                inFront = std::get<2>(tdm2);

            auto minTdm = (std::get<0>(tdm1) > std::get<0>(tdm2) && std::get<0>(tdm2) > 0 && std::get<2>(tdm2)) ? tdm2 : tdm1;
            if (!inFront)
            {
                minDep = std::make_pair<double, double>(double(offX), double(offY));
            }
            else
            {
                minDep = std::get<1>(minTdm);
            }

            return minDep;
        }

        bool PolygonalCollider::doesCollide(PolygonalCollider* collider, double offX, double offY) const
        {
            std::vector<Transform::UnitVector> fPath = this->getAllPoints();
            std::vector<Transform::UnitVector> sPath = collider->getAllPoints();

            Transform::UnitVector point1, point2, point3;
            double s1_x, s1_y, s2_x, s2_y;
            double s, t;
            bool collided = false;
            for (Transform::UnitVector point0 : fPath)
            {
                for (int i = 0; i < sPath.size(); i++)
                {
                    point1.x = point0.x + offX;
                    point1.y = point0.y + offY;
                    point2 = sPath[i];
                    point3 = sPath[(i == sPath.size() - 1) ? 0 : i + 1];

                    s1_x = point1.x - point0.x;
                    s1_y = point1.y - point0.y;
                    s2_x = point3.x - point2.x;
                    s2_y = point3.y - point2.y;

                    s = double((-s1_y * (point0.x - point2.x) + s1_x * (point0.y - point2.y))) / double((-s2_x * s1_y + s1_x * s2_y));
                    t = double((s2_x * (point0.y - point2.y) - s2_y * (point0.x - point2.x))) / double((-s2_x * s1_y + s1_x * s2_y));

                    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
                    {
                        collided = true;
                        break;
                    }
                }
            }
            return collided;
        }
    }
}
