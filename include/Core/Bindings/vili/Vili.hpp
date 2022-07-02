#pragma once

namespace sol
{
    class state_view;
};
namespace vili::bindings
{
    void load_class_const_node_iterator(sol::state_view state);
    void load_class_node(sol::state_view state);
    void load_class_node_iterator(sol::state_view state);
    void load_enum_node_type(sol::state_view state);
    void load_function_from_string(sol::state_view state);
    void load_function_to_string(sol::state_view state);
    void load_global_permissive_cast(sol::state_view state);
    void load_global_verbose_exceptions(sol::state_view state);
    void load_global_true_value(sol::state_view state);
    void load_global_false_value(sol::state_view state);
    void load_global_null_typename(sol::state_view state);
    void load_global_boolean_typename(sol::state_view state);
    void load_global_integer_typename(sol::state_view state);
    void load_global_number_typename(sol::state_view state);
    void load_global_string_typename(sol::state_view state);
    void load_global_object_typename(sol::state_view state);
    void load_global_array_typename(sol::state_view state);
    void load_global_unknown_typename(sol::state_view state);
    void load_global_container_typename(sol::state_view state);
}; // namespace vili::bindings