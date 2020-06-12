#include <Bindings/obe/Animation/Easing/Easing.hpp>

#include <Animation/Easing.hpp>

#include <Bindings/Config.hpp>

namespace obe::Animation::Easing::Bindings
{
    void LoadEnumEasingType(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.new_enum<obe::Animation::Easing::EasingType>("EasingType",
            { { "Linear", obe::Animation::Easing::EasingType::Linear },
                { "InSine", obe::Animation::Easing::EasingType::InSine },
                { "OutSine", obe::Animation::Easing::EasingType::OutSine },
                { "InOutSine", obe::Animation::Easing::EasingType::InOutSine },
                { "InQuad", obe::Animation::Easing::EasingType::InQuad },
                { "OutQuad", obe::Animation::Easing::EasingType::OutQuad },
                { "InOutQuad", obe::Animation::Easing::EasingType::InOutQuad },
                { "InCubic", obe::Animation::Easing::EasingType::InCubic },
                { "OutCubic", obe::Animation::Easing::EasingType::OutCubic },
                { "InOutCubic", obe::Animation::Easing::EasingType::InOutCubic },
                { "InQuart", obe::Animation::Easing::EasingType::InQuart },
                { "OutQuart", obe::Animation::Easing::EasingType::OutQuart },
                { "InOutQuart", obe::Animation::Easing::EasingType::InOutQuart },
                { "InQuint", obe::Animation::Easing::EasingType::InQuint },
                { "OutQuint", obe::Animation::Easing::EasingType::OutQuint },
                { "InOutQuint", obe::Animation::Easing::EasingType::InOutQuint },
                { "InExpo", obe::Animation::Easing::EasingType::InExpo },
                { "OutExpo", obe::Animation::Easing::EasingType::OutExpo },
                { "InOutExpo", obe::Animation::Easing::EasingType::InOutExpo },
                { "InCirc", obe::Animation::Easing::EasingType::InCirc },
                { "OutCirc", obe::Animation::Easing::EasingType::OutCirc },
                { "InOutCirc", obe::Animation::Easing::EasingType::InOutCirc },
                { "InBack", obe::Animation::Easing::EasingType::InBack },
                { "OutBack", obe::Animation::Easing::EasingType::OutBack },
                { "InOutBack", obe::Animation::Easing::EasingType::InOutBack },
                { "InElastic", obe::Animation::Easing::EasingType::InElastic },
                { "OutElastic", obe::Animation::Easing::EasingType::OutElastic },
                { "InOutElastic", obe::Animation::Easing::EasingType::InOutElastic },
                { "InBounce", obe::Animation::Easing::EasingType::InBounce },
                { "OutBounce", obe::Animation::Easing::EasingType::OutBounce },
                { "InOutBounce", obe::Animation::Easing::EasingType::InOutBounce } });
    }
    void LoadFunctionLinear(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("Linear", obe::Animation::Easing::Linear);
    }
    void LoadFunctionInSine(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InSine", obe::Animation::Easing::InSine);
    }
    void LoadFunctionOutSine(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutSine", obe::Animation::Easing::OutSine);
    }
    void LoadFunctionInOutSine(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InOutSine", obe::Animation::Easing::InOutSine);
    }
    void LoadFunctionInQuad(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InQuad", obe::Animation::Easing::InQuad);
    }
    void LoadFunctionOutQuad(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutQuad", obe::Animation::Easing::OutQuad);
    }
    void LoadFunctionInOutQuad(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InOutQuad", obe::Animation::Easing::InOutQuad);
    }
    void LoadFunctionInCubic(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InCubic", obe::Animation::Easing::InCubic);
    }
    void LoadFunctionOutCubic(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutCubic", obe::Animation::Easing::OutCubic);
    }
    void LoadFunctionInOutCubic(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InOutCubic", obe::Animation::Easing::InOutCubic);
    }
    void LoadFunctionInQuart(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InQuart", obe::Animation::Easing::InQuart);
    }
    void LoadFunctionOutQuart(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutQuart", obe::Animation::Easing::OutQuart);
    }
    void LoadFunctionInOutQuart(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InOutQuart", obe::Animation::Easing::InOutQuart);
    }
    void LoadFunctionInQuint(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InQuint", obe::Animation::Easing::InQuint);
    }
    void LoadFunctionOutQuint(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutQuint", obe::Animation::Easing::OutQuint);
    }
    void LoadFunctionInOutQuint(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InOutQuint", obe::Animation::Easing::InOutQuint);
    }
    void LoadFunctionInExpo(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InExpo", obe::Animation::Easing::InExpo);
    }
    void LoadFunctionOutExpo(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutExpo", obe::Animation::Easing::OutExpo);
    }
    void LoadFunctionInOutExpo(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InOutExpo", obe::Animation::Easing::InOutExpo);
    }
    void LoadFunctionInCirc(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InCirc", obe::Animation::Easing::InCirc);
    }
    void LoadFunctionOutCirc(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutCirc", obe::Animation::Easing::OutCirc);
    }
    void LoadFunctionInOutCirc(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InOutCirc", obe::Animation::Easing::InOutCirc);
    }
    void LoadFunctionInBack(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InBack", obe::Animation::Easing::InBack);
    }
    void LoadFunctionOutBack(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutBack", obe::Animation::Easing::OutBack);
    }
    void LoadFunctionInOutBack(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InOutBack", obe::Animation::Easing::InOutBack);
    }
    void LoadFunctionInElastic(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InElastic", obe::Animation::Easing::InElastic);
    }
    void LoadFunctionOutElastic(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutElastic", obe::Animation::Easing::OutElastic);
    }
    void LoadFunctionInOutElastic(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function(
            "InOutElastic", obe::Animation::Easing::InOutElastic);
    }
    void LoadFunctionInBounce(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InBounce", obe::Animation::Easing::InBounce);
    }
    void LoadFunctionOutBounce(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("OutBounce", obe::Animation::Easing::OutBounce);
    }
    void LoadFunctionInOutBounce(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("InOutBounce", obe::Animation::Easing::InOutBounce);
    }
    void LoadFunctionGet(sol::state_view state)
    {
        sol::table EasingNamespace
            = state["obe"]["Animation"]["Easing"].get<sol::table>();
        EasingNamespace.set_function("get",
            sol::overload(static_cast<obe::Animation::Easing::EasingFunction (*)(
                              const std::string&)>(obe::Animation::Easing::get),
                static_cast<obe::Animation::Easing::EasingFunction (*)(
                    obe::Animation::Easing::EasingType)>(obe::Animation::Easing::get)));
    }
};