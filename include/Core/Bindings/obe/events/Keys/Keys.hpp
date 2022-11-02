#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::Keys::bindings
{
    void load_class_pressed(sol::state_view state);
    void load_class_state_changed(sol::state_view state);
};