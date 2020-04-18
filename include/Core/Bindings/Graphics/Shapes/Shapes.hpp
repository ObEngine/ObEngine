#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Graphics::Shapes::Bindings
{
    void LoadClassCircle(sol::state_view state);
    void LoadClassPolygon(sol::state_view state);
    void LoadClassRectangle(sol::state_view state);
    void LoadClassText(sol::state_view state);
};