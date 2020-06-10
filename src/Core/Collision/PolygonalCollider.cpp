#include <cmath>

#include <Collision/PolygonalCollider.hpp>
#include <Debug/Logger.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Scene/Scene.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Collision
{
    bool pointsCompare(
        const Transform::UnitVector& first, const Transform::UnitVector& second)
    {
        if (first.x < second.x)
            return true;
        if (first.x == second.x)
            return first.y > second.y;
        return false;
    }

    double pointsDistance(
        const Transform::UnitVector& first, const Transform::UnitVector& second)
    {
        return std::sqrt(
            std::pow(second.x - first.x, 2) + std::pow(second.y - first.y, 2));
    }

    double cross(const Transform::UnitVector& O, const Transform::UnitVector& A,
        const Transform::UnitVector& B)
    {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    std::vector<Transform::UnitVector> convexHull(
        std::vector<Transform::UnitVector> points)
    {
        sort(points.begin(), points.end(), pointsCompare);
        if (points.size() <= 1)
            return points;
        std::vector<Transform::UnitVector> lowerHull;
        for (Transform::UnitVector& point : points)
        {
            while (lowerHull.size() >= 2
                && cross(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1],
                       point)
                    <= 0)
                lowerHull.pop_back();
            lowerHull.push_back(point);
        }
        reverse(points.begin(), points.end());
        std::vector<Transform::UnitVector> upperHull;
        for (Transform::UnitVector& point : points)
        {
            while (upperHull.size() >= 2
                && cross(upperHull[upperHull.size() - 2], upperHull[upperHull.size() - 1],
                       point)
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

    PolygonalCollider::PolygonalCollider(const std::string& id)
        : Selectable(false)
        , Component(id)
    {
    }

    std::string_view PolygonalCollider::type() const
    {
        return ComponentType;
    }

    void PolygonalCollider::resetUnit(Transform::Units unit)
    {
    }

    CollisionData PolygonalCollider::getMaximumDistanceBeforeCollision(
        const Transform::UnitVector& offset) const
    {
        std::vector<Transform::UnitVector> limitedMaxDistances;
        CollisionData collData;
        collData.offset = offset;

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
                    limitedMaxDistances.push_back(maxDist);
                    collData.colliders.push_back(collider);
                }
            }
        }

        const Transform::UnitVector destPos
            = (this->getCentroid() + offset).to<Transform::Units::ScenePixels>();
        if (!limitedMaxDistances.empty())
        {
            std::pair<double, Transform::UnitVector> minDist(-1, Transform::UnitVector());
            for (Transform::UnitVector& distCoordinates : limitedMaxDistances)
            {
                double dist = std::sqrt(std::pow(distCoordinates.x - destPos.x, 2)
                    + std::pow(distCoordinates.y - destPos.y, 2));
                if (minDist.first == -1 || minDist.first > dist)
                {
                    minDist
                        = std::pair<double, Transform::UnitVector>(dist, distCoordinates);
                }
            }
            collData.offset = minDist.second;
        }
        return collData;
    }

    std::string PolygonalCollider::getParentId() const
    {
        return m_parentId;
    }

    void PolygonalCollider::setParentId(const std::string& parent)
    {
        m_parentId = parent;
    }

    void PolygonalCollider::addTag(ColliderTagType tagType, const std::string& tag)
    {
        if (!Utils::Vector::contains(tag, m_tags.at(tagType)))
            m_tags.at(tagType).push_back(tag);
        else
            Debug::Log->warn("<PolygonalCollider> Tag '{0}' is already in "
                             "PolygonalCollider '{1}'",
                tag, m_id);
    }

    void PolygonalCollider::clearTags(ColliderTagType tagType)
    {
        m_tags.at(tagType).clear();
    }

    CollisionData PolygonalCollider::doesCollide(const Transform::UnitVector& offset) const
    {
        CollisionData collData;
        collData.offset = offset;
        for (auto& collider : Pool)
        {
            if (collider != this && checkTags(*collider))
            {
                if (this->doesCollide(*collider, offset))
                {
                    collData.colliders.push_back(collider);
                }
            }
        }

        return collData;
    }

    void PolygonalCollider::removeTag(ColliderTagType tagType, const std::string& tag)
    {
        std::vector<std::string>& tags = m_tags.at(ColliderTagType::Tag);
        tags.erase(std::remove(tags.begin(), tags.end(), tag), tags.end());
    }

    bool PolygonalCollider::doesHaveTag(ColliderTagType tagType, const std::string& tag)
    {
        return Utils::Vector::contains(tag, m_tags.at(tagType));
    }

    bool PolygonalCollider::doesHaveAnyTag(
        ColliderTagType tagType, const std::vector<std::string>& tags) const
    {
        if (m_tags.size() == 0)
            return false;
        for (const std::string& tag : tags)
        {
            if (Utils::Vector::contains(tag, m_tags.at(tagType)))
                return true;
        }
        return false;
    }

    std::vector<std::string> PolygonalCollider::getAllTags(ColliderTagType tagType) const
    {
        return m_tags.at(tagType);
    }

    Transform::UnitVector PolygonalCollider::getMaximumDistanceBeforeCollision(
        PolygonalCollider& collider, const Transform::UnitVector& offset) const
    {
        const Transform::Units pxUnit = Transform::Units::ScenePixels;
        const Transform::UnitVector tOffset = offset.to(pxUnit);
        bool inFront = false;
        Transform::UnitVector minDep;
        const auto calcMinDistanceDep = [this](const Transform::PolygonPath& sol1,
                                            const Transform::PolygonPath& sol2,
                                            const Transform::UnitVector& tOffset)
            -> std::tuple<double, Transform::UnitVector, bool> {
            double minDistance = -1;
            bool inFront = false;

            const Transform::Units pxUnit = Transform::Units::ScenePixels;
            Transform::UnitVector minDisplacement(pxUnit);
            Transform::UnitVector point1(pxUnit);
            Transform::UnitVector point2(pxUnit);
            Transform::UnitVector point3(pxUnit);
            Transform::UnitVector s1(pxUnit);
            for (auto& currentPoint : sol1)
            {
                const Transform::UnitVector point0 = currentPoint->to(pxUnit);
                for (int i = 0; i < sol2.size(); i++)
                {
                    point1 = point0 + tOffset;
                    point2 = sol2[i]->to(pxUnit);
                    point3 = sol2[(i == sol2.size() - 1) ? 0 : i + 1]->to(pxUnit);

                    s1 = point1 - point0;
                    const Transform::UnitVector s2 = point3 - point2;

                    const double s
                        = (-s1.y * (point0.x - point2.x) + s1.x * (point0.y - point2.y))
                        / (-s2.x * s1.y + s1.x * s2.y);
                    const double t
                        = (s2.x * (point0.y - point2.y) - s2.y * (point0.x - point2.x))
                        / (-s2.x * s1.y + s1.x * s2.y);

                    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
                    {
                        inFront = true;
                        const Transform::UnitVector ip
                            = point0 + (s1 * Transform::UnitVector(t, t, s1.unit));

                        const double distance = std::sqrt(std::pow((point0.x - ip.x), 2)
                            + std::pow((point0.y - ip.y), 2));
                        if (distance < minDistance || minDistance == -1)
                        {
                            minDistance = distance;
                            const double xComp = t * s1.x;
                            const double yComp = t * s1.y;
                            minDisplacement.set(
                                (xComp > 0) ? std::floor(xComp) : std::ceil(xComp),
                                (yComp > 0) ? std::floor(yComp) : std::ceil(yComp));
                        }
                    }
                }
            }
            return std::make_tuple(minDistance, minDisplacement, inFront);
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
            const int nPt = poly.size();
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

    vili::node PolygonalCollider::dump() const
    {
        vili::node result;
        result["unit"] = Transform::unitsToString(m_unit);
        result["points"] = vili::array {};
        for (auto& point : m_points)
        {
            const Transform::UnitVector pVec = point->to(m_unit);
            result["points"].push(vili::object { { "x", pVec.x }, { "y", pVec.y } });
        }
        return result;
    }

    void PolygonalCollider::load(vili::node& data)
    {
        auto addTagHelper = [this](ColliderTagType type, vili::node& tag) {
            if (!tag.is_null())
            {
                if (tag.is<vili::string>())
                {
                    this->addTag(type, tag);
                }
                else if (tag.is<vili::array>())
                {
                    for (vili::node& item : tag)
                        this->addTag(Collision::ColliderTagType::Rejected, item);
                }
                else
                {
                    // TODO: Raise exception
                }
            }
        };
        const std::string pointsUnit = data.at("unit");
        bool completePoint = true;
        double pointBuffer = 0;
        const Transform::Units pBaseUnit = Transform::stringToUnits(pointsUnit);
        for (vili::node& colliderPoint : data["points"])
        {
            const Transform::UnitVector pVector2 = Transform::UnitVector(
                colliderPoint["x"], colliderPoint["y"], pBaseUnit);
            this->addPoint(pVector2);
        }
        this->setWorkingUnit(pBaseUnit);

        addTagHelper(ColliderTagType::Tag, data["tag"]);
        addTagHelper(ColliderTagType::Accepted, data["accept"]);
        addTagHelper(ColliderTagType::Rejected, data["reject"]);
    }

    bool PolygonalCollider::checkTags(const PolygonalCollider& collider) const
    {
        if (this->doesHaveAnyTag(
                ColliderTagType::Rejected, collider.getAllTags(ColliderTagType::Tag)))
            return false;
        if (!m_tags.at(ColliderTagType::Accepted).empty()
            && !this->doesHaveAnyTag(
                ColliderTagType::Accepted, collider.getAllTags(ColliderTagType::Tag)))
            return false;
        return true;
    }
} // namespace obe::Collision