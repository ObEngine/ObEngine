#include <Bindings/obe/Animation/Exceptions/Exceptions.hpp>

#include <Animation/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::animation::exceptions::Bindings
{
    void LoadClassAnimationGroupTextureIndexOverflow(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::AnimationGroupTextureIndexOverflow>
            bindAnimationGroupTextureIndexOverflow = ExceptionsNamespace.new_usertype<
                obe::animation::exceptions::AnimationGroupTextureIndexOverflow>(
                "AnimationGroupTextureIndexOverflow", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::AnimationGroupTextureIndexOverflow(
                    std::string_view, std::size_t, std::size_t, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<
                    obe::Exception<obe::animation::exceptions::AnimationGroupTextureIndexOverflow>,
                    obe::BaseException>());
    }
    void LoadClassAnimationTextureIndexOverflow(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::AnimationTextureIndexOverflow>
            bindAnimationTextureIndexOverflow
            = ExceptionsNamespace
                  .new_usertype<obe::animation::exceptions::AnimationTextureIndexOverflow>(
                      "AnimationTextureIndexOverflow", sol::call_constructor,
                      sol::constructors<obe::animation::exceptions::AnimationTextureIndexOverflow(
                          std::string_view, std::size_t, std::size_t, obe::DebugInfo)>(),
                      sol::base_classes,
                      sol::bases<
                          obe::Exception<obe::animation::exceptions::AnimationTextureIndexOverflow>,
                          obe::BaseException>());
    }
    void LoadClassInvalidAnimationFile(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::InvalidAnimationFile> bindInvalidAnimationFile
            = ExceptionsNamespace.new_usertype<obe::animation::exceptions::InvalidAnimationFile>(
                "InvalidAnimationFile", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::InvalidAnimationFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::InvalidAnimationFile>,
                    obe::BaseException>());
    }
    void LoadClassNoSelectedAnimation(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::NoSelectedAnimation> bindNoSelectedAnimation
            = ExceptionsNamespace.new_usertype<obe::animation::exceptions::NoSelectedAnimation>(
                "NoSelectedAnimation", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::NoSelectedAnimation(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::NoSelectedAnimation>,
                    obe::BaseException>());
    }
    void LoadClassNoSelectedAnimationGroup(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::NoSelectedAnimationGroup>
            bindNoSelectedAnimationGroup = ExceptionsNamespace.new_usertype<
                obe::animation::exceptions::NoSelectedAnimationGroup>("NoSelectedAnimationGroup",
                sol::call_constructor,
                sol::constructors<obe::animation::exceptions::NoSelectedAnimationGroup(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::NoSelectedAnimationGroup>,
                    obe::BaseException>());
    }
    void LoadClassUnknownAnimation(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::UnknownAnimation> bindUnknownAnimation
            = ExceptionsNamespace.new_usertype<obe::animation::exceptions::UnknownAnimation>(
                "UnknownAnimation", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::UnknownAnimation(std::string_view,
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::UnknownAnimation>,
                    obe::BaseException>());
    }
    void LoadClassUnknownAnimationGroup(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::UnknownAnimationGroup> bindUnknownAnimationGroup
            = ExceptionsNamespace.new_usertype<obe::animation::exceptions::UnknownAnimationGroup>(
                "UnknownAnimationGroup", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::UnknownAnimationGroup(
                    std::string_view, std::string_view, const std::vector<std::string>&,
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::UnknownAnimationGroup>,
                    obe::BaseException>());
    }
    void LoadClassUnknownEasingFromEnum(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::UnknownEasingFromEnum> bindUnknownEasingFromEnum
            = ExceptionsNamespace.new_usertype<obe::animation::exceptions::UnknownEasingFromEnum>(
                "UnknownEasingFromEnum", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::UnknownEasingFromEnum(
                    int, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::UnknownEasingFromEnum>,
                    obe::BaseException>());
    }
    void LoadClassUnknownEasingFromString(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["animation"]["exceptions"].get<sol::table>();
        sol::usertype<obe::animation::exceptions::UnknownEasingFromString>
            bindUnknownEasingFromString
            = ExceptionsNamespace.new_usertype<obe::animation::exceptions::UnknownEasingFromString>(
                "UnknownEasingFromString", sol::call_constructor,
                sol::constructors<obe::animation::exceptions::UnknownEasingFromString(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::animation::exceptions::UnknownEasingFromString>,
                    obe::BaseException>());
    }
};