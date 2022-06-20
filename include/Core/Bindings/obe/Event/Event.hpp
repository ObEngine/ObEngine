#pragma once

namespace sol
{
    class state_view;
};
namespace obe::event::bindings
{
    void load_class_callback_profiler(sol::state_view state);
    void load_class_callback_scheduler(sol::state_view state);
    void load_class_event_base(sol::state_view state);
    void load_class_event_group(sol::state_view state);
    void load_class_event_group_view(sol::state_view state);
    void load_class_event_manager(sol::state_view state);
    void load_class_event_namespace(sol::state_view state);
    void load_class_event_namespace_view(sol::state_view state);
    void load_class_lua_event_listener(sol::state_view state);
    void load_class_scope_profiler(sol::state_view state);
    void load_enum_callback_scheduler_state(sol::state_view state);
    void load_enum_listener_change_state(sol::state_view state);
};