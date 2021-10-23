#pragma once

namespace sol
{
    class state_view;
};
namespace tgui::priv::Bindings
{
    void LoadClassAnimation(sol::state_view state);
    void LoadClassFadeAnimation(sol::state_view state);
    void LoadClassMoveAnimation(sol::state_view state);
    void LoadClassResizeAnimation(sol::state_view state);
    void LoadFunctionCheckAndLogOpenGlError(sol::state_view state);
};