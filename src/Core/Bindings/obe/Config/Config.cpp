#include <Bindings/obe/Config/Config.hpp>

#include <Config/Config.hpp>
#include <Config/Git.hpp>

#include <Bindings/Config.hpp>

namespace obe::Config::Bindings
{
    void LoadClassConfigurationManager(sol::state_view state)
    {
        sol::table ConfigNamespace = state["obe"]["Config"].get<sol::table>();
        sol::usertype<obe::Config::ConfigurationManager> bindConfigurationManager
            = ConfigNamespace.new_usertype<obe::Config::ConfigurationManager>(
                "ConfigurationManager", sol::call_constructor,
                sol::constructors<obe::Config::ConfigurationManager()>(),
                sol::base_classes, sol::bases<vili::node>());
        bindConfigurationManager["load"] = &obe::Config::ConfigurationManager::load;
    }
    void LoadGlobalOBENGINEGITBRANCH(sol::state_view state)
    {
        sol::table ConfigNamespace = state["obe"]["Config"].get<sol::table>();
        ConfigNamespace["OBENGINE_GIT_BRANCH"] = obe::Config::OBENGINE_GIT_BRANCH;
    }
    void LoadGlobalOBENGINEGITHASH(sol::state_view state)
    {
        sol::table ConfigNamespace = state["obe"]["Config"].get<sol::table>();
        ConfigNamespace["OBENGINE_GIT_HASH"] = obe::Config::OBENGINE_GIT_HASH;
    }
    void LoadGlobalOBENGINEVERSION(sol::state_view state)
    {
        sol::table ConfigNamespace = state["obe"]["Config"].get<sol::table>();
        ConfigNamespace["OBENGINE_VERSION"] = obe::Config::OBENGINE_VERSION;
    }
};