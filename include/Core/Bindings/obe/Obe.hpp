#pragma once

namespace sol
{
    class state_view;
};
namespace obe::bindings
{
    void load_class_base_exception(sol::state_view state);
    void load_function_init_engine(sol::state_view state);
};