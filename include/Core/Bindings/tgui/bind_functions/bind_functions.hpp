#pragma once

namespace sol
{
    class state_view;
};
namespace tgui::bind_functions::Bindings
{
    void LoadFunctionBindPosX(sol::state_view state);
    void LoadFunctionBindPosY(sol::state_view state);
    void LoadFunctionBindLeft(sol::state_view state);
    void LoadFunctionBindTop(sol::state_view state);
    void LoadFunctionBindWidth(sol::state_view state);
    void LoadFunctionBindHeight(sol::state_view state);
    void LoadFunctionBindInnerWidth(sol::state_view state);
    void LoadFunctionBindInnerHeight(sol::state_view state);
    void LoadFunctionBindRight(sol::state_view state);
    void LoadFunctionBindBottom(sol::state_view state);
    void LoadFunctionBindPosition(sol::state_view state);
    void LoadFunctionBindSize(sol::state_view state);
    void LoadFunctionBindInnerSize(sol::state_view state);
    void LoadFunctionBindMin(sol::state_view state);
    void LoadFunctionBindMax(sol::state_view state);
};