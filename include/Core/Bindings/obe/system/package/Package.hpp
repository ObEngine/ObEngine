#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::package::bindings
{
    void load_function_get_package_location(sol::state_view state);
    void load_function_package_exists(sol::state_view state);
    void load_function_list_packages(sol::state_view state);
    void load_function_install(sol::state_view state);
    void load_function_load(sol::state_view state);
};