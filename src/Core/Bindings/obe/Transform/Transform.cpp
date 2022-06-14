#include <Bindings/obe/Transform/Transform.hpp>

#include <Transform/Matrix2D.hpp>
#include <Transform/Movable.hpp>
#include <Transform/Polygon.hpp>
#include <Transform/Rect.hpp>
#include <Transform/Referential.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitStructures.hpp>
#include <Transform/UnitVector.hpp>
#include <Transform/Units.hpp>

#include <Bindings/Config.hpp>

namespace obe::transform::Bindings
{
    void LoadEnumRelativePositionFrom(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        TransformNamespace.new_enum<obe::transform::PolygonPoint::RelativePositionFrom>(
            "RelativePositionFrom",
            { { "Point0", obe::transform::PolygonPoint::RelativePositionFrom::Point0 },
                { "Centroid", obe::transform::PolygonPoint::RelativePositionFrom::Centroid } });
    }
    void LoadEnumReferentialConversionType(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        TransformNamespace.new_enum<obe::transform::ReferentialConversionType>(
            "ReferentialConversionType",
            { { "From", obe::transform::ReferentialConversionType::From },
                { "To", obe::transform::ReferentialConversionType::To } });
    }
    void LoadEnumFlipAxis(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        TransformNamespace.new_enum<obe::transform::FlipAxis>("FlipAxis",
            { { "Horizontal", obe::transform::FlipAxis::Horizontal },
                { "Vertical", obe::transform::FlipAxis::Vertical },
                { "Both", obe::transform::FlipAxis::Both } });
    }
    void LoadEnumUnits(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        TransformNamespace.new_enum<obe::transform::Units>("Units",
            { { "ViewPercentage", obe::transform::Units::ViewPercentage },
                { "ViewPixels", obe::transform::Units::ViewPixels },
                { "ViewUnits", obe::transform::Units::ViewUnits },
                { "ScenePixels", obe::transform::Units::ScenePixels },
                { "SceneUnits", obe::transform::Units::SceneUnits } });
    }
    void LoadClassMatrix2D(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Matrix2D> bindMatrix2D
            = TransformNamespace.new_usertype<obe::transform::Matrix2D>("Matrix2D",
                sol::call_constructor,
                sol::constructors<obe::transform::Matrix2D(std::array<double, 4>)>());
        bindMatrix2D["product"] = &obe::transform::Matrix2D::product;
    }
    void LoadClassMovable(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Movable> bindMovable
            = TransformNamespace.new_usertype<obe::transform::Movable>(
                "Movable", sol::call_constructor, sol::default_constructor);
        bindMovable["setPosition"] = &obe::transform::Movable::set_position;
        bindMovable["move"] = &obe::transform::Movable::move;
        bindMovable["get_position"] = &obe::transform::Movable::get_position;
    }
    void LoadClassPolygon(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Polygon> bindPolygon
            = TransformNamespace.new_usertype<obe::transform::Polygon>("Polygon",
                sol::call_constructor,
                sol::constructors<obe::transform::Polygon(),
                    obe::transform::Polygon(const obe::transform::Polygon&)>(),
                sol::base_classes,
                sol::bases<obe::transform::UnitBasedObject, obe::transform::Movable>());
        bindPolygon["add_point"] = sol::overload(
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position) -> void {
                return self->add_point(position);
            },
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position,
                int pointIndex) -> void { return self->add_point(position, pointIndex); });
        bindPolygon["find_closest_segment"] = &obe::transform::Polygon::find_closest_segment;
        bindPolygon["find_closest_point"] = sol::overload(
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position)
                -> obe::transform::PolygonPoint& { return self->find_closest_point(position); },
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position,
                bool neighbor) -> obe::transform::PolygonPoint& {
                return self->find_closest_point(position, neighbor);
            },
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position,
                bool neighbor, const std::vector<obe::transform::point_index_t>& excludedPoints)
                -> obe::transform::PolygonPoint& {
                return self->find_closest_point(position, neighbor, excludedPoints);
            });
        bindPolygon["get_all_points"] = &obe::transform::Polygon::get_all_points;
        bindPolygon["get_centroid"] = &obe::transform::Polygon::get_centroid;
        bindPolygon["get_points_amount"] = &obe::transform::Polygon::get_points_amount;
        bindPolygon["get_position"] = &obe::transform::Polygon::get_position;
        bindPolygon["get_rotation"] = &obe::transform::Polygon::get_rotation;
        bindPolygon["get_segment"] = &obe::transform::Polygon::get_segment;
        bindPolygon["get_segment_containing_point"] = sol::overload(
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position)
                -> std::optional<obe::transform::PolygonSegment> {
                return self->get_segment_containing_point(position);
            },
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position,
                double tolerance) -> std::optional<obe::transform::PolygonSegment> {
                return self->get_segment_containing_point(position, tolerance);
            });
        bindPolygon["is_centroid_near_position"]
            = &obe::transform::Polygon::is_centroid_near_position;
        bindPolygon["get_point_near_position"] = &obe::transform::Polygon::get_point_near_position;
        bindPolygon["move"] = &obe::transform::Polygon::move;
        bindPolygon["rotate"] = &obe::transform::Polygon::rotate;
        bindPolygon["setPosition"] = &obe::transform::Polygon::set_position;
        bindPolygon["set_rotation"] = &obe::transform::Polygon::set_rotation;
        bindPolygon["set_position_from_centroid"] = &obe::transform::Polygon::set_position_from_centroid;
        bindPolygon[sol::meta_function::index] = &obe::transform::Polygon::operator[];
        bindPolygon["get"]
            = sol::overload(static_cast<obe::transform::PolygonPoint& (
                                obe::transform::Polygon::*)(obe::transform::point_index_t)>(
                                &obe::transform::Polygon::get),
                static_cast<const obe::transform::PolygonPoint& (
                    obe::transform::Polygon::*)(obe::transform::point_index_t) const>(
                    &obe::transform::Polygon::get));
        bindPolygon["get_bounding_box"] = &obe::transform::Polygon::get_bounding_box;
        bindPolygon["DefaultTolerance"] = sol::var(&obe::transform::Polygon::DefaultTolerance);
    }
    void LoadClassPolygonPoint(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::PolygonPoint> bindPolygonPoint
            = TransformNamespace.new_usertype<obe::transform::PolygonPoint>("PolygonPoint",
                sol::call_constructor,
                sol::constructors<obe::transform::PolygonPoint(
                                      obe::transform::Polygon&, obe::transform::point_index_t),
                    obe::transform::PolygonPoint(obe::transform::Polygon&,
                        obe::transform::point_index_t, const obe::transform::UnitVector&)>(),
                sol::base_classes, sol::bases<obe::transform::UnitVector>());
        bindPolygonPoint["remove"] = &obe::transform::PolygonPoint::remove;
        bindPolygonPoint["distance"] = &obe::transform::PolygonPoint::distance;
        bindPolygonPoint["get_relative_position"]
            = &obe::transform::PolygonPoint::get_relative_position;
        bindPolygonPoint["set_relative_position"]
            = &obe::transform::PolygonPoint::set_relative_position;
        bindPolygonPoint["move"] = &obe::transform::PolygonPoint::move;
        bindPolygonPoint["index"] = sol::property(
            [](obe::transform::PolygonPoint* self) -> const obe::transform::point_index_t& {
                return self->index;
            });
    }
    void LoadClassPolygonSegment(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::PolygonSegment> bindPolygonSegment
            = TransformNamespace.new_usertype<obe::transform::PolygonSegment>("PolygonSegment",
                sol::call_constructor,
                sol::constructors<obe::transform::PolygonSegment(
                    const obe::transform::PolygonPoint&, const obe::transform::PolygonPoint&)>());
        bindPolygonSegment["get_angle"] = &obe::transform::PolygonSegment::get_angle;
        bindPolygonSegment["get_length"] = &obe::transform::PolygonSegment::get_length;
        bindPolygonSegment["first"] = sol::property(
            [](obe::transform::PolygonSegment* self) -> const obe::transform::PolygonPoint& {
                return self->first;
            });
        bindPolygonSegment["second"] = sol::property(
            [](obe::transform::PolygonSegment* self) -> const obe::transform::PolygonPoint& {
                return self->second;
            });
    }
    void LoadClassRect(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Rect> bindRect
            = TransformNamespace.new_usertype<obe::transform::Rect>("Rect", sol::call_constructor,
                sol::constructors<obe::transform::Rect(),
                    obe::transform::Rect(
                        const obe::transform::UnitVector&, const obe::transform::UnitVector&)>(),
                sol::base_classes, sol::bases<obe::transform::Movable>());
        bindRect["transform_referential"] = &obe::transform::Rect::transform_referential;
        bindRect["setPosition"] = sol::overload(
            static_cast<void (obe::transform::Rect::*)(const obe::transform::UnitVector&)>(
                &obe::transform::Rect::set_position),
            static_cast<void (obe::transform::Rect::*)(const obe::transform::UnitVector&,
                const obe::transform::Referential&)>(&obe::transform::Rect::set_position));
        bindRect["get_position"] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::Rect::*)() const>(
                &obe::transform::Rect::get_position),
            static_cast<obe::transform::UnitVector (obe::transform::Rect::*)(
                const obe::transform::Referential&) const>(&obe::transform::Rect::get_position));
        bindRect["move"] = &obe::transform::Rect::move;
        bindRect["set_point_position"] = sol::overload(
            [](obe::transform::Rect* self, const obe::transform::UnitVector& position) -> void {
                return self->set_point_position(position);
            },
            [](obe::transform::Rect* self, const obe::transform::UnitVector& position,
                const obe::transform::Referential& ref) -> void {
                return self->set_point_position(position, ref);
            });
        bindRect["move_point"] = sol::overload(
            [](obe::transform::Rect* self, const obe::transform::UnitVector& position) -> void {
                return self->move_point(position);
            },
            [](obe::transform::Rect* self, const obe::transform::UnitVector& position,
                const obe::transform::Referential& ref) -> void {
                return self->move_point(position, ref);
            });
        bindRect["set_size"] = sol::overload(
            [](obe::transform::Rect* self, const obe::transform::UnitVector& size) -> void {
                return self->set_size(size);
            },
            [](obe::transform::Rect* self, const obe::transform::UnitVector& size,
                const obe::transform::Referential& ref) -> void {
                return self->set_size(size, ref);
            });
        bindRect["scale"] = sol::overload(
            [](obe::transform::Rect* self, const obe::transform::UnitVector& size) -> void {
                return self->scale(size);
            },
            [](obe::transform::Rect* self, const obe::transform::UnitVector& size,
                const obe::transform::Referential& ref) -> void { return self->scale(size, ref); });
        bindRect["getSize"] = &obe::transform::Rect::get_size;
        bindRect["get_scale_factor"] = &obe::transform::Rect::get_scale_factor;
        bindRect["get_rotation"] = &obe::transform::Rect::get_rotation;
        bindRect["set_rotation"] = &obe::transform::Rect::set_rotation;
        bindRect["rotate"] = &obe::transform::Rect::rotate;
        bindRect["draw"] = &obe::transform::Rect::draw;
        bindRect["x"] = sol::property(&obe::transform::Rect::x);
        bindRect["y"] = sol::property(&obe::transform::Rect::y);
        bindRect["width"] = sol::property(&obe::transform::Rect::width);
        bindRect["height"] = sol::property(&obe::transform::Rect::height);
        bindRect["intersects"] = &obe::transform::Rect::intersects;
        bindRect["intersection"] = &obe::transform::Rect::intersection;
        bindRect["contains"] = sol::overload(
            static_cast<bool (obe::transform::Rect::*)(const obe::transform::Rect&) const>(
                &obe::transform::Rect::contains),
            static_cast<bool (obe::transform::Rect::*)(const obe::transform::UnitVector&) const>(
                &obe::transform::Rect::contains));
    }
    void LoadClassReferential(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Referential> bindReferential
            = TransformNamespace.new_usertype<obe::transform::Referential>("Referential",
                sol::call_constructor,
                sol::constructors<obe::transform::Referential(),
                    obe::transform::Referential(double, double)>());
        bindReferential[sol::meta_function::equal_to] = &obe::transform::Referential::operator==;
        bindReferential["flip"] = sol::overload(
            [](obe::transform::Referential* self) -> obe::transform::Referential {
                return self->flip();
            },
            [](obe::transform::Referential* self, obe::transform::FlipAxis axis)
                -> obe::transform::Referential { return self->flip(axis); });
        bindReferential["is_on_left_side"] = &obe::transform::Referential::is_on_left_side;
        bindReferential["is_on_right_side"] = &obe::transform::Referential::is_on_right_side;
        bindReferential["is_on_top_side"] = &obe::transform::Referential::is_on_top_side;
        bindReferential["is_on_bottom_side"] = &obe::transform::Referential::is_on_bottom_side;
        bindReferential["is_on_corner"] = &obe::transform::Referential::is_on_corner;
        bindReferential["is_on_side"] = &obe::transform::Referential::is_on_side;
        bindReferential["is_known"] = &obe::transform::Referential::is_known;
        bindReferential["get_offset"] = &obe::transform::Referential::get_offset;
        bindReferential["to_string"] = sol::overload(
            [](obe::transform::Referential* self) -> std::string { return self->to_string(); },
            [](obe::transform::Referential* self, const std::string& format) -> std::string {
                return self->to_string(format);
            });
        bindReferential["from_string"] = &obe::transform::Referential::from_string;
        bindReferential["TopLeft"] = sol::var(&obe::transform::Referential::TopLeft);
        bindReferential["Top"] = sol::var(&obe::transform::Referential::Top);
        bindReferential["TopRight"] = sol::var(&obe::transform::Referential::TopRight);
        bindReferential["Left"] = sol::var(&obe::transform::Referential::Left);
        bindReferential["Center"] = sol::var(&obe::transform::Referential::Center);
        bindReferential["Right"] = sol::var(&obe::transform::Referential::Right);
        bindReferential["BottomLeft"] = sol::var(&obe::transform::Referential::BottomLeft);
        bindReferential["Bottom"] = sol::var(&obe::transform::Referential::Bottom);
        bindReferential["BottomRight"] = sol::var(&obe::transform::Referential::BottomRight);
    }
    void LoadClassUnitBasedObject(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::UnitBasedObject> bindUnitBasedObject
            = TransformNamespace.new_usertype<obe::transform::UnitBasedObject>("UnitBasedObject");
        bindUnitBasedObject["set_working_unit"] = &obe::transform::UnitBasedObject::set_working_unit;
        bindUnitBasedObject["get_working_unit"] = &obe::transform::UnitBasedObject::get_working_unit;
    }
    void LoadClassUnitVector(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::UnitVector> bindUnitVector
            = TransformNamespace.new_usertype<obe::transform::UnitVector>("UnitVector",
                sol::call_constructor,
                sol::constructors<obe::transform::UnitVector(),
                    obe::transform::UnitVector(obe::transform::Units),
                    obe::transform::UnitVector(double, double),
                    obe::transform::UnitVector(double, double, obe::transform::Units)>());
        bindUnitVector["set"] = sol::overload(
            static_cast<void (obe::transform::UnitVector::*)(const obe::transform::UnitVector&)>(
                &obe::transform::UnitVector::set),
            static_cast<void (obe::transform::UnitVector::*)(double, double)>(
                &obe::transform::UnitVector::set));
        bindUnitVector["add"] = sol::overload(
            static_cast<void (obe::transform::UnitVector::*)(const obe::transform::UnitVector&)>(
                &obe::transform::UnitVector::add),
            static_cast<void (obe::transform::UnitVector::*)(double, double)>(
                &obe::transform::UnitVector::add));
        bindUnitVector[sol::meta_function::addition] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                const obe::transform::UnitVector&) const>(&obe::transform::UnitVector::operator+),
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(double) const>(
                &obe::transform::UnitVector::operator+));
        bindUnitVector[sol::meta_function::subtraction] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                const obe::transform::UnitVector&) const>(&obe::transform::UnitVector::operator-),
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(double) const>(
                &obe::transform::UnitVector::operator-));
        bindUnitVector[sol::meta_function::unary_minus]
            = static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)() const>(
                &obe::transform::UnitVector::operator-);
        bindUnitVector[sol::meta_function::multiplication] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                const obe::transform::UnitVector&) const>(&obe::transform::UnitVector::operator*),
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(double) const>(
                &obe::transform::UnitVector::operator*));
        bindUnitVector[sol::meta_function::division] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                const obe::transform::UnitVector&) const>(&obe::transform::UnitVector::operator/),
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(double) const>(
                &obe::transform::UnitVector::operator/));
        bindUnitVector[sol::meta_function::equal_to] = &obe::transform::UnitVector::operator==;
        bindUnitVector["to"]
            = static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                obe::transform::Units) const>(&obe::transform::UnitVector::to);
        bindUnitVector["unpack"] = &obe::transform::UnitVector::unpack;
        bindUnitVector["rotate"] = sol::overload(
            [](obe::transform::UnitVector* self, double angle) -> obe::transform::UnitVector {
                return self->rotate(angle);
            },
            [](obe::transform::UnitVector* self, double angle, obe::transform::UnitVector zero)
                -> obe::transform::UnitVector { return self->rotate(angle, zero); });
        bindUnitVector["distance"] = &obe::transform::UnitVector::distance;
        bindUnitVector["magnitude"] = &obe::transform::UnitVector::magnitude;
        bindUnitVector["x"] = &obe::transform::UnitVector::x;
        bindUnitVector["y"] = &obe::transform::UnitVector::y;
        bindUnitVector["unit"] = &obe::transform::UnitVector::unit;
    }
    void LoadClassScreenStruct(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::ScreenStruct> bindScreenStruct
            = TransformNamespace.new_usertype<obe::transform::ScreenStruct>(
                "ScreenStruct", sol::call_constructor, sol::default_constructor);
        bindScreenStruct["w"] = &obe::transform::ScreenStruct::w;
        bindScreenStruct["h"] = &obe::transform::ScreenStruct::h;
    }
    void LoadClassViewStruct(sol::state_view state)
    {
        sol::table TransformNamespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::ViewStruct> bindViewStruct
            = TransformNamespace.new_usertype<obe::transform::ViewStruct>(
                "ViewStruct", sol::call_constructor, sol::default_constructor);
        bindViewStruct["w"] = &obe::transform::ViewStruct::w;
        bindViewStruct["h"] = &obe::transform::ViewStruct::h;
        bindViewStruct["x"] = &obe::transform::ViewStruct::x;
        bindViewStruct["y"] = &obe::transform::ViewStruct::y;
    }
};