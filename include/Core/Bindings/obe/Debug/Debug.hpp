#pragma once

namespace sol
{
    class state_view;
};
namespace obe::debug::bindings
{
    void load_enum_log_level(sol::state_view state);
    void load_function_init_logger(sol::state_view state);
    void load_function_trace(sol::state_view state);
    void load_function_debug(sol::state_view state);
    void load_function_info(sol::state_view state);
    void load_function_warn(sol::state_view state);
    void load_function_error(sol::state_view state);
    void load_function_critical(sol::state_view state);
    void load_global_log(sol::state_view state);
};