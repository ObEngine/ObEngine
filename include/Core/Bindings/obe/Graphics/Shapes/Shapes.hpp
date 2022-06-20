#pragma once

namespace sol
{
    class state_view;
};
namespace obe::graphics::shapes::bindings
{
    void load_class_circle(sol::state_view state);
    void load_class_polygon(sol::state_view state);
    void load_class_rectangle(sol::state_view state);
    void load_class_text(sol::state_view state);
};