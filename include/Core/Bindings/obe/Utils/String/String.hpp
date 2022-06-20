#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::string::bindings
{
    void load_function_split(sol::state_view state);
    void load_function_occurences_in_string(sol::state_view state);
    void load_function_is_string_alpha(sol::state_view state);
    void load_function_is_string_alpha_numeric(sol::state_view state);
    void load_function_is_string_numeric(sol::state_view state);
    void load_function_is_string_int(sol::state_view state);
    void load_function_is_string_float(sol::state_view state);
    void load_function_replace(sol::state_view state);
    void load_function_is_surrounded_by(sol::state_view state);
    void load_function_get_random_key(sol::state_view state);
    void load_function_contains(sol::state_view state);
    void load_function_starts_with(sol::state_view state);
    void load_function_ends_with(sol::state_view state);
    void load_function_distance(sol::state_view state);
    void load_function_sort_by_distance(sol::state_view state);
    void load_function_quote(sol::state_view state);
    void load_function_titleize(sol::state_view state);
    void load_global_alphabet(sol::state_view state);
    void load_global_numbers(sol::state_view state);
};