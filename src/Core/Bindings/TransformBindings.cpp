#include <Bindings/Bindings.hpp>
#include <Bindings/TransformBindings.hpp>
#include <Transform/SceneNode.hpp>
#include <Transform/Polygon.hpp>
#include <Transform/ProtectedUnitVector.hpp>
#include <Transform/Rect.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Bindings::TransformBindings
{
    void LoadMovable(kaguya::State* lua)
    {
        Load(lua, "obe.Identifiable");
        (*lua)["obe"]["Movable"].setClass(kaguya::UserdataMetatable<Transform::Movable>()
            .addFunction("getPosition", &Transform::Movable::getPosition)
            .addFunction("getType", &Transform::Movable::getType)
            .addFunction("move", &Transform::Movable::move)
            .addFunction("setPosition", &Transform::Movable::setPosition)
        );
    }

    void LoadSceneNode(kaguya::State* lua)
    {
        Load(lua, "obe.Movable");
        (*lua)["obe"]["SceneNode"].setClass(kaguya::UserdataMetatable<Transform::SceneNode, Transform::Movable>()
            .addFunction("addChild", &Transform::SceneNode::addChild)
            .addFunction("move", &Transform::SceneNode::move)
            .addFunction("setPosition", &Transform::SceneNode::setPosition)
        );
    }

    void LoadProtectedUnitVector(kaguya::State* lua)
    {
        Load(lua, "obe.UnitVector");
        (*lua)["obe"]["ProtectedUnitVector"].setClass(kaguya::UserdataMetatable<Transform::ProtectedUnitVector, Transform::UnitVector>()
        );
    }

    KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
        Rect_getPosition_wrapper, Transform::Rect, getPosition, 0, 1, Transform::UnitVector(Transform::Rect::*)(Transform::Referencial)
    );
    KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
        Rect_movePoint_wrapper, Transform::Rect, movePoint, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
    );
    KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
        Rect_scale_wrapper, Transform::Rect, scale, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
    );
    KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
        Rect_setPointPosition_wrapper, Transform::Rect, setPointPosition, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
    );
    KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
        Rect_setPosition_wrapper, Transform::Rect, setPosition, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
    );
    KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
        Rect_setSize_wrapper, Transform::Rect, setSize, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
    );
    void LoadRect(kaguya::State* lua)
    {
        Load(lua, "obe.Movable");
        (*lua)["obe"]["Rect"].setClass(kaguya::UserdataMetatable<Transform::Rect, Transform::Movable>()
            .addFunction("getPosition", Rect_getPosition_wrapper())
            .addFunction("getScaleFactor", &Transform::Rect::getScaleFactor)
            .addFunction("getSize", &Transform::Rect::getSize)
            .addFunction("move", &Transform::Rect::move)
            .addFunction("movePoint", Rect_movePoint_wrapper())
            .addFunction("scale", Rect_scale_wrapper())
            .addFunction("setPointPosition", Rect_setPointPosition_wrapper())
            .addFunction("setPosition", Rect_setPosition_wrapper())
            .addFunction("setSize", Rect_setSize_wrapper())
            .addFunction("transformRef", &Transform::Rect::transformRef)
        );
    }

    void LoadReferencial(kaguya::State* lua)
    {
        (*lua)["obe"]["Referencial"] = kaguya::NewTable();
        (*lua)["obe"]["Referencial"]["Bottom"] = Transform::Referencial::Bottom;
        (*lua)["obe"]["Referencial"]["BottomLeft"] = Transform::Referencial::BottomLeft;
        (*lua)["obe"]["Referencial"]["BottomRight"] = Transform::Referencial::BottomRight;
        (*lua)["obe"]["Referencial"]["Center"] = Transform::Referencial::Center;
        (*lua)["obe"]["Referencial"]["Left"] = Transform::Referencial::Left;
        (*lua)["obe"]["Referencial"]["Right"] = Transform::Referencial::Right;
        (*lua)["obe"]["Referencial"]["Top"] = Transform::Referencial::Top;
        (*lua)["obe"]["Referencial"]["TopLeft"] = Transform::Referencial::TopLeft;
        (*lua)["obe"]["Referencial"]["TopRight"] = Transform::Referencial::TopRight;
    }

    void LoadUnitBasedObject(kaguya::State* lua)
    {
        (*lua)["obe"]["UnitBasedObject"].setClass(kaguya::UserdataMetatable<Transform::UnitBasedObject>()
            .addFunction("getWorkingUnit", &Transform::UnitBasedObject::getWorkingUnit)
            .addFunction("setWorkingUnit", &Transform::UnitBasedObject::setWorkingUnit)
        );
    }
    void LoadUnitVector(kaguya::State* lua)
    {
        (*lua)["obe"]["UnitVector"].setClass(kaguya::UserdataMetatable<Transform::UnitVector>()
            .setConstructors<
            Transform::UnitVector(),
            Transform::UnitVector(Transform::Units),
            Transform::UnitVector(double, double), 
            Transform::UnitVector(double, double, Transform::Units)
            >()
            .addOverloadedFunctions("add",
                static_cast<void (Transform::UnitVector::*)(const Transform::UnitVector&)>(&Transform::UnitVector::add),
                static_cast<void (Transform::UnitVector::*)(double, double)>(&Transform::UnitVector::add)
            )
            .addOverloadedFunctions("__add", 
                static_cast<Transform::UnitVector(Transform::UnitVector::*)(const Transform::UnitVector&) const>(&Transform::UnitVector::operator+),
                static_cast<Transform::UnitVector(Transform::UnitVector::*)(double) const>(&Transform::UnitVector::operator+))
            .addOverloadedFunctions("__sub", 
                static_cast<Transform::UnitVector (Transform::UnitVector::*)(const Transform::UnitVector&) const>(&Transform::UnitVector::operator-),
                static_cast<Transform::UnitVector(Transform::UnitVector::*)(double) const>(&Transform::UnitVector::operator-))
            .addOverloadedFunctions("__mul",
                static_cast<Transform::UnitVector(Transform::UnitVector::*)(const Transform::UnitVector&) const>(&Transform::UnitVector::operator*),
                static_cast<Transform::UnitVector(Transform::UnitVector::*)(double) const>(&Transform::UnitVector::operator*))
            .addOverloadedFunctions("__div",
                static_cast<Transform::UnitVector(Transform::UnitVector::*)(const Transform::UnitVector&) const>(&Transform::UnitVector::operator/),
                static_cast<Transform::UnitVector(Transform::UnitVector::*)(double) const>(&Transform::UnitVector::operator/))
            .addOverloadedFunctions("set",
                static_cast<void (Transform::UnitVector::*)(const Transform::UnitVector&)>(&Transform::UnitVector::set),
                static_cast<void (Transform::UnitVector::*)(double, double)>(&Transform::UnitVector::set)
            )
            .addFunction("__eq", &Transform::UnitVector::operator==)
            .addFunction("to", static_cast<Transform::UnitVector (Transform::UnitVector::*)(Transform::Units) const>(&Transform::UnitVector::to))
            .addProperty("x", &Transform::UnitVector::x)
            .addProperty("y", &Transform::UnitVector::y)
            .addProperty("unit", &Transform::UnitVector::unit)
        );
    }

    Transform::PolygonSegment* Polygon_getSegmentContainingPoint_subwrapper(
        Transform::Polygon& polygon, 
        const Transform::UnitVector& position, 
        double tolerance = Transform::Polygon::DefaultTolerance)
    {
        auto optret = polygon.getSegmentContainingPoint(position, tolerance);
        if (optret.has_value())
        {
            return &optret.value();
        }
        else
        {
            Transform::PolygonSegment* nullsegment = nullptr;
            return nullsegment;
        }
    }
    KAGUYA_FUNCTION_OVERLOADS(Polygon_getSegmentContainingPoint_wrapper, Polygon_getSegmentContainingPoint_subwrapper, 2, 3)
    KAGUYA_MEMBER_FUNCTION_OVERLOADS(Polygon_addPoint_wrapper, Transform::Polygon, addPoint, 1, 2);
    KAGUYA_MEMBER_FUNCTION_OVERLOADS(Polygon_findClosestPoint_wrapper, Transform::Polygon, findClosestPoint, 1, 3);
    void LoadPolygon(kaguya::State* lua)
    {
        Load(lua, "obe.Movable");
        Load(lua, "obe.UnitBasedObject");
        Load(lua, "obe.UnitVector");
        (*lua)["obe"]["PolygonPoint"].setClass(kaguya::UserdataMetatable<Transform::PolygonPoint, Transform::UnitVector>()
            .addFunction("distance", &Transform::PolygonPoint::distance)
            .addFunction("getRelativePosition", &Transform::PolygonPoint::getRelativePosition)
            .addFunction("move", &Transform::PolygonPoint::move)
            .addFunction("remove", &Transform::PolygonPoint::remove)
            .addFunction("setRelativePosition", &Transform::PolygonPoint::setRelativePosition)
        );
        (*lua)["obe"]["PolygonPoint"]["RelativePositionFrom"] = kaguya::NewTable();
        (*lua)["obe"]["PolygonPoint"]["RelativePositionFrom"]["Point0"] = Transform::PolygonPoint::RelativePositionFrom::Point0;
        (*lua)["obe"]["PolygonPoint"]["RelativePositionFrom"]["Centroid"] = Transform::PolygonPoint::RelativePositionFrom::Centroid;
        (*lua)["obe"]["PolygonPoint"]["index"] = kaguya::function([](Transform::PolygonPoint& point) {
            return point.index;
        });
        (*lua)["obe"]["PolygonSegment"].setClass(kaguya::UserdataMetatable<Transform::PolygonSegment>()
            .setConstructors<Transform::PolygonSegment(const Transform::PolygonPoint&, const Transform::PolygonPoint&)>()
            .addFunction("getAngle", &Transform::PolygonSegment::getAngle)
            .addFunction("getLength", &Transform::PolygonSegment::getLength)
        );
        (*lua)["obe"]["PolygonSegment"]["first"] = kaguya::function([](Transform::PolygonSegment& segment) {
            return &segment.first;
        });
        (*lua)["obe"]["PolygonSegment"]["second"] = kaguya::function([](Transform::PolygonSegment& segment) {
            return &segment.second;
        });
        (*lua)["obe"]["Polygon"].setClass(kaguya::UserdataMetatable<Transform::Polygon, 
        kaguya::MultipleBase<Transform::UnitBasedObject, Transform::Movable>>()
            .addFunction("addPoint", Polygon_addPoint_wrapper())
            .addFunction("findClosestSegment", &Transform::Polygon::findClosestSegment)
            .addFunction("findClosestPoint", Polygon_findClosestPoint_wrapper())
            .addFunction("getCentroid", &Transform::Polygon::getCentroid)
            .addFunction("getPointsAmount", &Transform::Polygon::getPointsAmount)
            .addFunction("getPosition", &Transform::Polygon::getPosition)
            .addFunction("getRotation", &Transform::Polygon::getRotation)
            .addFunction("getSegment", &Transform::Polygon::getSegment)
            .addFunction("isCentroidAroundPosition", &Transform::Polygon::isCentroidAroundPosition)
            .addFunction("move", &Transform::Polygon::move)
            .addFunction("rotate", &Transform::Polygon::rotate)
            .addFunction("setPosition", &Transform::Polygon::setPosition)
            .addFunction("setPositionFromCentroid", &Transform::Polygon::setPositionFromCentroid)
            .addFunction("setRotation", &Transform::Polygon::setRotation)
        );
        (*lua)["obe"]["Polygon"]["get"] = kaguya::function([](Transform::Polygon& polygon, Transform::point_index_t index) {
            return &polygon.get(index);
        });
        (*lua)["obe"]["Polygon"]["getAllPoints"] = kaguya::function([](Transform::Polygon& polygon){
            std::vector<Transform::PolygonPoint*> points;
            for (const auto& point : polygon.getAllPoints())
                points.push_back(point.get());
            return points;
        });
        (*lua)["obe"]["Polygon"]["getPointAroundPosition"] = kaguya::function(
            [](Transform::Polygon& polygon, const Transform::UnitVector& position, const Transform::UnitVector& tolerance) {
                auto optret = polygon.getPointAroundPosition(position, tolerance);
                if (optret.has_value())
                {
                    return optret.value();
                }
                else
                {
                    Transform::PolygonPoint* nullpoint = nullptr;
                    return nullpoint;
                }
            }
        );
        (*lua)["obe"]["Polygon"]["getSegmentContainingPoint"] = kaguya::function(Polygon_getSegmentContainingPoint_wrapper());
    }

    void LoadUnits(kaguya::State* lua)
    {
        (*lua)["obe"]["Units"] = kaguya::NewTable();
        (*lua)["obe"]["Units"]["ViewPercentage"] = Transform::Units::ViewPercentage;
        (*lua)["obe"]["Units"]["ViewPixels"] = Transform::Units::ViewPixels;
        (*lua)["obe"]["Units"]["ViewUnits"] = Transform::Units::ViewUnits;
        (*lua)["obe"]["Units"]["ScenePixels"] = Transform::Units::ScenePixels;
        (*lua)["obe"]["Units"]["SceneUnits"] = Transform::Units::SceneUnits;
    }
}