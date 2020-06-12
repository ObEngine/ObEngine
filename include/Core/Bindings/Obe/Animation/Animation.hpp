#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Animation::Bindings
{
    void LoadClassAnimation(sol::state_view state);
    void LoadClassAnimationGroup(sol::state_view state);
    void LoadClassAnimator(sol::state_view state);
    void LoadClassValueTweening(sol::state_view state);
    void LoadEnumAnimationPlayMode(sol::state_view state);
    void LoadEnumAnimationStatus(sol::state_view state);
    void LoadEnumAnimatorTargetScaleMode(sol::state_view state);
    void LoadFunctionStringToAnimationPlayMode(sol::state_view state);
};