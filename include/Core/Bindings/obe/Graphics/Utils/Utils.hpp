#pragma once

namespace sol
{
    class state_view;
};
namespace obe::graphics::utils::Bindings
{
    void LoadClassDrawPolygonOptions(sol::state_view state);
    void LoadFunctionDrawPoint(sol::state_view state);
    void LoadFunctionDrawLine(sol::state_view state);
    void LoadFunctionDrawPolygon(sol::state_view state);
};