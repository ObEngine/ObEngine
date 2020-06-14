#include <Bindings/obe/Transform/Exceptions/Exceptions.hpp>

#include <Transform/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Transform::Exceptions::Bindings
{
    void LoadClassInvalidUnitsEnumValue(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Transform"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Transform::Exceptions::InvalidUnitsEnumValue>
            bindInvalidUnitsEnumValue
            = ExceptionsNamespace
                  .new_usertype<obe::Transform::Exceptions::InvalidUnitsEnumValue>(
                      "InvalidUnitsEnumValue", sol::call_constructor,
                      sol::constructors<obe::Transform::Exceptions::InvalidUnitsEnumValue(
                          int, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassPolygonNotEnoughPoints(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Transform"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Transform::Exceptions::PolygonNotEnoughPoints>
            bindPolygonNotEnoughPoints = ExceptionsNamespace.new_usertype<
                obe::Transform::Exceptions::PolygonNotEnoughPoints>(
                "PolygonNotEnoughPoints", sol::call_constructor,
                sol::constructors<obe::Transform::Exceptions::PolygonNotEnoughPoints(
                    void*, std::size_t, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassPolygonPointIndexOverflow(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Transform"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Transform::Exceptions::PolygonPointIndexOverflow>
            bindPolygonPointIndexOverflow = ExceptionsNamespace.new_usertype<
                obe::Transform::Exceptions::PolygonPointIndexOverflow>(
                "PolygonPointIndexOverflow", sol::call_constructor,
                sol::constructors<obe::Transform::Exceptions::PolygonPointIndexOverflow(
                    void*, std::size_t, std::size_t, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownReferential(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Transform"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Transform::Exceptions::UnknownReferential>
            bindUnknownReferential
            = ExceptionsNamespace
                  .new_usertype<obe::Transform::Exceptions::UnknownReferential>(
                      "UnknownReferential", sol::call_constructor,
                      sol::constructors<obe::Transform::Exceptions::UnknownReferential(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownUnit(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Transform"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Transform::Exceptions::UnknownUnit> bindUnknownUnit
            = ExceptionsNamespace.new_usertype<obe::Transform::Exceptions::UnknownUnit>(
                "UnknownUnit", sol::call_constructor,
                sol::constructors<obe::Transform::Exceptions::UnknownUnit(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};