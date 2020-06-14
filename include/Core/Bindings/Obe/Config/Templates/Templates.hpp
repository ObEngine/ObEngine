#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Config::Templates::Bindings
{
    void LoadFunctionGetAnimationTemplates(sol::state_view state);
    void LoadFunctionGetConfigTemplates(sol::state_view state);
    void LoadFunctionGetGameObjectTemplates(sol::state_view state);
    void LoadFunctionGetMountTemplates(sol::state_view state);
    void LoadFunctionGetSceneTemplates(sol::state_view state);
    void LoadGlobalWaitCommand(sol::state_view state);
    void LoadGlobalPlayGroupCommand(sol::state_view state);
    void LoadGlobalSetAnimationCommand(sol::state_view state);
};