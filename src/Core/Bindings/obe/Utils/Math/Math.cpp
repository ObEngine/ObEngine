#include <Bindings/obe/Utils/Math/Math.hpp>

#include <Utils/MathUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::Utils::Math::Bindings
{
    void LoadFunctionRandint(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("randint", &obe::Utils::Math::randint);
    }
    void LoadFunctionRandfloat(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("randfloat", &obe::Utils::Math::randfloat);
    }
    void LoadFunctionGetMin(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("get_min",
            sol::overload(static_cast<int (*)(const int&, const int&)>(&obe::Utils::Math::get_min),
                static_cast<double (*)(const double&, const double&)>(&obe::Utils::Math::get_min)));
    }
    void LoadFunctionGetMax(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("get_max",
            sol::overload(static_cast<int (*)(const int&, const int&)>(&obe::Utils::Math::get_max),
                static_cast<double (*)(const double&, const double&)>(&obe::Utils::Math::get_max)));
    }
    void LoadFunctionIsBetween(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("is_between",
            sol::overload(static_cast<bool (*)(const int&, const int&, const int&)>(
                              &obe::Utils::Math::is_between),
                static_cast<bool (*)(const int&, const int&, const double&)>(
                    &obe::Utils::Math::is_between),
                static_cast<bool (*)(const int&, const double&, const int&)>(
                    &obe::Utils::Math::is_between),
                static_cast<bool (*)(const int&, const double&, const double&)>(
                    &obe::Utils::Math::is_between),
                static_cast<bool (*)(const double&, const int&, const int&)>(
                    &obe::Utils::Math::is_between),
                static_cast<bool (*)(const double&, const int&, const double&)>(
                    &obe::Utils::Math::is_between),
                static_cast<bool (*)(const double&, const double&, const int&)>(
                    &obe::Utils::Math::is_between),
                static_cast<bool (*)(const double&, const double&, const double&)>(
                    &obe::Utils::Math::is_between)));
    }
    void LoadFunctionIsDoubleInt(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("is_double_int", &obe::Utils::Math::is_double_int);
    }
    void LoadFunctionSign(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("sign",
            sol::overload(static_cast<int (*)(int)>(&obe::Utils::Math::sign),
                static_cast<int (*)(double)>(&obe::Utils::Math::sign)));
    }
    void LoadFunctionConvertToRadian(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("convert_to_radian", &obe::Utils::Math::convert_to_radian);
    }
    void LoadFunctionConvertToDegree(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("convert_to_degrees", &obe::Utils::Math::convert_to_degrees);
    }
    void LoadFunctionNormalize(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("normalize", &obe::Utils::Math::normalize);
    }
    void LoadGlobalPi(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace["pi"] = obe::Utils::Math::pi;
    }
};