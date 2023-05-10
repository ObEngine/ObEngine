#include <Bindings/obe/utils/math/Math.hpp>

#include <Utils/MathUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::math::bindings
{
    void load_function_randbool(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("randbool", &obe::utils::math::randbool);
    }
    void load_function_randint(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("randint",
            sol::overload(static_cast<uint16_t (*)(uint16_t, uint16_t)>(&obe::utils::math::randint),
                static_cast<uint32_t (*)(uint32_t, uint32_t)>(&obe::utils::math::randint),
                static_cast<uint64_t (*)(uint64_t, uint64_t)>(&obe::utils::math::randint),
                static_cast<int16_t (*)(int16_t, int16_t)>(&obe::utils::math::randint),
                static_cast<int32_t (*)(int32_t, int32_t)>(&obe::utils::math::randint),
                static_cast<int64_t (*)(int64_t, int64_t)>(&obe::utils::math::randint)));
    }
    void load_function_randfloat(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("randfloat", &obe::utils::math::randfloat);
    }
    void load_function_get_min(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("get_min",
            sol::overload(static_cast<int (*)(const int&, const int&)>(&obe::utils::math::get_min),
                static_cast<double (*)(const double&, const double&)>(&obe::utils::math::get_min)));
    }
    void load_function_get_max(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("get_max",
            sol::overload(static_cast<int (*)(const int&, const int&)>(&obe::utils::math::get_max),
                static_cast<double (*)(const double&, const double&)>(&obe::utils::math::get_max)));
    }
    void load_function_is_between(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("is_between",
            sol::overload(static_cast<bool (*)(const int&, const int&, const int&)>(
                              &obe::utils::math::is_between),
                static_cast<bool (*)(const int&, const int&, const double&)>(
                    &obe::utils::math::is_between),
                static_cast<bool (*)(const int&, const double&, const int&)>(
                    &obe::utils::math::is_between),
                static_cast<bool (*)(const int&, const double&, const double&)>(
                    &obe::utils::math::is_between),
                static_cast<bool (*)(const double&, const int&, const int&)>(
                    &obe::utils::math::is_between),
                static_cast<bool (*)(const double&, const int&, const double&)>(
                    &obe::utils::math::is_between),
                static_cast<bool (*)(const double&, const double&, const int&)>(
                    &obe::utils::math::is_between),
                static_cast<bool (*)(const double&, const double&, const double&)>(
                    &obe::utils::math::is_between)));
    }
    void load_function_is_double_int(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("is_double_int", &obe::utils::math::is_double_int);
    }
    void load_function_sign(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("sign",
            sol::overload(static_cast<int (*)(int)>(&obe::utils::math::sign),
                static_cast<int (*)(double)>(&obe::utils::math::sign)));
    }
    void load_function_convert_to_radian(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("convert_to_radian", &obe::utils::math::convert_to_radian);
    }
    void load_function_convert_to_degrees(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("convert_to_degrees", &obe::utils::math::convert_to_degrees);
    }
    void load_function_normalize(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace.set_function("normalize", &obe::utils::math::normalize);
    }
    void load_global_pi(sol::state_view state)
    {
        sol::table math_namespace = state["obe"]["utils"]["math"].get<sol::table>();
        math_namespace["pi"] = obe::utils::math::pi;
    }
};