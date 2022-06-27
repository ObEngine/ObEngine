#include <Bindings/obe/animation/easing/Easing.hpp>

#include <Animation/Easing.hpp>

#include <Bindings/Config.hpp>

namespace obe::animation::easing::bindings
{
    void load_enum_easing_type(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.new_enum<obe::animation::easing::EasingType>("EasingType",
            { { "Linear", obe::animation::easing::EasingType::Linear },
                { "InSine", obe::animation::easing::EasingType::InSine },
                { "OutSine", obe::animation::easing::EasingType::OutSine },
                { "InOutSine", obe::animation::easing::EasingType::InOutSine },
                { "InQuad", obe::animation::easing::EasingType::InQuad },
                { "OutQuad", obe::animation::easing::EasingType::OutQuad },
                { "InOutQuad", obe::animation::easing::EasingType::InOutQuad },
                { "InCubic", obe::animation::easing::EasingType::InCubic },
                { "OutCubic", obe::animation::easing::EasingType::OutCubic },
                { "InOutCubic", obe::animation::easing::EasingType::InOutCubic },
                { "InQuart", obe::animation::easing::EasingType::InQuart },
                { "OutQuart", obe::animation::easing::EasingType::OutQuart },
                { "InOutQuart", obe::animation::easing::EasingType::InOutQuart },
                { "InQuint", obe::animation::easing::EasingType::InQuint },
                { "OutQuint", obe::animation::easing::EasingType::OutQuint },
                { "InOutQuint", obe::animation::easing::EasingType::InOutQuint },
                { "InExpo", obe::animation::easing::EasingType::InExpo },
                { "OutExpo", obe::animation::easing::EasingType::OutExpo },
                { "InOutExpo", obe::animation::easing::EasingType::InOutExpo },
                { "InCirc", obe::animation::easing::EasingType::InCirc },
                { "OutCirc", obe::animation::easing::EasingType::OutCirc },
                { "InOutCirc", obe::animation::easing::EasingType::InOutCirc },
                { "InBack", obe::animation::easing::EasingType::InBack },
                { "OutBack", obe::animation::easing::EasingType::OutBack },
                { "InOutBack", obe::animation::easing::EasingType::InOutBack },
                { "InElastic", obe::animation::easing::EasingType::InElastic },
                { "OutElastic", obe::animation::easing::EasingType::OutElastic },
                { "InOutElastic", obe::animation::easing::EasingType::InOutElastic },
                { "InBounce", obe::animation::easing::EasingType::InBounce },
                { "OutBounce", obe::animation::easing::EasingType::OutBounce },
                { "InOutBounce", obe::animation::easing::EasingType::InOutBounce } });
    }
    void load_function_linear(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("linear", &obe::animation::easing::linear);
    }
    void load_function_in_sine(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_sine", &obe::animation::easing::in_sine);
    }
    void load_function_out_sine(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_sine", &obe::animation::easing::out_sine);
    }
    void load_function_in_out_sine(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_sine", &obe::animation::easing::in_out_sine);
    }
    void load_function_in_quad(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_quad", &obe::animation::easing::in_quad);
    }
    void load_function_out_quad(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_quad", &obe::animation::easing::out_quad);
    }
    void load_function_in_out_quad(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_quad", &obe::animation::easing::in_out_quad);
    }
    void load_function_in_cubic(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_cubic", &obe::animation::easing::in_cubic);
    }
    void load_function_out_cubic(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_cubic", &obe::animation::easing::out_cubic);
    }
    void load_function_in_out_cubic(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_cubic", &obe::animation::easing::in_out_cubic);
    }
    void load_function_in_quart(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_quart", &obe::animation::easing::in_quart);
    }
    void load_function_out_quart(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_quart", &obe::animation::easing::out_quart);
    }
    void load_function_in_out_quart(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_quart", &obe::animation::easing::in_out_quart);
    }
    void load_function_in_quint(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_quint", &obe::animation::easing::in_quint);
    }
    void load_function_out_quint(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_quint", &obe::animation::easing::out_quint);
    }
    void load_function_in_out_quint(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_quint", &obe::animation::easing::in_out_quint);
    }
    void load_function_in_expo(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_expo", &obe::animation::easing::in_expo);
    }
    void load_function_out_expo(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_expo", &obe::animation::easing::out_expo);
    }
    void load_function_in_out_expo(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_expo", &obe::animation::easing::in_out_expo);
    }
    void load_function_in_circ(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_circ", &obe::animation::easing::in_circ);
    }
    void load_function_out_circ(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_circ", &obe::animation::easing::out_circ);
    }
    void load_function_in_out_circ(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_circ", &obe::animation::easing::in_out_circ);
    }
    void load_function_in_back(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_back", &obe::animation::easing::in_back);
    }
    void load_function_out_back(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_back", &obe::animation::easing::out_back);
    }
    void load_function_in_out_back(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_back", &obe::animation::easing::in_out_back);
    }
    void load_function_in_elastic(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_elastic", &obe::animation::easing::in_elastic);
    }
    void load_function_out_elastic(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_elastic", &obe::animation::easing::out_elastic);
    }
    void load_function_in_out_elastic(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_elastic", &obe::animation::easing::in_out_elastic);
    }
    void load_function_in_bounce(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_bounce", &obe::animation::easing::in_bounce);
    }
    void load_function_out_bounce(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("out_bounce", &obe::animation::easing::out_bounce);
    }
    void load_function_in_out_bounce(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("in_out_bounce", &obe::animation::easing::in_out_bounce);
    }
    void load_function_get(sol::state_view state)
    {
        sol::table easing_namespace = state["obe"]["animation"]["easing"].get<sol::table>();
        easing_namespace.set_function("get",
            sol::overload(
                static_cast<obe::animation::easing::EasingFunction (*)(const std::string&)>(
                    &obe::animation::easing::get),
                static_cast<obe::animation::easing::EasingFunction (*)(
                    obe::animation::easing::EasingType)>(&obe::animation::easing::get)));
    }
};