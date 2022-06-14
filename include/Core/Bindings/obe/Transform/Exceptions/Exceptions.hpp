#pragma once

namespace sol
{
    class state_view;
};
namespace obe::transform::exceptions::Bindings
{
    void LoadClassPolygonNotEnoughPoints(sol::state_view state);
    void LoadClassPolygonPointIndexOverflow(sol::state_view state);
    void LoadClassUnknownReferential(sol::state_view state);
};