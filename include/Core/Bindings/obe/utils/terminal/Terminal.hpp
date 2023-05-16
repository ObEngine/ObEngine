#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::terminal::bindings
{
    void load_function_styled_print(sol::state_view state);
};