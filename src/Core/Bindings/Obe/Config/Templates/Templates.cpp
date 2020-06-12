#include <Bindings/obe/Config/Templates/Templates.hpp>

#include <Config/Templates/Animation.hpp>
#include <Config/Templates/Mount.hpp>

#include <Bindings/Config.hpp>

namespace obe::Config::Templates::Bindings
{
    void LoadFunctionGetAnimationTemplates(sol::state_view state)
    {
        sol::table TemplatesNamespace
            = state["obe"]["Config"]["Templates"].get<sol::table>();
        TemplatesNamespace.set_function(
            "getAnimationTemplates", obe::Config::Templates::getAnimationTemplates);
    }
    void LoadFunctionGetMountTemplates(sol::state_view state)
    {
        sol::table TemplatesNamespace
            = state["obe"]["Config"]["Templates"].get<sol::table>();
        TemplatesNamespace.set_function(
            "getMountTemplates", obe::Config::Templates::getMountTemplates);
    }
    void LoadGlobalWaitCommand(sol::state_view state)
    {
        sol::table TemplatesNamespace
            = state["obe"]["Config"]["Templates"].get<sol::table>();
        TemplatesNamespace["wait_command"] = obe::Config::Templates::wait_command;
    }
    void LoadGlobalPlayGroupCommand(sol::state_view state)
    {
        sol::table TemplatesNamespace
            = state["obe"]["Config"]["Templates"].get<sol::table>();
        TemplatesNamespace["play_group_command"]
            = obe::Config::Templates::play_group_command;
    }
    void LoadGlobalSetAnimationCommand(sol::state_view state)
    {
        sol::table TemplatesNamespace
            = state["obe"]["Config"]["Templates"].get<sol::table>();
        TemplatesNamespace["set_animation_command"]
            = obe::Config::Templates::set_animation_command;
    }
};