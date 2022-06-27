#pragma once

namespace sol
{
    class state_view;
};
namespace vili::writer::bindings
{
    void load_class_dump_options(sol::state_view state);
    void load_class__array(sol::state_view state);
    void load_class__items_per_line(sol::state_view state);
    void load_class__object(sol::state_view state);
    void load_class_dump_state(sol::state_view state);
    void load_enum_delimiter_newline_policy(sol::state_view state);
    void load_enum_object_style(sol::state_view state);
    void load_function_dump_integer(sol::state_view state);
    void load_function_dump_number(sol::state_view state);
    void load_function_dump_boolean(sol::state_view state);
    void load_function_dump_string(sol::state_view state);
    void load_function_dump_array(sol::state_view state);
    void load_function_dump_object(sol::state_view state);
    void load_function_dump(sol::state_view state);
};