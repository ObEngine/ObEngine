#include <Bindings/obe/Utils/Math/Math.hpp>

#include <Utils/MathUtils.hpp>

#include <Bindings/Config.hpp>

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
    void LoadFunctionGetMin(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("obe::Utils::Math::getMin",
            sol::overload(
                static_cast<int (*)(const int&, const int&)>(obe::Utils::Math::getMin),
                static_cast<double (*)(const double&, const double&)>(
                    obe::Utils::Math::getMin)));
    }
    void LoadFunctionGetMax(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("obe::Utils::Math::getMax",
            sol::overload(
                static_cast<int (*)(const int&, const int&)>(obe::Utils::Math::getMax),
                static_cast<double (*)(const double&, const double&)>(
                    obe::Utils::Math::getMax)));
    }
    void LoadFunctionIsBetween(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("obe::Utils::Math::isBetween",
            sol::overload(static_cast<bool (*)(const int&, const int&, const int&)>(
                              obe::Utils::Math::isBetween),
                static_cast<bool (*)(const int&, const int&, const double&)>(
                    obe::Utils::Math::isBetween),
                static_cast<bool (*)(const int&, const double&, const int&)>(
                    obe::Utils::Math::isBetween),
                static_cast<bool (*)(const int&, const double&, const double&)>(
                    obe::Utils::Math::isBetween),
                static_cast<bool (*)(const double&, const int&, const int&)>(
                    obe::Utils::Math::isBetween),
                static_cast<bool (*)(const double&, const int&, const double&)>(
                    obe::Utils::Math::isBetween),
                static_cast<bool (*)(const double&, const double&, const int&)>(
                    obe::Utils::Math::isBetween),
                static_cast<bool (*)(const double&, const double&, const double&)>(
                    obe::Utils::Math::isBetween)));
    }
    void LoadFunctionIsDoubleInt(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("isDoubleInt", obe::Utils::Math::isDoubleInt);
    }
    void LoadFunctionSign(sol::state_view state)
    {
        sol::table MathNamespace = state["obe"]["Utils"]["Math"].get<sol::table>();
        MathNamespace.set_function("obe::Utils::Math::sign",
            sol::overload(static_cast<int (*)(int)>(obe::Utils::Math::sign),
                static_cast<int (*)(double)>(obe::Utils::Math::sign)));
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