#include <Bindings/obe/Config/Config.hpp>

#include <Config/Config.hpp>
#include <Config/Version.hpp>

#include <Bindings/Config.hpp>

namespace obe::Config::Bindings
{
    void LoadClassConfigurationManager(sol::state_view state)
    {
        sol::table ConfigNamespace = state["obe"]["Config"].get<sol::table>();
        sol::usertype<obe::Config::ConfigurationManager> bindConfigurationManager
            = ConfigNamespace.new_usertype<obe::Config::ConfigurationManager>(
                "ConfigurationManager", sol::call_constructor,
                sol::constructors<obe::Config::ConfigurationManager()>());
        bindConfigurationManager["load"] = &obe::Config::ConfigurationManager::load;
    }
    void LoadClassVersion(sol::state_view state)
    {
        sol::table ConfigNamespace = state["obe"]["Config"].get<sol::table>();
        sol::usertype<obe::Config::Version> bindVersion
            = ConfigNamespace.new_usertype<obe::Config::Version>("Version", sol::call_constructor,
                sol::constructors<obe::Config::Version(int, int, int),
                    obe::Config::Version(const std::string&)>());
        bindVersion["string"] = &obe::Config::Version::string;
        bindVersion["major"] = &obe::Config::Version::major;
        bindVersion["minor"] = &obe::Config::Version::minor;
        bindVersion["patch"] = &obe::Config::Version::patch;
    }
};