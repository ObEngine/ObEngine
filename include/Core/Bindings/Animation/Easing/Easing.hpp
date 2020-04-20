#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Animation::Easing::Bindings
{
    void LoadEnumEasingType(sol::state_view state);
    void LoadFunctionLinear(sol::state_view state);
    void LoadFunctionInSine(sol::state_view state);
    void LoadFunctionOutSine(sol::state_view state);
    void LoadFunctionInOutSine(sol::state_view state);
    void LoadFunctionInQuad(sol::state_view state);
    void LoadFunctionOutQuad(sol::state_view state);
    void LoadFunctionInOutQuad(sol::state_view state);
    void LoadFunctionInCubic(sol::state_view state);
    void LoadFunctionOutCubic(sol::state_view state);
    void LoadFunctionInOutCubic(sol::state_view state);
    void LoadFunctionInQuart(sol::state_view state);
    void LoadFunctionOutQuart(sol::state_view state);
    void LoadFunctionInOutQuart(sol::state_view state);
    void LoadFunctionInQuint(sol::state_view state);
    void LoadFunctionOutQuint(sol::state_view state);
    void LoadFunctionInOutQuint(sol::state_view state);
    void LoadFunctionInExpo(sol::state_view state);
    void LoadFunctionOutExpo(sol::state_view state);
    void LoadFunctionInOutExpo(sol::state_view state);
    void LoadFunctionInCirc(sol::state_view state);
    void LoadFunctionOutCirc(sol::state_view state);
    void LoadFunctionInOutCirc(sol::state_view state);
    void LoadFunctionInBack(sol::state_view state);
    void LoadFunctionOutBack(sol::state_view state);
    void LoadFunctionInOutBack(sol::state_view state);
    void LoadFunctionInElastic(sol::state_view state);
    void LoadFunctionOutElastic(sol::state_view state);
    void LoadFunctionInOutElastic(sol::state_view state);
    void LoadFunctionInBounce(sol::state_view state);
    void LoadFunctionOutBounce(sol::state_view state);
    void LoadFunctionInOutBounce(sol::state_view state);
    void LoadFunctionGet(sol::state_view state);
};