#pragma once

namespace sol
{
    class state_view;
};
namespace obe::time::bindings
{
    void load_class_chronometer(sol::state_view state);
    void load_class_framerate_counter(sol::state_view state);
    void load_class_framerate_manager(sol::state_view state);
    void load_function_epoch(sol::state_view state);
    void load_global_seconds(sol::state_view state);
    void load_global_milliseconds(sol::state_view state);
    void load_global_microseconds(sol::state_view state);
    void load_global_minutes(sol::state_view state);
    void load_global_hours(sol::state_view state);
    void load_global_days(sol::state_view state);
    void load_global_weeks(sol::state_view state);
}; // namespace obe::time::bindings