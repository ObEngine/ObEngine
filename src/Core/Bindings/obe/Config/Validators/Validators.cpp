#include <Bindings/obe/Config/Validators/Validators.hpp>

#include <Config/Validators.hpp>

#include <Bindings/Config.hpp>

namespace obe::config::validators::Bindings
{
    void LoadFunctionAnimationValidator(sol::state_view state)
    {
        sol::table ValidatorsNamespace = state["obe"]["config"]["validators"].get<sol::table>();
        ValidatorsNamespace.set_function(
            "animation_validator", &obe::config::validators::animation_validator);
    }
    void LoadFunctionConfigValidator(sol::state_view state)
    {
        sol::table ValidatorsNamespace = state["obe"]["config"]["validators"].get<sol::table>();
        ValidatorsNamespace.set_function(
            "config_validator", &obe::config::validators::config_validator);
    }
    void LoadFunctionMountValidator(sol::state_view state)
    {
        sol::table ValidatorsNamespace = state["obe"]["config"]["validators"].get<sol::table>();
        ValidatorsNamespace.set_function(
            "mount_validator", &obe::config::validators::mount_validator);
    }
    void LoadFunctionProjectValidator(sol::state_view state)
    {
        sol::table ValidatorsNamespace = state["obe"]["config"]["validators"].get<sol::table>();
        ValidatorsNamespace.set_function(
            "project_validator", &obe::config::validators::project_validator);
    }
};