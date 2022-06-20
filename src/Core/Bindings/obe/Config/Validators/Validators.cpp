#include <Bindings/obe/config/validators/Validators.hpp>

#include <Config/Validators.hpp>

#include <Bindings/Config.hpp>

namespace obe::config::validators::bindings
{
    void load_function_animation_validator(sol::state_view state)
    {
        sol::table validators_namespace = state["obe"]["config"]["validators"].get<sol::table>();
        validators_namespace.set_function(
            "animation_validator", &obe::config::validators::animation_validator);
    }
    void load_function_config_validator(sol::state_view state)
    {
        sol::table validators_namespace = state["obe"]["config"]["validators"].get<sol::table>();
        validators_namespace.set_function(
            "config_validator", &obe::config::validators::config_validator);
    }
    void load_function_mount_validator(sol::state_view state)
    {
        sol::table validators_namespace = state["obe"]["config"]["validators"].get<sol::table>();
        validators_namespace.set_function(
            "mount_validator", &obe::config::validators::mount_validator);
    }
    void load_function_project_validator(sol::state_view state)
    {
        sol::table validators_namespace = state["obe"]["config"]["validators"].get<sol::table>();
        validators_namespace.set_function(
            "project_validator", &obe::config::validators::project_validator);
    }
};