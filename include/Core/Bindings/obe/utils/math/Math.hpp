#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::math::bindings
{
    void load_function_randint(sol::state_view state);
    void load_function_randfloat(sol::state_view state);
    void load_function_get_min(sol::state_view state);
    void load_function_get_max(sol::state_view state);
    void load_function_is_between(sol::state_view state);
    void load_function_is_double_int(sol::state_view state);
    void load_function_sign(sol::state_view state);
    void load_function_convert_to_radian(sol::state_view state);
    void load_function_convert_to_degrees(sol::state_view state);
    void load_function_normalize(sol::state_view state);
    void load_global_pi(sol::state_view state);
};