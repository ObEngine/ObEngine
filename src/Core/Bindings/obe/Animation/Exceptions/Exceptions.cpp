#include <Bindings/obe/animation/exceptions/Exceptions.hpp>

#include <Animation/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::animation::exceptions::bindings
{
    void load_class_animation_group_texture_index_overflow(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::AnimationGroupTextureIndexOverflow>
            bind_animation_group_texture_index_overflow = exceptions_namespace.new_usertype<
                obe::animation::exceptions::AnimationGroupTextureIndexOverflow>(
                "AnimationGroupTextureIndexOverflow", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::AnimationGroupTextureIndexOverflow(
                    std::string_view, std::size_t, std::size_t, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<
                    obe::Exception<obe::animation::exceptions::AnimationGroupTextureIndexOverflow>,
                    obe::BaseException>());
    }
    void load_class_animation_texture_index_overflow(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::AnimationTextureIndexOverflow>
            bind_animation_texture_index_overflow
            = exceptions_namespace
                  .new_usertype<obe::animation::exceptions::AnimationTextureIndexOverflow>(
                      "AnimationTextureIndexOverflow", sol::call_constructor,
                      sol::constructors<obe::animation::exceptions::AnimationTextureIndexOverflow(
                          std::string_view, std::size_t, std::size_t, obe::DebugInfo)>(),
                      sol::base_classes,
                      sol::bases<
                          obe::Exception<obe::animation::exceptions::AnimationTextureIndexOverflow>,
                          obe::BaseException>());
    }
    void load_class_invalid_animation_file(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::InvalidAnimationFile> bind_invalid_animation_file
            = exceptions_namespace.new_usertype<obe::animation::exceptions::InvalidAnimationFile>(
                "InvalidAnimationFile", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::InvalidAnimationFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::InvalidAnimationFile>,
                    obe::BaseException>());
    }
    void load_class_invalid_easing_function(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::InvalidEasingFunction>
            bind_invalid_easing_function
            = exceptions_namespace.new_usertype<obe::animation::exceptions::InvalidEasingFunction>(
                "InvalidEasingFunction", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::InvalidEasingFunction(
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::InvalidEasingFunction>,
                    obe::BaseException>());
    }
    void load_class_no_selected_animation(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::NoSelectedAnimation> bind_no_selected_animation
            = exceptions_namespace.new_usertype<obe::animation::exceptions::NoSelectedAnimation>(
                "NoSelectedAnimation", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::NoSelectedAnimation(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::NoSelectedAnimation>,
                    obe::BaseException>());
    }
    void load_class_no_selected_animation_group(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::NoSelectedAnimationGroup>
            bind_no_selected_animation_group = exceptions_namespace.new_usertype<
                obe::animation::exceptions::NoSelectedAnimationGroup>("NoSelectedAnimationGroup",
                sol::call_constructor,
                sol::constructors<obe::animation::exceptions::NoSelectedAnimationGroup(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::NoSelectedAnimationGroup>,
                    obe::BaseException>());
    }
    void load_class_unknown_animation(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::UnknownAnimation> bind_unknown_animation
            = exceptions_namespace.new_usertype<obe::animation::exceptions::UnknownAnimation>(
                "UnknownAnimation", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::UnknownAnimation(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::UnknownAnimation>,
                    obe::BaseException>());
    }
    void load_class_unknown_animation_group(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::UnknownAnimationGroup>
            bind_unknown_animation_group
            = exceptions_namespace.new_usertype<obe::animation::exceptions::UnknownAnimationGroup>(
                "UnknownAnimationGroup", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::UnknownAnimationGroup(
                    std::string_view, std::string_view, const std::vector<std::string>&,
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::UnknownAnimationGroup>,
                    obe::BaseException>());
    }
    void load_class_unknown_easing_from_enum(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::UnknownEasingFromEnum>
            bind_unknown_easing_from_enum
            = exceptions_namespace.new_usertype<obe::animation::exceptions::UnknownEasingFromEnum>(
                "UnknownEasingFromEnum", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::UnknownEasingFromEnum(
                    int, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::UnknownEasingFromEnum>,
                    obe::BaseException>());
    }
    void load_class_unknown_easing_from_string(sol::state_view state)
    {
        sol::table exceptions_namespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::UnknownEasingFromString>
            bind_unknown_easing_from_string = exceptions_namespace.new_usertype<
                obe::animation::exceptions::UnknownEasingFromString>("UnknownEasingFromString",
                sol::call_constructor,
                sol::constructors<obe::animation::exceptions::UnknownEasingFromString(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::UnknownEasingFromString>,
                    obe::BaseException>());
    }
};