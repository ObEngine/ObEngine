#include <Bindings/Config/Config.hpp>

#include <Config/Config.hpp>

#include <sol/sol.hpp>

namespace obe::Config::Bindings
{
void LoadClassConfigurationManager(sol::state_view state)
{
sol::table ConfigNamespace = state["obe"]["Config"].get<sol::table>();
sol::usertype<obe::Config::ConfigurationManager> bindConfigurationManager = ConfigNamespace.new_usertype<obe::Config::ConfigurationManager>(
"ConfigurationManager", sol::call_constructor, sol::constructors<obe::Config::ConfigurationManager()>());
bindConfigurationManager["load"] = 
&obe::Config::ConfigurationManager::load
;
bindConfigurationManager["get"] = 
&obe::Config::ConfigurationManager::get
;

}
};