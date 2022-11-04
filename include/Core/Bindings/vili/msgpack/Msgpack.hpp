#pragma once

namespace sol
{
    class state_view;
};
namespace vili::msgpack::bindings
{
    void load_function_from_string(sol::state_view state);
    void load_function_to_string(sol::state_view state);
    void load_function_dump_element(sol::state_view state);
};