#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::Cursor::bindings
{
    void load_class_hold(sol::state_view state);
    void load_class_move(sol::state_view state);
    void load_class_press(sol::state_view state);
    void load_class_release(sol::state_view state);
}; // namespace obe::events::Cursor::bindings