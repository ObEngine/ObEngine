#include <cmath>

#include <SFML/Graphics/CircleShape.hpp>
#include <vili/ErrorHandler.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Scene/Scene.hpp>
#include <System/Window.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Collision
{
    bool pointsCompare(const Transform::UnitVector& first, const Transform::UnitVector& second)
    {
        if (first.x < second.x)
            return true;
        if (first.x == second.x)
            return first.y > second.y;
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
            while (lowerHull.size() >= 2
                && cross(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1], point)
                    <= 0)
                lowerHull.pop_back();
            lowerHull.push_back(point);
        }
        reverse(points.begin(), points.end());
        std::vector<Transform::UnitVector> upperHull;
        for (Transform::UnitVector& point : points)
        {
            while (upperHull.size() >= 2
                && cross(upperHull[upperHull.size() - 2], upperHull[upperHull.size() - 1], point)
                    <= 0)
                upperHull.pop_back();
            upperHull.push_back(point);
        }
        std::vector<Transform::UnitVector> fullHull;
        fullHull.reserve(lowerHull.size() + upperHull.size() - 2);
        fullHull.insert(fullHull.end(), lowerHull.begin(), lowerHull.end() - 1);
        fullHull.insert(fullHull.end(), upperHull.begin(), upperHull.end() - 1);
        return fullHull;
    }

    double cross(const Transform::UnitVector& O, const Transform::UnitVector& A,
        const Transform::UnitVector& B)
    {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    std::map<std::string, sf::Color> PolygonalCollider::TagsColor;
    PolygonalCollider::PolygonalCollider(const std::string& id)
        : Selectable(false)
        , Component(id)
    {
    }

    PolygonalCollider::~PolygonalCollider()
    {
        this->clearOriginChildren();
        this->removeOrigin();
    }

    std::string_view PolygonalCollider::type() const
    {
        return ComponentType;
    }

    void PolygonalCollider::resetUnit(Transform::Units unit)
    {
    }

    std::vector<std::string> PolygonalCollider::retrieveTagVector(ColliderTagType tagType) const
    {
        switch (tagType)
        {
        case ColliderTagType::Tag:
            return m_tags;
        case ColliderTagType::Accepted:
            return m_acceptedTags;
        case ColliderTagType::Rejected:
            return m_rejectedTags;
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Collision.PolygonalCollider.WrongColliderTagType");
    }

    std::vector<std::string>& PolygonalCollider::retrieveTagVector(ColliderTagType tagType)
    {
        switch (tagType)
        {
        case ColliderTagType::Tag:
            return m_tags;
        case ColliderTagType::Accepted:
            return m_acceptedTags;
        case ColliderTagType::Rejected:
            return m_rejectedTags;
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Collision.PolygonalCollider.WrongColliderTagType");
    }

    Transform::UnitVector PolygonalCollider::getMaximumDistanceBeforeCollision(
        const Transform::UnitVector& offset) const
    {
        std::vector<Transform::UnitVector> limitedMaxDists;
        for (auto& collider : Pool)
        {
            if (checkTags(*collider))
            {
                const Transform::UnitVector maxDist
                    = this->getMaximumDistanceBeforeCollision(*collider, offset);
                // Debug::Log->warn("Maximum distance before collision from {}
                // with {} is ({}, {})", this->getId(), collider->getId(),
                // maxDist.x, maxDist.y);
                if (maxDist != offset && collider != this)
                {
                    limitedMaxDists.push_back(maxDist);
                }
            }
        }

        const Transform::UnitVector destPos
            = (this->getCentroid() + offset).to<Transform::Units::ScenePixels>();
        if (!limitedMaxDists.empty())
        {
            std::pair<double, Transform::UnitVector> minDist(-1, Transform::UnitVector());
            for (Transform::UnitVector& distCoord : limitedMaxDists)
            {
                double dist = std::sqrt(
                    std::pow(distCoord.x - destPos.x, 2) + std::pow(distCoord.y - destPos.y, 2));
                if (minDist.first == -1 || minDist.first > dist)
                {
                    minDist = std::pair<double, Transform::UnitVector>(dist, distCoord);
                }
            }
            return minDist.second;
        }
        return offset;
    }

    void PolygonalCollider::draw(
        Scene::Camera& camera, bool drawLines, bool drawPoints, bool drawMasterPoint, bool drawSkel)
    {
        if (m_points.size() >= 3)
        {
            const Transform::UnitVector offset
                = camera.getPosition().to<Transform::Units::ScenePixels>();
            const Transform::UnitVector pMaster
                = this->getCentroid().to<Transform::Units::ScenePixels>();

            /*bool hasDrawablePoint = false; (Old Optimisation Trick, doesn't
            work) Transform::UnitVector csize =
            camera.getSize().to<Transform::Units::ScenePixels>(); if
            (drawMasterPoint || drawSkel)
            {
                if (pMaster.x >= offset.x && pMaster.y >= offset.y && pMaster.x
            <= offset.x + csize.x && pMaster.y <= offset.y + csize.y)
                {
                    hasDrawablePoint = true;
                }
            }
            if (!hasDrawablePoint)
            {
                for (int i = 0; i < m_allPoints.size(); i++)
                {
                    Transform::UnitVector point =
            m_allPoints[i].to<Transform::Units::ScenePixels>(); if (point.x >=
            offset.x && point.y >= offset.y && point.x <= offset.x + csize.x &&
            point.y <= offset.y + csize.y)
                    {
                        hasDrawablePoint = true;
                        break;
                    }
                }
            }
            if (!hasDrawablePoint)
            {
                return;
            }*/

            int r = 6;
            Graphics::Utils::DrawPolygonOptions drawOptions
                = { { "lines", drawLines }, { "points", drawPoints }, { "radius", r },
                      { "point_color", sf::Color::White }, { "line_color", getTagColor() } };

            std::vector<sf::Vector2i> lDrawPoints;

            for (int i = 0; i < m_points.size(); i++)
            {
                const Transform::UnitVector point
                    = this->get(i).to<Transform::Units::ScenePixels>();

                if (Utils::Vector::contains(i, m_highlightedPoints) && m_selected)
                    drawOptions["point_color_" + std::to_string(i)] = sf::Color(255, 0, 0);
                if (Utils::Vector::contains(
                        (i != m_points.size() - 1) ? i + 1 : 0, m_highlightedLines)
                    && m_selected)
                    drawOptions["line_color_" + std::to_string(i)] = sf::Color(0, 255, 0);

                lDrawPoints.emplace_back(point.x - offset.x, point.y - offset.y);
            }

            if (Utils::Vector::contains(0, m_highlightedPoints) && m_selected)
                drawOptions["point_color_0"] = sf::Color(255, 255, 0);
            else if (m_selected)
                drawOptions["point_color_0"] = sf::Color(0, 255, 0);

            if (drawMasterPoint)
            {
                sf::CircleShape polyPt;
                polyPt.setPosition(
                    sf::Vector2f(pMaster.x - offset.x - r, pMaster.y - offset.y - r));
                polyPt.setRadius(r);
                const sf::Color polyPtColor
                    = m_selected ? sf::Color(0, 150, 255) : sf::Color(255, 150, 0);
                polyPt.setFillColor(polyPtColor);
                System::MainWindow.draw(polyPt);
                if (drawSkel)
                {
                    for (int i = 0; i < m_points.size(); i++)
                    {
                        const Transform::UnitVector point
                            = this->get(i).to<Transform::Units::ScenePixels>();
                        const sf::Color currentLineColor
                            = m_selected ? sf::Color(0, 200, 255) : sf::Color(255, 200, 0);
                        Graphics::Utils::drawLine(point.x - offset.x, point.y - offset.y,
                            pMaster.x - offset.x, pMaster.y - offset.y, 2, currentLineColor);
                    }
                }
            }
            Graphics::Utils::drawPolygon(lDrawPoints, drawOptions);
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
        if (points)
            m_highlightedPoints.clear();
        if (lines)
            m_highlightedLines.clear();
    }

    std::string PolygonalCollider::getParentId() const
    {
        return m_parentId;
    }

    void PolygonalCollider::setParentId(const std::string& parent)
    {
        m_parentId = parent;
    }

    /*PolygonalCollider PolygonalCollider::joinPolygonalColliders(std::string
    joinID, PolygonalCollider* other) const
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
        auto findFromAddress = [polyA, polyB](Transform::UnitVector* addr) ->
    int
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
                if (Utils::Vector::contains(a, polys[poly]) &&
    Utils::Vector::contains(b, polys[poly]))
                {
                    int iA = findFromAddress(a);
                    int iB = findFromAddress(b);
                    int counter = 1;
                    while ((iA + counter) % polys[poly].size() != iB)
                    {
                        int index = (iA + counter) % polys[poly].size();
                        result.addPoint(polys[poly][index]->X,
    polys[poly][index]->Y); counter++;
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
        if (Utils::Vector::contains(child, m_originChildren))
        {
            for (int i = 0; i < m_originChildren.size(); i++)
            {
                if (child == m_originChildren[i])
                {
                    if (trigger)
                        m_originChildren[i]->removeOrigin();
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
        if (!Utils::Vector::contains(tag, this->retrieveTagVector(tagType)))
            this->retrieveTagVector(tagType).push_back(tag);
        else
            Debug::Log->warn("<PolygonalCollider> Tag '{0}' is already in "
                             "PolygonalCollider '{1}'",
                tag, m_id);
    }

    void PolygonalCollider::clearTags(ColliderTagType tagType)
    {
        this->retrieveTagVector(tagType).clear();
    }

    bool PolygonalCollider::doesCollide(const Transform::UnitVector& offset) const
    {
        bool collided = false;
        for (auto& collider : Pool)
        {
            if (checkTags(*collider))
            {
                if (this->doesCollide(*collider, offset))
                {
                    return true;
                }
            }
        }

        return false;
    }

    void PolygonalCollider::removeTag(ColliderTagType tagType, const std::string& tag)
    {
        Utils::Vector::eraseAll(this->retrieveTagVector(tagType), tag);
    }

    bool PolygonalCollider::doesHaveTag(ColliderTagType tagType, const std::string& tag)
    {
        return Utils::Vector::contains(tag, this->retrieveTagVector(tagType));
    }

    bool PolygonalCollider::doesHaveAnyTag(
        ColliderTagType tagType, const std::vector<std::string>& tags) const
    {
        if (m_tags.size() == 0)
            return false;
        for (const std::string& tag : tags)
        {
            if (Utils::Vector::contains(tag, this->retrieveTagVector(tagType)))
                return true;
        }
        return false;
    }

    std::vector<std::string> PolygonalCollider::getAllTags(ColliderTagType tagType) const
    {
        return this->retrieveTagVector(tagType);
    }

    Transform::UnitVector PolygonalCollider::getMaximumDistanceBeforeCollision(
        PolygonalCollider& collider, const Transform::UnitVector& offset) const
    {
        const Transform::Units pxUnit = Transform::Units::ScenePixels;
        const Transform::UnitVector tOffset = offset.to(pxUnit);
        bool inFront = false;
        Transform::UnitVector minDep;
        const auto calcMinDistanceDep
            = [this](const Transform::PolygonPath& sol1, const Transform::PolygonPath& sol2,
                  const Transform::UnitVector& tOffset)
            -> std::tuple<double, Transform::UnitVector, bool> {
            double minDistance = -1;
            bool inFront = false;

            Transform::Units pxUnit = Transform::Units::ScenePixels;
            Transform::UnitVector minDeplacement(pxUnit);
            Transform::UnitVector point1(pxUnit);
            Transform::UnitVector point2(pxUnit);
            Transform::UnitVector point3(pxUnit);
            Transform::UnitVector s1(pxUnit);
            Transform::UnitVector s2(pxUnit);
            Transform::UnitVector ip(pxUnit);
            double s, t, distance;
            for (auto& currentPoint : sol1)
            {
                const Transform::UnitVector point0 = currentPoint->to(pxUnit);
                for (int i = 0; i < sol2.size(); i++)
                {
                    point1 = point0 + tOffset;
                    point2 = sol2[i]->to(pxUnit);
                    point3 = sol2[(i == sol2.size() - 1) ? 0 : i + 1]->to(pxUnit);

                    s1 = point1 - point0;
                    s2 = point3 - point2;

                    s = (-s1.y * (point0.x - point2.x) + s1.x * (point0.y - point2.y))
                        / (-s2.x * s1.y + s1.x * s2.y);
                    t = (s2.x * (point0.y - point2.y) - s2.y * (point0.x - point2.x))
                        / (-s2.x * s1.y + s1.x * s2.y);

                    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
                    {
                        inFront = true;
                        ip = point0 + (s1 * Transform::UnitVector(t, t, s1.unit));

                        distance = std::sqrt(
                            std::pow((point0.x - ip.x), 2) + std::pow((point0.y - ip.y), 2));
                        if (distance < minDistance || minDistance == -1)
                        {
                            minDistance = distance;
                            double xComp = t * s1.x;
                            double yComp = t * s1.y;
                            minDeplacement.set((xComp > 0) ? std::floor(xComp) : std::ceil(xComp),
                                (yComp > 0) ? std::floor(yComp) : std::ceil(yComp));
                        }
                    }
                }
            }
            return std::make_tuple(minDistance, minDeplacement, inFront);
        };
        const Transform::PolygonPath& fPath = m_points;
        const Transform::PolygonPath& sPath = collider.getAllPoints();

        auto tdm1 = calcMinDistanceDep(fPath, sPath, tOffset);
        auto tdm2 = calcMinDistanceDep(
            sPath, fPath, tOffset * Transform::UnitVector(-1.0, -1.0, tOffset.unit));
        std::get<1>(tdm2).x = -std::get<1>(tdm2).x;
        std::get<1>(tdm2).y = -std::get<1>(tdm2).y;
        if (std::get<2>(tdm1) || std::get<2>(tdm2))
            inFront = true;

        if (!inFront)
            minDep = tOffset;
        else if (std::get<0>(tdm1) == 0 || std::get<0>(tdm2) == 0)
            return Transform::UnitVector(0, 0, tOffset.unit);
        else if (std::get<0>(tdm1) > 0
            && (std::get<0>(tdm1) <= std::get<0>(tdm2) || std::get<0>(tdm2) == -1))
            minDep = std::get<1>(tdm1);
        else if (std::get<0>(tdm2) > 0)
            minDep = std::get<1>(tdm2);
        else
            return Transform::UnitVector(0, 0, tOffset.unit);

        return minDep;
    }

    bool PolygonalCollider::doesCollide(
        PolygonalCollider& collider, const Transform::UnitVector& offset) const
    {
        std::vector<Transform::UnitVector> pSet1;
        pSet1.reserve(m_points.size());
        std::vector<Transform::UnitVector> pSet2;
        pSet2.reserve(m_points.size());

        for (const auto& point : m_points)
            pSet1.push_back(*point);
        for (const auto& point : collider.getAllPoints())
            pSet2.push_back(*point);
        for (auto& applyOffset : pSet1)
            applyOffset += offset;
        const auto pointInPolygon = [](const std::vector<Transform::UnitVector>& poly,
                                        Transform::UnitVector& pTest) -> bool {
            int i, j, c = 0;
            unsigned int nPt = poly.size();
            for (i = 0, j = nPt - 1; i < nPt; j = i++)
            {
                if (((poly[i].y > pTest.y) != (poly[j].y > pTest.y))
                    && (pTest.x < (poly[j].x - poly[i].x) * (pTest.y - poly[i].y)
                                   / (poly[j].y - poly[i].y)
                               + poly[i].x))
                    c = !c;
            }
            return c;
        };
        for (Transform::UnitVector& pTest : pSet1)
        {
            if (pointInPolygon(pSet2, pTest))
                return true;
        }
        for (auto& pTest : pSet2)
        {
            if (pointInPolygon(pSet1, pTest))
                return true;
        }
        return false;
    }

    void PolygonalCollider::dump(vili::ComplexNode& target) const
    {
        vili::ComplexNode& ser = target.createComplexNode(m_id);
        ser.createComplexNode("unit").createDataNode("unit", Transform::unitsToString(m_unit));
        vili::ArrayNode& points = ser.createArrayNode("points");
        for (auto& point : m_points)
        {
            const Transform::UnitVector pVec = point->to(m_unit);
            points.push(pVec.x);
            points.push(pVec.y);
        }
    }

    void PolygonalCollider::load(vili::ComplexNode& data)
    {
        const std::string pointsUnit = data.at<vili::DataNode>("unit", "unit").get<std::string>();
        bool completePoint = true;
        double pointBuffer = 0;
        const Transform::Units pBaseUnit = Transform::stringToUnits(pointsUnit);
        for (vili::DataNode* colliderPoint : data.getArrayNode("points"))
        {
            if ((completePoint = !completePoint))
            {
                const Transform::UnitVector pVector2
                    = Transform::UnitVector(pointBuffer, colliderPoint->get<double>(), pBaseUnit);
                this->addPoint(pVector2);
            }
            else
                pointBuffer = colliderPoint->get<double>();
        }
        this->setWorkingUnit(pBaseUnit);
        if (data.contains(vili::NodeType::DataNode, "tag"))
            this->addTag(
                Collision::ColliderTagType::Tag, data.at<vili::DataNode>("tag").get<std::string>());
        else if (data.contains(vili::NodeType::ArrayNode, "tags"))
        {
            for (vili::DataNode* cTag : data.at<vili::ArrayNode>("tags"))
                this->addTag(Collision::ColliderTagType::Tag, cTag->get<std::string>());
        }
        if (data.contains(vili::NodeType::DataNode, "accept"))
            this->addTag(Collision::ColliderTagType::Accepted,
                data.at<vili::DataNode>("accept").get<std::string>());
        else if (data.contains(vili::NodeType::ArrayNode, "accept"))
        {
            for (vili::DataNode* aTag : data.at<vili::ArrayNode>("accept"))
                this->addTag(Collision::ColliderTagType::Accepted, aTag->get<std::string>());
        }
        if (data.contains(vili::NodeType::DataNode, "reject"))
            this->addTag(Collision::ColliderTagType::Rejected,
                data.at<vili::DataNode>("reject").get<std::string>());
        else if (data.contains(vili::NodeType::ArrayNode, "reject"))
        {
            for (vili::DataNode* rTag : data.at<vili::ArrayNode>("reject"))
                this->addTag(Collision::ColliderTagType::Rejected, rTag->get<std::string>());
        }
    }

    bool PolygonalCollider::checkTags(const PolygonalCollider& collider) const
    {
        if (this->doesHaveAnyTag(
                ColliderTagType::Rejected, collider.getAllTags(ColliderTagType::Tag)))
            return false;
        if (!m_acceptedTags.empty()
            && !this->doesHaveAnyTag(
                   ColliderTagType::Accepted, collider.getAllTags(ColliderTagType::Tag)))
            return false;
        return true;
    }

    sf::Color PolygonalCollider::getTagColor()
    {
        for (const std::string& tag : m_tags)
        {
            for (auto& tagColor : TagsColor)
            {
                if (tag == tagColor.first)
                    return tagColor.second;
            }
        }
        return sf::Color::White;
    }

    void PolygonalCollider::SetTagColor(const std::string& tag, sf::Color color)
    {
        TagsColor[tag] = color;
    }
} // namespace obe::Collision