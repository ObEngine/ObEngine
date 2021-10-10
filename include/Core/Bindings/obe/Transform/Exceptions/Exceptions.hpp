#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Transform::Exceptions::Bindings
{
    void LoadClassInvalidUnitsEnumValue(sol::state_view state);
    void LoadClassPolygonNotEnoughPoints(sol::state_view state);
    void LoadClassPolygonPointIndexOverflow(sol::state_view state);
    void LoadClassUnknownReferential(sol::state_view state);
    void LoadClassUnknownUnit(sol::state_view state);
};