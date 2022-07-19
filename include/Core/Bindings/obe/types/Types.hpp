#pragma once

namespace sol
{
    class state_view;
};
namespace obe::types::bindings
{
    void load_class_identifiable(sol::state_view state);
    void load_class_protected_identifiable(sol::state_view state);
    void load_class_selectable(sol::state_view state);
    void load_class_serializable(sol::state_view state);
    void load_class_togglable(sol::state_view state);
    void load_class_unique_identifiable(sol::state_view state);
    void load_class_unknown_enum_entry(sol::state_view state);
};