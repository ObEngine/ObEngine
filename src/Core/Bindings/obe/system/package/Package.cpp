#include <Bindings/obe/system/package/Package.hpp>

#include <System/Package.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::package::bindings
{
    void load_function_get_package_location(sol::state_view state)
    {
        sol::table package_namespace = state["obe"]["system"]["package"].get<sol::table>();
        package_namespace.set_function(
            "get_package_location", &obe::system::package::get_package_location);
    }
    void load_function_package_exists(sol::state_view state)
    {
        sol::table package_namespace = state["obe"]["system"]["package"].get<sol::table>();
        package_namespace.set_function("package_exists", &obe::system::package::package_exists);
    }
    void load_function_list_packages(sol::state_view state)
    {
        sol::table package_namespace = state["obe"]["system"]["package"].get<sol::table>();
        package_namespace.set_function("list_packages", &obe::system::package::list_packages);
    }
    void load_function_install(sol::state_view state)
    {
        sol::table package_namespace = state["obe"]["system"]["package"].get<sol::table>();
        package_namespace.set_function("install", &obe::system::package::install);
    }
    void load_function_load(sol::state_view state)
    {
        sol::table package_namespace = state["obe"]["system"]["package"].get<sol::table>();
        package_namespace.set_function("load",
            sol::overload(
                [](const std::string& package_name, const std::string& prefix) -> bool
                {
                    return obe::system::package::load(package_name, prefix);
                },
                [](const std::string& package_name, const std::string& prefix,
                    unsigned int priority) -> bool
                {
                    return obe::system::package::load(package_name, prefix, priority);
                }));
    }
};