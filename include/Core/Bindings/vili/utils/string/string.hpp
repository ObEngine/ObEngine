#pragma once

namespace sol
{
    class state_view;
};
namespace vili::utils::string::bindings
{
    void load_function_replace(sol::state_view state);
    void load_function_is_int(sol::state_view state);
    void load_function_is_float(sol::state_view state);
    void load_function_truncate_float(sol::state_view state);
    void load_function_quote(sol::state_view state);
    void load_function_to_double(sol::state_view state);
    void load_function_to_long(sol::state_view state);
    void load_function_indent(sol::state_view state);
    void load_function_distance(sol::state_view state);
    void load_function_sort_by_distance(sol::state_view state);
};