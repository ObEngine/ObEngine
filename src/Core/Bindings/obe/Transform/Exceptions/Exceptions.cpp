#include <Bindings/obe/Transform/Exceptions/Exceptions.hpp>

#include <Transform/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::transform::exceptions::Bindings
{
    void LoadClassPolygonNotEnoughPoints(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["transform"]["exceptions"].get<sol::table>();
        sol::usertype<obe::transform::exceptions::PolygonNotEnoughPoints> bindPolygonNotEnoughPoints
            = ExceptionsNamespace.new_usertype<obe::transform::exceptions::PolygonNotEnoughPoints>(
                "PolygonNotEnoughPoints", sol::call_constructor,
                sol::constructors<obe::transform::exceptions::PolygonNotEnoughPoints(
                    void*, std::size_t, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::transform::exceptions::PolygonNotEnoughPoints>,
                    obe::BaseException>());
    }
    void LoadClassPolygonPointIndexOverflow(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["transform"]["exceptions"].get<sol::table>();
        sol::usertype<obe::transform::exceptions::PolygonPointIndexOverflow>
            bindPolygonPointIndexOverflow = ExceptionsNamespace.new_usertype<
                obe::transform::exceptions::PolygonPointIndexOverflow>("PolygonPointIndexOverflow",
                sol::call_constructor,
                sol::constructors<obe::transform::exceptions::PolygonPointIndexOverflow(
                    const void*, std::size_t, std::size_t, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::transform::exceptions::PolygonPointIndexOverflow>,
                    obe::BaseException>());
    }
    void LoadClassUnknownReferential(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["transform"]["exceptions"].get<sol::table>();
        sol::usertype<obe::transform::exceptions::UnknownReferential> bindUnknownReferential
            = ExceptionsNamespace.new_usertype<obe::transform::exceptions::UnknownReferential>(
                "UnknownReferential", sol::call_constructor,
                sol::constructors<obe::transform::exceptions::UnknownReferential(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::transform::exceptions::UnknownReferential>,
                    obe::BaseException>());
    }
};