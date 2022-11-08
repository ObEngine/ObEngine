#include <Bindings/obe/transform/Transform.hpp>

#include <Transform/AABB.hpp>
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

namespace obe::transform::bindings
{
    void load_enum_referential_conversion_type(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        transform_namespace.new_enum<obe::transform::ReferentialConversionType>(
            "ReferentialConversionType",
            { { "From", obe::transform::ReferentialConversionType::From },
                { "To", obe::transform::ReferentialConversionType::To } });
    }
    void load_enum_flip_axis(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        transform_namespace.new_enum<obe::transform::FlipAxis>("FlipAxis",
            { { "Horizontal", obe::transform::FlipAxis::Horizontal },
                { "Vertical", obe::transform::FlipAxis::Vertical },
                { "Both", obe::transform::FlipAxis::Both } });
    }
    void load_enum_units(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        transform_namespace.new_enum<obe::transform::Units>("Units",
            { { "ViewPercentage", obe::transform::Units::ViewPercentage },
                { "ViewPixels", obe::transform::Units::ViewPixels },
                { "ViewUnits", obe::transform::Units::ViewUnits },
                { "ScenePixels", obe::transform::Units::ScenePixels },
                { "SceneUnits", obe::transform::Units::SceneUnits } });
    }
    void load_enum_relative_position_from(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        transform_namespace.new_enum<obe::transform::PolygonPoint::RelativePositionFrom>(
            "RelativePositionFrom",
            { { "Point0", obe::transform::PolygonPoint::RelativePositionFrom::Point0 },
                { "Centroid", obe::transform::PolygonPoint::RelativePositionFrom::Centroid } });
    }
    void load_class_aabb(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::AABB> bind_aabb
            = transform_namespace.new_usertype<obe::transform::AABB>("AABB", sol::call_constructor,
                sol::constructors<obe::transform::AABB(),
                    obe::transform::AABB(
                        const obe::transform::UnitVector&, const obe::transform::UnitVector&)>(),
                sol::base_classes, sol::bases<obe::transform::Movable>());
        bind_aabb["set_position"] = sol::overload(
            static_cast<void (obe::transform::AABB::*)(const obe::transform::UnitVector&,
                const obe::transform::Referential&)>(&obe::transform::AABB::set_position),
            static_cast<void (obe::transform::AABB::*)(const obe::transform::UnitVector&)>(
                &obe::transform::AABB::set_position));
        bind_aabb["move"] = sol::overload(
            static_cast<void (obe::transform::AABB::*)(const obe::transform::UnitVector&)>(
                &obe::transform::AABB::move),
            static_cast<void (obe::transform::AABB::*)(const obe::transform::UnitVector&)>(
                &obe::transform::AABB::move));
        bind_aabb["get_position"] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::AABB::*)(
                const obe::transform::Referential&) const>(&obe::transform::AABB::get_position),
            static_cast<obe::transform::UnitVector (obe::transform::AABB::*)() const>(
                &obe::transform::AABB::get_position));
        bind_aabb["set_point_position"] = sol::overload(
            [](obe::transform::AABB* self, const obe::transform::UnitVector& position) -> void {
                return self->set_point_position(position);
            },
            [](obe::transform::AABB* self, const obe::transform::UnitVector& position,
                const obe::transform::Referential& ref) -> void {
                return self->set_point_position(position, ref);
            });
        bind_aabb["move_point"] = sol::overload(
            [](obe::transform::AABB* self, const obe::transform::UnitVector& position) -> void {
                return self->move_point(position);
            },
            [](obe::transform::AABB* self, const obe::transform::UnitVector& position,
                const obe::transform::Referential& ref) -> void {
                return self->move_point(position, ref);
            });
        bind_aabb["set_size"] = sol::overload(
            [](obe::transform::AABB* self, const obe::transform::UnitVector& size) -> void {
                return self->set_size(size);
            },
            [](obe::transform::AABB* self, const obe::transform::UnitVector& size,
                const obe::transform::Referential& ref) -> void {
                return self->set_size(size, ref);
            });
        bind_aabb["scale"] = sol::overload(
            [](obe::transform::AABB* self, const obe::transform::UnitVector& size) -> void {
                return self->scale(size);
            },
            [](obe::transform::AABB* self, const obe::transform::UnitVector& size,
                const obe::transform::Referential& ref) -> void { return self->scale(size, ref); });
        bind_aabb["get_size"] = &obe::transform::AABB::get_size;
        bind_aabb["x"] = sol::property(&obe::transform::AABB::x);
        bind_aabb["y"] = sol::property(&obe::transform::AABB::y);
        bind_aabb["width"] = sol::property(&obe::transform::AABB::width);
        bind_aabb["height"] = sol::property(&obe::transform::AABB::height);
        bind_aabb["intersects"] = &obe::transform::AABB::intersects;
        bind_aabb["intersection"] = &obe::transform::AABB::intersection;
        bind_aabb["contains"] = sol::overload(
            static_cast<bool (obe::transform::AABB::*)(const obe::transform::AABB&) const>(
                &obe::transform::AABB::contains),
            static_cast<bool (obe::transform::AABB::*)(const obe::transform::UnitVector&) const>(
                &obe::transform::AABB::contains));
    }
    void load_class_matrix2_d(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Matrix2D> bind_matrix2_d
            = transform_namespace.new_usertype<obe::transform::Matrix2D>("Matrix2D",
                sol::call_constructor,
                sol::constructors<obe::transform::Matrix2D(std::array<double, 4>)>());
        bind_matrix2_d["product"] = &obe::transform::Matrix2D::product;
    }
    void load_class_movable(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Movable> bind_movable
            = transform_namespace.new_usertype<obe::transform::Movable>("Movable",
                sol::call_constructor,
                sol::constructors<obe::transform::Movable(),
                    obe::transform::Movable(const obe::transform::UnitVector&)>());
        bind_movable["set_position"] = &obe::transform::Movable::set_position;
        bind_movable["move"] = &obe::transform::Movable::move;
        bind_movable["get_position"] = &obe::transform::Movable::get_position;
    }
    void load_class_polygon(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Polygon> bind_polygon
            = transform_namespace.new_usertype<obe::transform::Polygon>("Polygon",
                sol::call_constructor,
                sol::constructors<obe::transform::Polygon(),
                    obe::transform::Polygon(const obe::transform::Polygon&)>());
        bind_polygon["add_point"] = sol::overload(
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position) -> void {
                return self->add_point(position);
            },
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position,
                int point_index) -> void { return self->add_point(position, point_index); });
        bind_polygon["find_closest_segment"] = &obe::transform::Polygon::find_closest_segment;
        bind_polygon["find_closest_point"] = sol::overload(
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position)
                -> obe::transform::PolygonPoint& { return self->find_closest_point(position); },
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position,
                bool neighbor) -> obe::transform::PolygonPoint& {
                return self->find_closest_point(position, neighbor);
            },
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position,
                bool neighbor, const std::vector<obe::transform::point_index_t>& excluded_points)
                -> obe::transform::PolygonPoint& {
                return self->find_closest_point(position, neighbor, excluded_points);
            });
        bind_polygon["get_all_points"] = &obe::transform::Polygon::get_all_points;
        bind_polygon["get_centroid"] = &obe::transform::Polygon::get_centroid;
        bind_polygon["get_points_amount"] = &obe::transform::Polygon::get_points_amount;
        bind_polygon["get_position"] = &obe::transform::Polygon::get_position;
        bind_polygon["get_segment"] = &obe::transform::Polygon::get_segment;
        bind_polygon["get_segment_containing_point"] = sol::overload(
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position)
                -> std::optional<obe::transform::PolygonSegment> {
                return self->get_segment_containing_point(position);
            },
            [](obe::transform::Polygon* self, const obe::transform::UnitVector& position,
                double tolerance) -> std::optional<obe::transform::PolygonSegment> {
                return self->get_segment_containing_point(position, tolerance);
            });
        bind_polygon["is_centroid_near_position"]
            = &obe::transform::Polygon::is_centroid_near_position;
        bind_polygon["get_point_near_position"] = &obe::transform::Polygon::get_point_near_position;
        bind_polygon["move"] = &obe::transform::Polygon::move;
        bind_polygon["set_position"] = &obe::transform::Polygon::set_position;
        bind_polygon["set_position_from_centroid"]
            = &obe::transform::Polygon::set_position_from_centroid;
        bind_polygon[sol::meta_function::index] = &obe::transform::Polygon::operator[];
        bind_polygon["get"]
            = sol::overload(static_cast<obe::transform::PolygonPoint& (
                                obe::transform::Polygon::*)(obe::transform::point_index_t)>(
                                &obe::transform::Polygon::get),
                static_cast<const obe::transform::PolygonPoint& (
                    obe::transform::Polygon::*)(obe::transform::point_index_t) const>(
                    &obe::transform::Polygon::get));
        bind_polygon["get_bounding_box"] = &obe::transform::Polygon::get_bounding_box;
        bind_polygon["set_rotation"] = &obe::transform::Polygon::set_rotation;
        bind_polygon["rotate"] = &obe::transform::Polygon::rotate;
        bind_polygon["get_rotation"] = &obe::transform::Polygon::get_rotation;
        bind_polygon["DefaultTolerance"] = sol::var(&obe::transform::Polygon::DefaultTolerance);
    }
    void load_class_polygon_point(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::PolygonPoint> bind_polygon_point
            = transform_namespace.new_usertype<obe::transform::PolygonPoint>("PolygonPoint",
                sol::call_constructor,
                sol::constructors<obe::transform::PolygonPoint(
                                      obe::transform::Polygon&, obe::transform::point_index_t),
                    obe::transform::PolygonPoint(obe::transform::Polygon&,
                        obe::transform::point_index_t, const obe::transform::UnitVector&)>(),
                sol::base_classes, sol::bases<obe::transform::UnitVector>());
        bind_polygon_point["remove"] = &obe::transform::PolygonPoint::remove;
        bind_polygon_point["distance"] = &obe::transform::PolygonPoint::distance;
        bind_polygon_point["get_relative_position"]
            = &obe::transform::PolygonPoint::get_relative_position;
        bind_polygon_point["set_relative_position"]
            = &obe::transform::PolygonPoint::set_relative_position;
        bind_polygon_point["move"] = &obe::transform::PolygonPoint::move;
        bind_polygon_point["index"] = sol::property(
            [](obe::transform::PolygonPoint* self) -> const obe::transform::point_index_t* {
                return &self->index;
            });
    }
    void load_class_polygon_segment(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::PolygonSegment> bind_polygon_segment
            = transform_namespace.new_usertype<obe::transform::PolygonSegment>("PolygonSegment",
                sol::call_constructor,
                sol::constructors<obe::transform::PolygonSegment(
                    const obe::transform::PolygonPoint&, const obe::transform::PolygonPoint&)>());
        bind_polygon_segment["get_angle"] = &obe::transform::PolygonSegment::get_angle;
        bind_polygon_segment["get_length"] = &obe::transform::PolygonSegment::get_length;
        bind_polygon_segment["first"] = sol::property(
            [](obe::transform::PolygonSegment* self) -> const obe::transform::PolygonPoint* {
                return &self->first;
            });
        bind_polygon_segment["second"] = sol::property(
            [](obe::transform::PolygonSegment* self) -> const obe::transform::PolygonPoint* {
                return &self->second;
            });
    }
    void load_class_rect(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Rect> bind_rect
            = transform_namespace.new_usertype<obe::transform::Rect>("Rect", sol::call_constructor,
                sol::constructors<obe::transform::Rect(),
                    obe::transform::Rect(
                        const obe::transform::UnitVector&, const obe::transform::UnitVector&)>(),
                sol::base_classes, sol::bases<obe::transform::Movable>());
        bind_rect["transform_referential"] = &obe::transform::Rect::transform_referential;
        bind_rect["set_position"] = sol::overload(
            static_cast<void (obe::transform::Rect::*)(const obe::transform::UnitVector&,
                const obe::transform::Referential&)>(&obe::transform::Rect::set_position),
            static_cast<void (obe::transform::Rect::*)(const obe::transform::UnitVector&)>(
                &obe::transform::Rect::set_position));
        bind_rect["get_position"] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::Rect::*)(
                const obe::transform::Referential&) const>(&obe::transform::Rect::get_position),
            static_cast<obe::transform::UnitVector (obe::transform::Rect::*)() const>(
                &obe::transform::Rect::get_position));
        bind_rect["set_point_position"] = sol::overload(
            [](obe::transform::Rect* self, const obe::transform::UnitVector& position) -> void {
                return self->set_point_position(position);
            },
            [](obe::transform::Rect* self, const obe::transform::UnitVector& position,
                const obe::transform::Referential& ref) -> void {
                return self->set_point_position(position, ref);
            });
        bind_rect["move_point"] = sol::overload(
            [](obe::transform::Rect* self, const obe::transform::UnitVector& position) -> void {
                return self->move_point(position);
            },
            [](obe::transform::Rect* self, const obe::transform::UnitVector& position,
                const obe::transform::Referential& ref) -> void {
                return self->move_point(position, ref);
            });
        bind_rect["set_size"] = sol::overload(
            [](obe::transform::Rect* self, const obe::transform::UnitVector& size) -> void {
                return self->set_size(size);
            },
            [](obe::transform::Rect* self, const obe::transform::UnitVector& size,
                const obe::transform::Referential& ref) -> void {
                return self->set_size(size, ref);
            });
        bind_rect["scale"] = sol::overload(
            [](obe::transform::Rect* self, const obe::transform::UnitVector& size) -> void {
                return self->scale(size);
            },
            [](obe::transform::Rect* self, const obe::transform::UnitVector& size,
                const obe::transform::Referential& ref) -> void { return self->scale(size, ref); });
        bind_rect["get_size"] = &obe::transform::Rect::get_size;
        bind_rect["get_scale_factor"] = &obe::transform::Rect::get_scale_factor;
        bind_rect["get_rotation"] = &obe::transform::Rect::get_rotation;
        bind_rect["set_rotation"] = &obe::transform::Rect::set_rotation;
        bind_rect["rotate"] = &obe::transform::Rect::rotate;
        bind_rect["draw"] = &obe::transform::Rect::draw;
        bind_rect["x"] = sol::property(&obe::transform::Rect::x);
        bind_rect["y"] = sol::property(&obe::transform::Rect::y);
        bind_rect["width"] = sol::property(&obe::transform::Rect::width);
        bind_rect["height"] = sol::property(&obe::transform::Rect::height);
        bind_rect["intersects"] = &obe::transform::Rect::intersects;
        bind_rect["intersection"] = &obe::transform::Rect::intersection;
        bind_rect["contains"] = sol::overload(
            static_cast<bool (obe::transform::Rect::*)(const obe::transform::Rect&) const>(
                &obe::transform::Rect::contains),
            static_cast<bool (obe::transform::Rect::*)(const obe::transform::UnitVector&) const>(
                &obe::transform::Rect::contains));
        bind_rect["move"] = &obe::transform::Rect::move;
    }
    void load_class_referential(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::Referential> bind_referential
            = transform_namespace.new_usertype<obe::transform::Referential>("Referential",
                sol::call_constructor,
                sol::constructors<obe::transform::Referential(),
                    obe::transform::Referential(double, double)>());
        bind_referential[sol::meta_function::equal_to] = &obe::transform::Referential::operator==;
        bind_referential["flip"] = sol::overload(
            [](obe::transform::Referential* self) -> obe::transform::Referential {
                return self->flip();
            },
            [](obe::transform::Referential* self, obe::transform::FlipAxis axis)
                -> obe::transform::Referential { return self->flip(axis); });
        bind_referential["is_on_left_side"] = &obe::transform::Referential::is_on_left_side;
        bind_referential["is_on_right_side"] = &obe::transform::Referential::is_on_right_side;
        bind_referential["is_on_top_side"] = &obe::transform::Referential::is_on_top_side;
        bind_referential["is_on_bottom_side"] = &obe::transform::Referential::is_on_bottom_side;
        bind_referential["is_on_corner"] = &obe::transform::Referential::is_on_corner;
        bind_referential["is_on_side"] = &obe::transform::Referential::is_on_side;
        bind_referential["is_known"] = &obe::transform::Referential::is_known;
        bind_referential["get_offset"] = &obe::transform::Referential::get_offset;
        bind_referential["to_string"] = &obe::transform::Referential::to_string;
        bind_referential["from_string"] = &obe::transform::Referential::from_string;
        bind_referential["TopLeft"] = sol::var(&obe::transform::Referential::TopLeft);
        bind_referential["Top"] = sol::var(&obe::transform::Referential::Top);
        bind_referential["TopRight"] = sol::var(&obe::transform::Referential::TopRight);
        bind_referential["Left"] = sol::var(&obe::transform::Referential::Left);
        bind_referential["Center"] = sol::var(&obe::transform::Referential::Center);
        bind_referential["Right"] = sol::var(&obe::transform::Referential::Right);
        bind_referential["BottomLeft"] = sol::var(&obe::transform::Referential::BottomLeft);
        bind_referential["Bottom"] = sol::var(&obe::transform::Referential::Bottom);
        bind_referential["BottomRight"] = sol::var(&obe::transform::Referential::BottomRight);
    }
    void load_class_unit_based_object(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::UnitBasedObject> bind_unit_based_object
            = transform_namespace.new_usertype<obe::transform::UnitBasedObject>("UnitBasedObject");
        bind_unit_based_object["set_working_unit"]
            = &obe::transform::UnitBasedObject::set_working_unit;
        bind_unit_based_object["get_working_unit"]
            = &obe::transform::UnitBasedObject::get_working_unit;
    }
    void load_class_unit_vector(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::UnitVector> bind_unit_vector
            = transform_namespace.new_usertype<obe::transform::UnitVector>("UnitVector",
                sol::call_constructor,
                sol::constructors<obe::transform::UnitVector(),
                    obe::transform::UnitVector(obe::transform::Units),
                    obe::transform::UnitVector(double, double),
                    obe::transform::UnitVector(double, double, obe::transform::Units)>());
        bind_unit_vector["set"] = sol::overload(
            static_cast<void (obe::transform::UnitVector::*)(const obe::transform::UnitVector&)>(
                &obe::transform::UnitVector::set),
            static_cast<void (obe::transform::UnitVector::*)(double, double)>(
                &obe::transform::UnitVector::set));
        bind_unit_vector["add"] = sol::overload(
            static_cast<void (obe::transform::UnitVector::*)(const obe::transform::UnitVector&)>(
                &obe::transform::UnitVector::add),
            static_cast<void (obe::transform::UnitVector::*)(double, double)>(
                &obe::transform::UnitVector::add));
        bind_unit_vector[sol::meta_function::addition] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                const obe::transform::UnitVector&) const>(&obe::transform::UnitVector::operator+),
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(double) const>(
                &obe::transform::UnitVector::operator+));
        bind_unit_vector[sol::meta_function::subtraction] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                const obe::transform::UnitVector&) const>(&obe::transform::UnitVector::operator-),
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(double) const>(
                &obe::transform::UnitVector::operator-));
        bind_unit_vector[sol::meta_function::unary_minus]
            = static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)() const>(
                &obe::transform::UnitVector::operator-);
        bind_unit_vector[sol::meta_function::multiplication] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                const obe::transform::UnitVector&) const>(&obe::transform::UnitVector::operator*),
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(double) const>(
                &obe::transform::UnitVector::operator*));
        bind_unit_vector[sol::meta_function::division] = sol::overload(
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                const obe::transform::UnitVector&) const>(&obe::transform::UnitVector::operator/),
            static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(double) const>(
                &obe::transform::UnitVector::operator/));
        bind_unit_vector[sol::meta_function::equal_to] = &obe::transform::UnitVector::operator==;
        bind_unit_vector["to"]
            = static_cast<obe::transform::UnitVector (obe::transform::UnitVector::*)(
                obe::transform::Units) const>(&obe::transform::UnitVector::to);
        bind_unit_vector["unpack"] = &obe::transform::UnitVector::unpack;
        bind_unit_vector["rotate"] = sol::overload(
            [](obe::transform::UnitVector* self, double angle) -> obe::transform::UnitVector {
                return self->rotate(angle);
            },
            [](obe::transform::UnitVector* self, double angle, obe::transform::UnitVector zero)
                -> obe::transform::UnitVector { return self->rotate(angle, zero); });
        bind_unit_vector["distance"] = &obe::transform::UnitVector::distance;
        bind_unit_vector["magnitude"] = &obe::transform::UnitVector::magnitude;
        bind_unit_vector["x"] = &obe::transform::UnitVector::x;
        bind_unit_vector["y"] = &obe::transform::UnitVector::y;
        bind_unit_vector["unit"] = &obe::transform::UnitVector::unit;
    }
    void load_class_screen_struct(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::ScreenStruct> bind_screen_struct
            = transform_namespace.new_usertype<obe::transform::ScreenStruct>(
                "ScreenStruct", sol::call_constructor, sol::default_constructor);
        bind_screen_struct["w"] = &obe::transform::ScreenStruct::w;
        bind_screen_struct["h"] = &obe::transform::ScreenStruct::h;
    }
    void load_class_view_struct(sol::state_view state)
    {
        sol::table transform_namespace = state["obe"]["transform"].get<sol::table>();
        sol::usertype<obe::transform::ViewStruct> bind_view_struct
            = transform_namespace.new_usertype<obe::transform::ViewStruct>(
                "ViewStruct", sol::call_constructor, sol::default_constructor);
        bind_view_struct["w"] = &obe::transform::ViewStruct::w;
        bind_view_struct["h"] = &obe::transform::ViewStruct::h;
        bind_view_struct["x"] = &obe::transform::ViewStruct::x;
        bind_view_struct["y"] = &obe::transform::ViewStruct::y;
    }
};