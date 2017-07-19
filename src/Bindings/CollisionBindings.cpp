#include <Bindings/CollisionBindings.hpp>
#include <Collision/PolygonalCollider.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace CollisionBindings
        {
            void LoadPolygonalCollider(kaguya::State& lua)
            {
                lua["Core"]["Collision"]["PolygonalCollider"].setClass(
                    kaguya::UserdataMetatable<
                    Collision::PolygonalCollider,
                    kaguya::MultipleBase<
                    Transform::UnitBasedObject,
                    Types::Selectable,
                    Types::Identifiable>
                    >
                    ()
                    .addFunction("addOriginChild", &Collision::PolygonalCollider::addOriginChild)
                    .addFunction("addPoint", &Collision::PolygonalCollider::addPoint)
                    .addFunction("addTag", &Collision::PolygonalCollider::addTag)
                    .addFunction("clearHighlights", &Collision::PolygonalCollider::clearHighlights)
                    .addFunction("clearOriginChildren", &Collision::PolygonalCollider::clearOriginChildren)
                    .addFunction("clearTags", &Collision::PolygonalCollider::clearTags)
                    .addFunction("deletePoint", &Collision::PolygonalCollider::deletePoint)
                    .addFunction("doesCollide", &Collision::PolygonalCollider::doesCollide)
                    .addFunction("doesHaveAnyTag", &Collision::PolygonalCollider::doesHaveAnyTag)
                    .addFunction("doesHaveTag", &Collision::PolygonalCollider::doesHaveTag)
                    .addFunction("draw", &Collision::PolygonalCollider::draw)
                    .addFunction("findClosestLine", &Collision::PolygonalCollider::findClosestLine)
                    .addFunction("findClosestPoint", &Collision::PolygonalCollider::findClosestPoint)
                    .addFunction("getAllPoints", &Collision::PolygonalCollider::getAllPoints)
                    .addFunction("getAllTags", &Collision::PolygonalCollider::getAllTags)
                    .addFunction("getDistanceFromPoint", &Collision::PolygonalCollider::getDistanceFromPoint)
                    .addFunction("getMasterPointPosition", &Collision::PolygonalCollider::getMasterPointPosition)
                    .addFunction("getMaximumDistanceBeforeCollision", &Collision::PolygonalCollider::getMaximumDistanceBeforeCollision)
                    .addFunction("getOrigin", &Collision::PolygonalCollider::getOrigin)
                    .addFunction("getParentId", &Collision::PolygonalCollider::getParentId)
                    .addFunction("getPointPosition", &Collision::PolygonalCollider::getPointPosition)
                    .addFunction("getPointRelativePosition", &Collision::PolygonalCollider::getPointRelativePosition)
                    .addFunction("getPointsAmount", &Collision::PolygonalCollider::getPointsAmount)
                    .addFunction("getPosition", &Collision::PolygonalCollider::getPosition)
                    .addFunction("getSideAngle", &Collision::PolygonalCollider::getSideAngle)
                    .addFunction("getSideContainingPoint", &Collision::PolygonalCollider::getSideContainingPoint)
                    .addFunction("getSideLength", &Collision::PolygonalCollider::getSideLength)
                    .addFunction("hasMasterPoint", &Collision::PolygonalCollider::hasMasterPoint)
                    .addFunction("hasPoint", &Collision::PolygonalCollider::hasPoint)
                    .addFunction("highlightLine", &Collision::PolygonalCollider::highlightLine)
                    .addFunction("highlightPoint", &Collision::PolygonalCollider::highlightPoint)
                    .addFunction("move", &Collision::PolygonalCollider::move)
                    .addFunction("movePoint", &Collision::PolygonalCollider::movePoint)
                    .addFunction("removeOrigin", &Collision::PolygonalCollider::removeOrigin)
                    .addFunction("removeOriginChild", &Collision::PolygonalCollider::removeOriginChild)
                    .addFunction("removeTag", &Collision::PolygonalCollider::removeTag)
                    .addFunction("setOrigin", &Collision::PolygonalCollider::setOrigin)
                    .addFunction("setParentId", &Collision::PolygonalCollider::setParentId)
                    .addFunction("setPointPosition", &Collision::PolygonalCollider::setPointPosition)
                    .addFunction("setPointPositionFromMaster", &Collision::PolygonalCollider::setPointPositionFromMaster)
                    .addFunction("setPointRelativePosition", &Collision::PolygonalCollider::setPointRelativePosition)
                    .addFunction("setPosition", &Collision::PolygonalCollider::setPosition)
                    .addFunction("setPositionFromMaster", &Collision::PolygonalCollider::setPositionFromMaster)
                );
            }
        }
    }
}
