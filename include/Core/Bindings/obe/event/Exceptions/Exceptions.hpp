#pragma once

namespace sol
{
    class state_view;
};
namespace obe::event::Exceptions::bindings
{
    void load_class_callback_creation_error(sol::state_view state);
    void load_class_event_already_exists(sol::state_view state);
    void load_class_event_execution_error(sol::state_view state);
    void load_class_event_group_already_exists(sol::state_view state);
    void load_class_event_group_not_joinable(sol::state_view state);
    void load_class_event_namespace_already_exists(sol::state_view state);
    void load_class_event_namespace_not_joinable(sol::state_view state);
    void load_class_unknown_event(sol::state_view state);
    void load_class_unknown_event_group(sol::state_view state);
    void load_class_unknown_event_namespace(sol::state_view state);
};