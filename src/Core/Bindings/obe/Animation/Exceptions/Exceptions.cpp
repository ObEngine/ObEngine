#include <Bindings/obe/Animation/Exceptions/Exceptions.hpp>

#include <Animation/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Animation::Exceptions::Bindings
{
    void LoadClassAnimationGroupTextureIndexOverflow(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::AnimationGroupTextureIndexOverflow>
            bindAnimationGroupTextureIndexOverflow = ExceptionsNamespace.new_usertype<
                obe::Animation::Exceptions::AnimationGroupTextureIndexOverflow>(
                "AnimationGroupTextureIndexOverflow", sol::call_constructor,
                sol::constructors<
                    obe::Animation::Exceptions::AnimationGroupTextureIndexOverflow(
                        std::string_view, std::size_t, std::size_t, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassAnimationTextureIndexOverflow(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::AnimationTextureIndexOverflow>
            bindAnimationTextureIndexOverflow = ExceptionsNamespace.new_usertype<
                obe::Animation::Exceptions::AnimationTextureIndexOverflow>(
                "AnimationTextureIndexOverflow", sol::call_constructor,
                sol::constructors<
                    obe::Animation::Exceptions::AnimationTextureIndexOverflow(
                        std::string_view, std::size_t, std::size_t, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassNoSelectedAnimation(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::NoSelectedAnimation>
            bindNoSelectedAnimation
            = ExceptionsNamespace
                  .new_usertype<obe::Animation::Exceptions::NoSelectedAnimation>(
                      "NoSelectedAnimation", sol::call_constructor,
                      sol::constructors<obe::Animation::Exceptions::NoSelectedAnimation(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassNoSelectedAnimationGroup(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::NoSelectedAnimationGroup>
            bindNoSelectedAnimationGroup = ExceptionsNamespace.new_usertype<
                obe::Animation::Exceptions::NoSelectedAnimationGroup>(
                "NoSelectedAnimationGroup", sol::call_constructor,
                sol::constructors<obe::Animation::Exceptions::NoSelectedAnimationGroup(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownAnimation(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::UnknownAnimation> bindUnknownAnimation
            = ExceptionsNamespace
                  .new_usertype<obe::Animation::Exceptions::UnknownAnimation>(
                      "UnknownAnimation", sol::call_constructor,
                      sol::constructors<obe::Animation::Exceptions::UnknownAnimation(
                          std::string_view, std::string_view,
                          const std::vector<std::string>&, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownAnimationCommand(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::UnknownAnimationCommand>
            bindUnknownAnimationCommand = ExceptionsNamespace.new_usertype<
                obe::Animation::Exceptions::UnknownAnimationCommand>(
                "UnknownAnimationCommand", sol::call_constructor,
                sol::constructors<obe::Animation::Exceptions::UnknownAnimationCommand(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownAnimationGroup(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::UnknownAnimationGroup>
            bindUnknownAnimationGroup
            = ExceptionsNamespace
                  .new_usertype<obe::Animation::Exceptions::UnknownAnimationGroup>(
                      "UnknownAnimationGroup", sol::call_constructor,
                      sol::constructors<obe::Animation::Exceptions::UnknownAnimationGroup(
                          std::string_view, std::string_view,
                          const std::vector<std::string>&, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownAnimationPlayMode(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::UnknownAnimationPlayMode>
            bindUnknownAnimationPlayMode = ExceptionsNamespace.new_usertype<
                obe::Animation::Exceptions::UnknownAnimationPlayMode>(
                "UnknownAnimationPlayMode", sol::call_constructor,
                sol::constructors<obe::Animation::Exceptions::UnknownAnimationPlayMode(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownEasingFromEnum(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::UnknownEasingFromEnum>
            bindUnknownEasingFromEnum
            = ExceptionsNamespace
                  .new_usertype<obe::Animation::Exceptions::UnknownEasingFromEnum>(
                      "UnknownEasingFromEnum", sol::call_constructor,
                      sol::constructors<obe::Animation::Exceptions::UnknownEasingFromEnum(
                          int, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownEasingFromString(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Animation"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Animation::Exceptions::UnknownEasingFromString>
            bindUnknownEasingFromString = ExceptionsNamespace.new_usertype<
                obe::Animation::Exceptions::UnknownEasingFromString>(
                "UnknownEasingFromString", sol::call_constructor,
                sol::constructors<obe::Animation::Exceptions::UnknownEasingFromString(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};