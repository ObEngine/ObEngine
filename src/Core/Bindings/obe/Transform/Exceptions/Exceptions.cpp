#include <Bindings/obe/transform/exceptions/Exceptions.hpp>

#include <Transform/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::transform::exceptions::bindings
{
    void load_class_polygon_not_enough_points(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["transform"]["exceptions"].get<sol::table>();
        sol::usertype<obe::transform::exceptions::PolygonNotEnoughPoints>
            bind_polygon_not_enough_points
            = exceptions_namespace.new_usertype<obe::transform::exceptions::PolygonNotEnoughPoints>(
                "PolygonNotEnoughPoints", sol::call_constructor,
                sol::constructors<obe::transform::exceptions::PolygonNotEnoughPoints(
                    void*, std::size_t, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::transform::exceptions::PolygonNotEnoughPoints>,
                    obe::BaseException>());
    }
    void load_class_polygon_point_index_overflow(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["transform"]["exceptions"].get<sol::table>();
        sol::usertype<obe::transform::exceptions::PolygonPointIndexOverflow>
            bind_polygon_point_index_overflow = exceptions_namespace.new_usertype<
                obe::transform::exceptions::PolygonPointIndexOverflow>("PolygonPointIndexOverflow",
                sol::call_constructor,
                sol::constructors<obe::transform::exceptions::PolygonPointIndexOverflow(
                    const void*, std::size_t, std::size_t, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::transform::exceptions::PolygonPointIndexOverflow>,
                    obe::BaseException>());
    }
    void load_class_unknown_referential(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["transform"]["exceptions"].get<sol::table>();
        sol::usertype<obe::transform::exceptions::UnknownReferential> bind_unknown_referential
            = exceptions_namespace.new_usertype<obe::transform::exceptions::UnknownReferential>(
                "UnknownReferential", sol::call_constructor,
                sol::constructors<obe::transform::exceptions::UnknownReferential(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::transform::exceptions::UnknownReferential>,
                    obe::BaseException>());
    }
};