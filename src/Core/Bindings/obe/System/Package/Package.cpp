#include <Bindings/obe/System/Package/Package.hpp>

#include <System/Package.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::package::Bindings
{
    void LoadFunctionGetPackageLocation(sol::state_view state)
    {
        sol::table PackageNamespace = state["obe"]["system"]["package"].get<sol::table>();
        PackageNamespace.set_function(
            "get_package_location", &obe::system::package::get_package_location);
    }
    void LoadFunctionPackageExists(sol::state_view state)
    {
        sol::table PackageNamespace = state["obe"]["system"]["package"].get<sol::table>();
        PackageNamespace.set_function("package_exists", &obe::system::package::package_exists);
    }
    void LoadFunctionListPackages(sol::state_view state)
    {
        sol::table PackageNamespace = state["obe"]["system"]["package"].get<sol::table>();
        PackageNamespace.set_function("list_packages", &obe::system::package::list_packages);
    }
    void LoadFunctionInstall(sol::state_view state)
    {
        sol::table PackageNamespace = state["obe"]["system"]["package"].get<sol::table>();
        PackageNamespace.set_function("install", &obe::system::package::install);
    }
    void LoadFunctionLoad(sol::state_view state)
    {
        sol::table PackageNamespace = state["obe"]["system"]["package"].get<sol::table>();
        PackageNamespace.set_function("load",
            sol::overload([](const std::string& packageName, const std::string& prefix)
                              -> bool { return obe::system::package::load(packageName, prefix); },
                [](const std::string& packageName, const std::string& prefix, unsigned int priority)
                    -> bool { return obe::system::package::load(packageName, prefix, priority); }));
    }
};