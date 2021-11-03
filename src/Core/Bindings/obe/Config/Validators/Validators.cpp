#include <Bindings/obe/Config/Validators/Validators.hpp>

#include <Config/Validators.hpp>

#include <Bindings/Config.hpp>

namespace obe::Config::Validators::Bindings
{
    void LoadFunctionAnimationValidator(sol::state_view state)
    {
        sol::table ValidatorsNamespace = state["obe"]["Config"]["Validators"].get<sol::table>();
        ValidatorsNamespace.set_function(
            "AnimationValidator", &obe::Config::Validators::AnimationValidator);
    }
    void LoadFunctionConfigValidator(sol::state_view state)
    {
        sol::table ValidatorsNamespace = state["obe"]["Config"]["Validators"].get<sol::table>();
        ValidatorsNamespace.set_function(
            "ConfigValidator", &obe::Config::Validators::ConfigValidator);
    }
    void LoadFunctionMountValidator(sol::state_view state)
    {
        sol::table ValidatorsNamespace = state["obe"]["Config"]["Validators"].get<sol::table>();
        ValidatorsNamespace.set_function(
            "MountValidator", &obe::Config::Validators::MountValidator);
    }
    void LoadFunctionProjectValidator(sol::state_view state)
    {
        sol::table ValidatorsNamespace = state["obe"]["Config"]["Validators"].get<sol::table>();
        ValidatorsNamespace.set_function(
            "ProjectValidator", &obe::Config::Validators::ProjectValidator);
    }
};