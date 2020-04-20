#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Graphics::Canvas::Bindings
{
    void LoadClassBezier(sol::state_view state);
    void LoadClassCanvas(sol::state_view state);
    void LoadClassCanvasElement(sol::state_view state);
    void LoadClassCanvasPositionable(sol::state_view state);
    void LoadClassCircle(sol::state_view state);
    void LoadClassLine(sol::state_view state);
    void LoadClassPolygon(sol::state_view state);
    void LoadClassRectangle(sol::state_view state);
    void LoadClassText(sol::state_view state);
    void LoadEnumCanvasElementType(sol::state_view state);
    void LoadEnumTextHorizontalAlign(sol::state_view state);
    void LoadEnumTextVerticalAlign(sol::state_view state);
    void LoadFunctionCanvasElementTypeToString(sol::state_view state);
};