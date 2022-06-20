#pragma once

namespace sol
{
    class state_view;
};
namespace obe::animation::easing::bindings
{
    void load_enum_easing_type(sol::state_view state);
    void load_function_linear(sol::state_view state);
    void load_function_in_sine(sol::state_view state);
    void load_function_out_sine(sol::state_view state);
    void load_function_in_out_sine(sol::state_view state);
    void load_function_in_quad(sol::state_view state);
    void load_function_out_quad(sol::state_view state);
    void load_function_in_out_quad(sol::state_view state);
    void load_function_in_cubic(sol::state_view state);
    void load_function_out_cubic(sol::state_view state);
    void load_function_in_out_cubic(sol::state_view state);
    void load_function_in_quart(sol::state_view state);
    void load_function_out_quart(sol::state_view state);
    void load_function_in_out_quart(sol::state_view state);
    void load_function_in_quint(sol::state_view state);
    void load_function_out_quint(sol::state_view state);
    void load_function_in_out_quint(sol::state_view state);
    void load_function_in_expo(sol::state_view state);
    void load_function_out_expo(sol::state_view state);
    void load_function_in_out_expo(sol::state_view state);
    void load_function_in_circ(sol::state_view state);
    void load_function_out_circ(sol::state_view state);
    void load_function_in_out_circ(sol::state_view state);
    void load_function_in_back(sol::state_view state);
    void load_function_out_back(sol::state_view state);
    void load_function_in_out_back(sol::state_view state);
    void load_function_in_elastic(sol::state_view state);
    void load_function_out_elastic(sol::state_view state);
    void load_function_in_out_elastic(sol::state_view state);
    void load_function_in_bounce(sol::state_view state);
    void load_function_out_bounce(sol::state_view state);
    void load_function_in_out_bounce(sol::state_view state);
    void load_function_get(sol::state_view state);
};