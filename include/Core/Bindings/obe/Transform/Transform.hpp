#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Transform::Bindings
{
    void LoadClassMatrix2D(sol::state_view state);
    void LoadClassMovable(sol::state_view state);
    void LoadClassPolygon(sol::state_view state);
    void LoadClassPolygonPoint(sol::state_view state);
    void LoadClassPolygonSegment(sol::state_view state);
    void LoadClassRect(sol::state_view state);
    void LoadClassReferential(sol::state_view state);
    void LoadClassUnitBasedObject(sol::state_view state);
    void LoadClassUnitVector(sol::state_view state);
    void LoadEnumRelativePositionFrom(sol::state_view state);
    void LoadEnumFlipAxis(sol::state_view state);
    void LoadEnumUnits(sol::state_view state);
    void LoadFunctionStringToUnits(sol::state_view state);
    void LoadFunctionUnitsToString(sol::state_view state);
};