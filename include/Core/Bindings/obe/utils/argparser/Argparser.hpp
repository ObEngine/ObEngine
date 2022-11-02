#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::argparser::bindings
{
    void load_function_parse_args(sol::state_view state);
};