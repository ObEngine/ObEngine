#pragma once

namespace sol
{
    class state_view;
};
namespace vili::parser::bindings
{
    void load_class_node_in_stack(sol::state_view state);
    void load_class_state(sol::state_view state);
    void load_function_from_string(sol::state_view state);
    void load_function_from_file(sol::state_view state);
};