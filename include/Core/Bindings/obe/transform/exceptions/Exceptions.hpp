#pragma once

namespace sol
{
    class state_view;
};
namespace obe::transform::exceptions::bindings
{
    void load_class_polygon_not_enough_points(sol::state_view state);
    void load_class_polygon_point_index_overflow(sol::state_view state);
    void load_class_unknown_referential(sol::state_view state);
};