#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::base64::bindings
{
    void load_function_encode(sol::state_view state);
    void load_function_decode(sol::state_view state);
    void load_global_base64_chars(sol::state_view state);
};