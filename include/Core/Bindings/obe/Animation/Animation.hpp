#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Animation::Bindings
{
    void LoadClassAnimation(sol::state_view state);
    void LoadClassAnimationGroup(sol::state_view state);
    void LoadClassAnimationState(sol::state_view state);
    void LoadClassAnimator(sol::state_view state);
    void LoadClassAnimatorState(sol::state_view state);
    void LoadClassColorTweening(sol::state_view state);
    void LoadClassUnitVectorTweening(sol::state_view state);
    void LoadClassRectTweening(sol::state_view state);
    void LoadClassTrajectoryTweening(sol::state_view state);
    void LoadClassIntTweening(sol::state_view state);
    void LoadClassDoubleTweening(sol::state_view state);
    void LoadEnumAnimationPlayMode(sol::state_view state);
    void LoadEnumAnimationStatus(sol::state_view state);
    void LoadEnumAnimatorTargetScaleMode(sol::state_view state);
    void LoadFunctionStringToAnimationPlayMode(sol::state_view state);
    void LoadFunctionStringToAnimatorTargetScaleMode(sol::state_view state);
    void LoadFunctionTemplateSpecializationExistsImpl(sol::state_view state);
    void LoadFunctionTween(sol::state_view state);
};