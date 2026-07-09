#pragma once

namespace sol
{
    class state_view;
};
namespace obe::script::Helpers::bindings
{
    void load_function_make_all_helpers(sol::state_view state);
    void load_function_fetch_from_one_of(sol::state_view state);
    void load_function_rawget_from(sol::state_view state);
    void load_function_len_from(sol::state_view state);
    void load_function_pairs_from(sol::state_view state);
    void load_function_ordered_table(sol::state_view state);
};