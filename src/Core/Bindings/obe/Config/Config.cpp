#include <Bindings/obe/Config/Config.hpp>

#include <Config/Config.hpp>
#include <Config/Version.hpp>

#include <Bindings/Config.hpp>

namespace obe::config::Bindings
{
    void LoadClassConfigurationManager(sol::state_view state)
    {
        sol::table ConfigNamespace = state["obe"]["config"].get<sol::table>();
        sol::usertype<obe::config::ConfigurationManager> bindConfigurationManager
            = ConfigNamespace.new_usertype<obe::config::ConfigurationManager>(
                "ConfigurationManager", sol::call_constructor,
                sol::constructors<obe::config::ConfigurationManager()>(), sol::base_classes,
                sol::bases<vili::node>());
        bindConfigurationManager["load"] = &obe::config::ConfigurationManager::load;
    }
    void LoadClassVersion(sol::state_view state)
    {
        sol::table ConfigNamespace = state["obe"]["config"].get<sol::table>();
        sol::usertype<obe::config::Version> bindVersion
            = ConfigNamespace.new_usertype<obe::config::Version>("Version", sol::call_constructor,
                sol::constructors<obe::config::Version(int, int, int),
                    obe::config::Version(const std::string&)>());
        bindVersion["string"] = &obe::config::Version::string;
        bindVersion["major"] = &obe::config::Version::major;
        bindVersion["minor"] = &obe::config::Version::minor;
        bindVersion["patch"] = &obe::config::Version::patch;
    }
};