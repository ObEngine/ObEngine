#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Animation::Exceptions::Bindings
{
    void LoadClassAnimationGroupTextureIndexOverflow(sol::state_view state);
    void LoadClassAnimationTextureIndexOverflow(sol::state_view state);
    void LoadClassNoSelectedAnimation(sol::state_view state);
    void LoadClassNoSelectedAnimationGroup(sol::state_view state);
    void LoadClassUnknownAnimation(sol::state_view state);
    void LoadClassUnknownAnimationCommand(sol::state_view state);
    void LoadClassUnknownAnimationGroup(sol::state_view state);
    void LoadClassUnknownAnimationPlayMode(sol::state_view state);
    void LoadClassUnknownEasingFromEnum(sol::state_view state);
    void LoadClassUnknownEasingFromString(sol::state_view state);
};