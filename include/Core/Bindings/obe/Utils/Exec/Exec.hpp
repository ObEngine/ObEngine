#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::exec::bindings
{
    void load_class_run_args_parser(sol::state_view state);
};