#include <Bindings/Utils/Math/Math.hpp>

#include <Utils/MathUtils.hpp>

#include <sol/sol.hpp>

namespace obe::Utils::Math::Bindings
{
    void LoadFunctionRandint(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("randint", obe::Utils::Math::randint);
    }
    void LoadFunctionRandfloat(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("randfloat", obe::Utils::Math::randfloat);
    }
    void LoadFunctionIsDoubleInt(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("isDoubleInt", obe::Utils::Math::isDoubleInt);
    }
    void LoadFunctionConvertToRadian(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("convertToRadian", obe::Utils::Math::convertToRadian);
    }
    void LoadFunctionConvertToDegree(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("convertToDegree", obe::Utils::Math::convertToDegree);
    }
    void LoadFunctionNormalize(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("normalize", obe::Utils::Math::normalize);
    }
    void LoadGlobalPi(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace["pi"] = obe::Utils::Math::pi;
    }
};