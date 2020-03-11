#include <Bindings/Transform/Transform.hpp>

#include <Transform/Matrix2D.hpp>
#include <Transform/Movable.hpp>
#include <Transform/Polygon.hpp>
#include <Transform/Rect.hpp>
#include <Transform/Referential.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitVector.hpp>
#include <Transform/Units.hpp>

#include <sol/sol.hpp>

namespace obe::Transform::Bindings
{
    void LoadEnumUnits(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        TransformNamespace.new_enum<obe::Transform::Units>("Units",
            { { "ViewPercentage", obe::Transform::Units::ViewPercentage },
                { "ViewPixels", obe::Transform::Units::ViewPixels },
                { "ViewUnits", obe::Transform::Units::ViewUnits },
                { "ScenePixels", obe::Transform::Units::ScenePixels },
                { "SceneUnits", obe::Transform::Units::SceneUnits } });
    }
    void LoadClassMatrix2D(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        sol::usertype<obe::Transform::Matrix2D> bindMatrix2D
            = TransformNamespace.new_usertype<obe::Transform::Matrix2D>("Matrix2D",
                sol::call_constructor,
                sol::constructors<obe::Transform::Matrix2D(std::array<double, 4>)>());
        bindMatrix2D["product"] = &obe::Transform::Matrix2D::product;
    }
    void LoadClassMovable(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        sol::usertype<obe::Transform::Movable> bindMovable
            = TransformNamespace.new_usertype<obe::Transform::Movable>(
                "Movable", sol::call_constructor, sol::default_constructor);
        bindMovable["setPosition"] = &obe::Transform::Movable::setPosition;
        bindMovable["move"] = &obe::Transform::Movable::move;
        bindMovable["getPosition"] = &obe::Transform::Movable::getPosition;
    }
    void LoadClassPolygon(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        sol::usertype<obe::Transform::Polygon> bindPolygon
            = TransformNamespace.new_usertype<obe::Transform::Polygon>(
                "Polygon", sol::call_constructor, sol::default_constructor);
        bindPolygon["addPoint"] = &obe::Transform::Polygon::addPoint;
        bindPolygon["findClosestSegment"] = &obe::Transform::Polygon::findClosestSegment;
        bindPolygon["findClosestPoint"] = &obe::Transform::Polygon::findClosestPoint;
        bindPolygon["getAllPoints"] = &obe::Transform::Polygon::getAllPoints;
        bindPolygon["getCentroid"] = &obe::Transform::Polygon::getCentroid;
        bindPolygon["getPointsAmount"] = &obe::Transform::Polygon::getPointsAmount;
        bindPolygon["getPosition"] = &obe::Transform::Polygon::getPosition;
        bindPolygon["getRotation"] = &obe::Transform::Polygon::getRotation;
        bindPolygon["getSegment"] = &obe::Transform::Polygon::getSegment;
        bindPolygon["getSegmentContainingPoint"]
            = &obe::Transform::Polygon::getSegmentContainingPoint;
        bindPolygon["isCentroidAroundPosition"]
            = &obe::Transform::Polygon::isCentroidAroundPosition;
        bindPolygon["getPointAroundPosition"]
            = &obe::Transform::Polygon::getPointAroundPosition;
        bindPolygon["move"] = &obe::Transform::Polygon::move;
        bindPolygon["rotate"] = &obe::Transform::Polygon::rotate;
        bindPolygon["setPosition"] = &obe::Transform::Polygon::setPosition;
        bindPolygon["setRotation"] = &obe::Transform::Polygon::setRotation;
        bindPolygon["setPositionFromCentroid"]
            = &obe::Transform::Polygon::setPositionFromCentroid;
        bindPolygon["operator[]"] = &obe::Transform::Polygon::operator[];
        bindPolygon["get"] = &obe::Transform::Polygon::get;
        bindPolygon["getBoundingBox"] = &obe::Transform::Polygon::getBoundingBox;
    }
    void LoadClassPolygonPoint(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        sol::usertype<obe::Transform::PolygonPoint> bindPolygonPoint
            = TransformNamespace.new_usertype<obe::Transform::PolygonPoint>(
                "PolygonPoint", sol::call_constructor,
                sol::constructors<obe::Transform::PolygonPoint(
                                      obe::Transform::Polygon&, unsigned int),
                    obe::Transform::PolygonPoint(obe::Transform::Polygon&, unsigned int,
                        const obe::Transform::UnitVector&)>());
        bindPolygonPoint["remove"] = &obe::Transform::PolygonPoint::remove;
        bindPolygonPoint["distance"] = &obe::Transform::PolygonPoint::distance;
        bindPolygonPoint["getRelativePosition"]
            = &obe::Transform::PolygonPoint::getRelativePosition;
        bindPolygonPoint["setRelativePosition"]
            = &obe::Transform::PolygonPoint::setRelativePosition;
        bindPolygonPoint["move"] = &obe::Transform::PolygonPoint::move;
        bindPolygonPoint["index"] = sol::property(
            [](obe::Transform::PolygonPoint* self) { return self->index; });
    }
    void LoadClassPolygonSegment(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        sol::usertype<obe::Transform::PolygonSegment> bindPolygonSegment
            = TransformNamespace.new_usertype<obe::Transform::PolygonSegment>(
                "PolygonSegment", sol::call_constructor,
                sol::constructors<obe::Transform::PolygonSegment(
                    const obe::Transform::PolygonPoint&,
                    const obe::Transform::PolygonPoint&)>());
        bindPolygonSegment["getAngle"] = &obe::Transform::PolygonSegment::getAngle;
        bindPolygonSegment["getLength"] = &obe::Transform::PolygonSegment::getLength;
        bindPolygonSegment["first"] = sol::property(
            [](obe::Transform::PolygonSegment* self) { return self->first; });
        bindPolygonSegment["second"] = sol::property(
            [](obe::Transform::PolygonSegment* self) { return self->second; });
    }
    void LoadClassRect(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        sol::usertype<obe::Transform::Rect> bindRect
            = TransformNamespace.new_usertype<obe::Transform::Rect>("Rect",
                sol::call_constructor,
                sol::constructors<obe::Transform::Rect(),
                    obe::Transform::Rect(const obe::Transform::UnitVector&,
                        const obe::Transform::UnitVector&)>());
        bindRect["transformRef"] = &obe::Transform::Rect::transformRef;
        bindRect["setPosition"] = sol::overload(
            static_cast<void (obe::Transform::Rect::*)(
                const obe::Transform::UnitVector&)>(&obe::Transform::Rect::setPosition),
            static_cast<void (obe::Transform::Rect::*)(const obe::Transform::UnitVector&,
                obe::Transform::Referential)>(&obe::Transform::Rect::setPosition));
        bindRect["getPosition"] = sol::overload(
            static_cast<obe::Transform::UnitVector (obe::Transform::Rect::*)() const>(
                &obe::Transform::Rect::getPosition),
            static_cast<obe::Transform::UnitVector (obe::Transform::Rect::*)(
                obe::Transform::Referential) const>(&obe::Transform::Rect::getPosition));
        bindRect["move"] = &obe::Transform::Rect::move;
        bindRect["setPointPosition"] = &obe::Transform::Rect::setPointPosition;
        bindRect["movePoint"] = &obe::Transform::Rect::movePoint;
        bindRect["setSize"] = &obe::Transform::Rect::setSize;
        bindRect["scale"] = &obe::Transform::Rect::scale;
        bindRect["getSize"] = &obe::Transform::Rect::getSize;
        bindRect["getScaleFactor"] = &obe::Transform::Rect::getScaleFactor;
        bindRect["getRotation"] = &obe::Transform::Rect::getRotation;
        bindRect["setRotation"] = &obe::Transform::Rect::setRotation;
        bindRect["rotate"] = &obe::Transform::Rect::rotate;
        bindRect["draw"] = &obe::Transform::Rect::draw;
    }
    void LoadClassReferential(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        sol::usertype<obe::Transform::Referential> bindReferential
            = TransformNamespace.new_usertype<obe::Transform::Referential>("Referential",
                sol::call_constructor,
                sol::constructors<obe::Transform::Referential(),
                    obe::Transform::Referential(double, double)>());
        bindReferential[sol::meta_function::equal_to]
            = &obe::Transform::Referential::operator==;
        bindReferential["flip"] = &obe::Transform::Referential::flip;
        bindReferential["isOnLeftSide"] = &obe::Transform::Referential::isOnLeftSide;
        bindReferential["isOnRightSide"] = &obe::Transform::Referential::isOnRightSide;
        bindReferential["isOnTopSide"] = &obe::Transform::Referential::isOnTopSide;
        bindReferential["isOnBottomSide"] = &obe::Transform::Referential::isOnBottomSide;
        bindReferential["isOnCorner"] = &obe::Transform::Referential::isOnCorner;
        bindReferential["isOnSide"] = &obe::Transform::Referential::isOnSide;
        bindReferential["isKnown"] = &obe::Transform::Referential::isKnown;
        bindReferential["getOffset"] = &obe::Transform::Referential::getOffset;
        bindReferential["toString"] = &obe::Transform::Referential::toString;
    }
    void LoadClassUnitBasedObject(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        sol::usertype<obe::Transform::UnitBasedObject> bindUnitBasedObject
            = TransformNamespace.new_usertype<obe::Transform::UnitBasedObject>(
                "UnitBasedObject");
        bindUnitBasedObject["setWorkingUnit"]
            = &obe::Transform::UnitBasedObject::setWorkingUnit;
        bindUnitBasedObject["getWorkingUnit"]
            = &obe::Transform::UnitBasedObject::getWorkingUnit;
    }
    void LoadClassUnitVector(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        sol::usertype<obe::Transform::UnitVector> bindUnitVector
            = TransformNamespace.new_usertype<obe::Transform::UnitVector>("UnitVector",
                sol::call_constructor,
                sol::constructors<obe::Transform::UnitVector(),
                    obe::Transform::UnitVector(obe::Transform::Units),
                    obe::Transform::UnitVector(double, double),
                    obe::Transform::UnitVector(double, double, obe::Transform::Units)>());
        bindUnitVector["set"] = sol::overload(
            static_cast<void (obe::Transform::UnitVector::*)(
                const obe::Transform::UnitVector&)>(&obe::Transform::UnitVector::set),
            static_cast<void (obe::Transform::UnitVector::*)(double, double)>(
                &obe::Transform::UnitVector::set));
        bindUnitVector["add"] = sol::overload(
            static_cast<void (obe::Transform::UnitVector::*)(
                const obe::Transform::UnitVector&)>(&obe::Transform::UnitVector::add),
            static_cast<void (obe::Transform::UnitVector::*)(double, double)>(
                &obe::Transform::UnitVector::add));
        bindUnitVector[sol::meta_function::addition] = sol::overload(
            static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(
                const obe::Transform::UnitVector&) const>(
                &obe::Transform::UnitVector::operator+),
            static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(double)
                    const>(&obe::Transform::UnitVector::operator+));
        bindUnitVector[sol::meta_function::subtraction] = sol::overload(
            static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(
                const obe::Transform::UnitVector&) const>(
                &obe::Transform::UnitVector::operator-),
            static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(double)
                    const>(&obe::Transform::UnitVector::operator-),
            static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)()
                    const>(&obe::Transform::UnitVector::operator-));
        bindUnitVector[sol::meta_function::multiplication] = sol::overload(
            static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(
                const obe::Transform::UnitVector&) const>(
                &obe::Transform::UnitVector::operator*),
            static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(double)
                    const>(&obe::Transform::UnitVector::operator*));
        bindUnitVector[sol::meta_function::division] = sol::overload(
            static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(
                const obe::Transform::UnitVector&) const>(
                &obe::Transform::UnitVector::operator/),
            static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(double)
                    const>(&obe::Transform::UnitVector::operator/));
        bindUnitVector[sol::meta_function::equal_to]
            = &obe::Transform::UnitVector::operator==;
        // bindUnitVector["to"] = &obe::Transform::UnitVector::to;
        bindUnitVector["unpack"] = &obe::Transform::UnitVector::unpack;
        bindUnitVector["rotate"] = &obe::Transform::UnitVector::rotate;
        bindUnitVector["distance"] = &obe::Transform::UnitVector::distance;
        // bindUnitVector["Init"] = sol::overload(static_cast<void (*)(obe::Transform::ViewStruct *&) >(&obe::Transform::UnitVector::Init), static_cast<void (*)(int, int) >(&obe::Transform::UnitVector::Init));
        bindUnitVector["x"] = sol::readonly(&obe::Transform::UnitVector::x);
        bindUnitVector["y"] = sol::readonly(&obe::Transform::UnitVector::y);
        bindUnitVector["unit"] = sol::readonly(&obe::Transform::UnitVector::unit);
    }
    void LoadFunctionStringToUnits(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        TransformNamespace.set_function("stringToUnits", obe::Transform::stringToUnits);
    }
    void LoadFunctionUnitsToString(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
        TransformNamespace.set_function("unitsToString", obe::Transform::unitsToString);
    }
};