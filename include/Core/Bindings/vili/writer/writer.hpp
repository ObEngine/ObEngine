#pragma once

namespace sol
{
    class state_view;
};
namespace vili::writer::bindings
{
    void load_class_dump_options(sol::state_view state);
    void load_class__array(sol::state_view state);
    void load_class__object(sol::state_view state);
    void load_enum_delimiter_newline_policy(sol::state_view state);
    void load_enum_object_style(sol::state_view state);
    void load_function_dump(sol::state_view state);
};