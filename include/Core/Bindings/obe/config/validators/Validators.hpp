#pragma once

namespace sol
{
    class state_view;
};
namespace obe::config::validators::bindings
{
    void load_function_animation_validator(sol::state_view state);
    void load_function_config_validator(sol::state_view state);
    void load_function_mount_validator(sol::state_view state);
    void load_function_project_validator(sol::state_view state);
};