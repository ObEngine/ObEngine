#include <Bindings/obe/config/Config.hpp>

#include <Config/Config.hpp>
#include <Config/Version.hpp>

#include <Bindings/Config.hpp>

namespace obe::config::bindings
{
    void load_class_configuration_manager(sol::state_view state)
    {
        sol::table config_namespace = state["obe"]["config"].get<sol::table>();
        sol::usertype<obe::config::ConfigurationManager> bind_configuration_manager
            = config_namespace.new_usertype<obe::config::ConfigurationManager>(
                "ConfigurationManager", sol::call_constructor,
                sol::constructors<obe::config::ConfigurationManager()>(), sol::base_classes,
                sol::bases<vili::node>());
        bind_configuration_manager["load"] = &obe::config::ConfigurationManager::load;
    }
    void load_class_version(sol::state_view state)
    {
        sol::table config_namespace = state["obe"]["config"].get<sol::table>();
        sol::usertype<obe::config::Version> bind_version
            = config_namespace.new_usertype<obe::config::Version>("Version", sol::call_constructor,
                sol::constructors<obe::config::Version(int, int, int),
                    obe::config::Version(const std::string&)>());
        bind_version["string"] = &obe::config::Version::string;
        bind_version["major"] = &obe::config::Version::major;
        bind_version["minor"] = &obe::config::Version::minor;
        bind_version["patch"] = &obe::config::Version::patch;
    }
};