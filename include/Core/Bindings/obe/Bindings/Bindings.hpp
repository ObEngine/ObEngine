#pragma once

namespace sol
{
    class state_view;
};
namespace obe::bindings::bindings
{
    void load_function_index_core_bindings(sol::state_view state);
};