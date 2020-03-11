#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Utils::Math::Bindings
{
    void LoadFunctionRandint(sol::state_view state);
    void LoadFunctionRandfloat(sol::state_view state);
    void LoadFunctionIsDoubleInt(sol::state_view state);
    void LoadFunctionConvertToRadian(sol::state_view state);
    void LoadFunctionConvertToDegree(sol::state_view state);
    void LoadFunctionNormalize(sol::state_view state);
    void LoadGlobalPi(sol::state_view state);
};