#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Graphics::Utils::Bindings
{
    void LoadFunctionDrawPoint(sol::state_view state);
    void LoadFunctionDrawLine(sol::state_view state);
    void LoadFunctionDrawPolygon(sol::state_view state);
};