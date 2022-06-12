#include <Bindings/obe/Animation/Easing/Easing.hpp>

#include <Animation/Easing.hpp>

#include <Bindings/Config.hpp>

namespace obe::animation::easing::Bindings
{
    void LoadEnumEasingType(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.new_enum<obe::animation::easing::EasingType>("EasingType",
            { { "linear", obe::animation::easing::EasingType::Linear },
                { "in_sine", obe::animation::easing::EasingType::InSine },
                { "out_sine", obe::animation::easing::EasingType::OutSine },
                { "in_out_sine", obe::animation::easing::EasingType::InOutSine },
                { "in_quad", obe::animation::easing::EasingType::InQuad },
                { "out_quad", obe::animation::easing::EasingType::OutQuad },
                { "in_out_quad", obe::animation::easing::EasingType::InOutQuad },
                { "in_cubic", obe::animation::easing::EasingType::InCubic },
                { "out_cubic", obe::animation::easing::EasingType::OutCubic },
                { "in_out_cubic", obe::animation::easing::EasingType::InOutCubic },
                { "in_quart", obe::animation::easing::EasingType::InQuart },
                { "out_quart", obe::animation::easing::EasingType::OutQuart },
                { "in_out_quart", obe::animation::easing::EasingType::InOutQuart },
                { "in_quint", obe::animation::easing::EasingType::InQuint },
                { "out_quint", obe::animation::easing::EasingType::OutQuint },
                { "in_out_quint", obe::animation::easing::EasingType::InOutQuint },
                { "in_expo", obe::animation::easing::EasingType::InExpo },
                { "out_expo", obe::animation::easing::EasingType::OutExpo },
                { "in_out_expo", obe::animation::easing::EasingType::InOutExpo },
                { "in_circ", obe::animation::easing::EasingType::InCirc },
                { "out_circ", obe::animation::easing::EasingType::OutCirc },
                { "in_out_circ", obe::animation::easing::EasingType::InOutCirc },
                { "in_back", obe::animation::easing::EasingType::InBack },
                { "out_back", obe::animation::easing::EasingType::OutBack },
                { "in_out_back", obe::animation::easing::EasingType::InOutBack },
                { "in_elastic", obe::animation::easing::EasingType::InElastic },
                { "out_elastic", obe::animation::easing::EasingType::OutElastic },
                { "in_out_elastic", obe::animation::easing::EasingType::InOutElastic },
                { "in_bounce", obe::animation::easing::EasingType::InBounce },
                { "out_bounce", obe::animation::easing::EasingType::OutBounce },
                { "in_out_bounce", obe::animation::easing::EasingType::InOutBounce } });
    }
    void LoadFunctionLinear(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("linear", &obe::animation::easing::linear);
    }
    void LoadFunctionInSine(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_sine", &obe::animation::easing::in_sine);
    }
    void LoadFunctionOutSine(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_sine", &obe::animation::easing::out_sine);
    }
    void LoadFunctionInOutSine(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_sine", &obe::animation::easing::in_out_sine);
    }
    void LoadFunctionInQuad(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_quad", &obe::animation::easing::in_quad);
    }
    void LoadFunctionOutQuad(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_quad", &obe::animation::easing::out_quad);
    }
    void LoadFunctionInOutQuad(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_quad", &obe::animation::easing::in_out_quad);
    }
    void LoadFunctionInCubic(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_cubic", &obe::animation::easing::in_cubic);
    }
    void LoadFunctionOutCubic(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_cubic", &obe::animation::easing::out_cubic);
    }
    void LoadFunctionInOutCubic(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_cubic", &obe::animation::easing::in_out_cubic);
    }
    void LoadFunctionInQuart(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_quart", &obe::animation::easing::in_quart);
    }
    void LoadFunctionOutQuart(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_quart", &obe::animation::easing::out_quart);
    }
    void LoadFunctionInOutQuart(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_quart", &obe::animation::easing::in_out_quart);
    }
    void LoadFunctionInQuint(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_quint", &obe::animation::easing::in_quint);
    }
    void LoadFunctionOutQuint(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_quint", &obe::animation::easing::out_quint);
    }
    void LoadFunctionInOutQuint(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_quint", &obe::animation::easing::in_out_quint);
    }
    void LoadFunctionInExpo(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_expo", &obe::animation::easing::in_expo);
    }
    void LoadFunctionOutExpo(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_expo", &obe::animation::easing::out_expo);
    }
    void LoadFunctionInOutExpo(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_expo", &obe::animation::easing::in_out_expo);
    }
    void LoadFunctionInCirc(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_circ", &obe::animation::easing::in_circ);
    }
    void LoadFunctionOutCirc(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_circ", &obe::animation::easing::out_circ);
    }
    void LoadFunctionInOutCirc(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_circ", &obe::animation::easing::in_out_circ);
    }
    void LoadFunctionInBack(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_back", &obe::animation::easing::in_back);
    }
    void LoadFunctionOutBack(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_back", &obe::animation::easing::out_back);
    }
    void LoadFunctionInOutBack(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_back", &obe::animation::easing::in_out_back);
    }
    void LoadFunctionInElastic(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_elastic", &obe::animation::easing::in_elastic);
    }
    void LoadFunctionOutElastic(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_elastic", &obe::animation::easing::out_elastic);
    }
    void LoadFunctionInOutElastic(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_elastic", &obe::animation::easing::in_out_elastic);
    }
    void LoadFunctionInBounce(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_bounce", &obe::animation::easing::in_bounce);
    }
    void LoadFunctionOutBounce(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("out_bounce", &obe::animation::easing::out_bounce);
    }
    void LoadFunctionInOutBounce(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("in_out_bounce", &obe::animation::easing::in_out_bounce);
    }
    void LoadFunctionGet(sol::state_view state)
    {
        sol::table EasingNamespace = state["obe"]["animation"]["easing"].get<sol::table>();
        EasingNamespace.set_function("get",
            sol::overload(
                static_cast<obe::animation::easing::EasingFunction (*)(const std::string&)>(
                    &obe::animation::easing::get),
                static_cast<obe::animation::easing::EasingFunction (*)(
                    obe::animation::easing::EasingType)>(&obe::animation::easing::get)));
    }
};