#pragma once

namespace sol
{
    class state_view;
};
namespace obe::config::validators::Bindings
{
    void LoadFunctionAnimationValidator(sol::state_view state);
    void LoadFunctionConfigValidator(sol::state_view state);
    void LoadFunctionMountValidator(sol::state_view state);
    void LoadFunctionProjectValidator(sol::state_view state);
};