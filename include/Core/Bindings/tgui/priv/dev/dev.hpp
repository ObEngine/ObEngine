#pragma once

namespace sol
{
    class state_view;
};
namespace tgui::priv::dev::Bindings
{
    void LoadClassBackgroundComponent(sol::state_view state);
    void LoadClassComponent(sol::state_view state);
    void LoadClassGroupComponent(sol::state_view state);
    void LoadClassImageComponent(sol::state_view state);
    void LoadClassMessageBroker(sol::state_view state);
    void LoadClassStylePropertyBase(sol::state_view state);
    void LoadClassTextComponent(sol::state_view state);
    void LoadClassStylePropertyBackground(sol::state_view state);
    void LoadClassStylePropertyText(sol::state_view state);
    void LoadEnumComponentState(sol::state_view state);
    void LoadEnumAlignLayout(sol::state_view state);
    void LoadEnumPositionAlignment(sol::state_view state);
    void LoadFunctionGetStateFromFlags(sol::state_view state);
    void LoadFunctionSetOptionalPropertyValue(sol::state_view state);
};