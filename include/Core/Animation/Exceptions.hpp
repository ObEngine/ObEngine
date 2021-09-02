#pragma once

#include <Exception.hpp>

namespace obe::Animation::Exceptions
{
    class UnknownAnimationPlayMode : public Exception<UnknownAnimationPlayMode>
    {
    public:
        using Exception::Exception;
        UnknownAnimationPlayMode(std::string_view playMode, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Unable to convert the string '{}' to an AnimationPlayMode", playMode);
            this->hint("Try one of the following values : (OneTime, Loop, Force)");
        }
    };

    class UnknownAnimationGroup : public Exception<UnknownAnimationGroup>
    {
    public:
        using Exception::Exception;
        UnknownAnimationGroup(std::string_view animation, std::string_view groupName,
            const std::vector<std::string>& groups, DebugInfo info)
            : Exception(info)
        {
            this->error("Unable to retrieve AnimationGroup '{}' from Animation '{}'",
                animation, groupName);
            this->hint("Existing groups are ({})", fmt::join(groups, ", "));
        }
    };

    class AnimationTextureIndexOverflow : public Exception<AnimationTextureIndexOverflow>
    {
    public:
        using Exception::Exception;
        AnimationTextureIndexOverflow(std::string_view animation, std::size_t index,
            std::size_t maximum, DebugInfo info)
            : Exception(info)
        {
            this->error("Tried to access Texture of Animation '{}' at index {} when it "
                        "only contains {} textures",
                animation, index, maximum);
        }
    };

    class AnimationGroupTextureIndexOverflow : public Exception<AnimationGroupTextureIndexOverflow>
    {
    public:
        using Exception::Exception;
        AnimationGroupTextureIndexOverflow(std::string_view animationGroup,
            std::size_t index, std::size_t maximum, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Tried to access Texture of AnimationGroup '{}' at index {} when it "
                "only contains {} textures",
                animationGroup, index, maximum);
        }
    };

    class NoSelectedAnimationGroup : public Exception<NoSelectedAnimationGroup>
    {
    public:
        using Exception::Exception;
        NoSelectedAnimationGroup(std::string_view animation, DebugInfo info)
            : Exception(info)
        {
            this->error("The Animation '{}' does not have any AnimationGroup selected",
                animation);
        }
    };

    class UnknownAnimationCommand : public Exception <NoSelectedAnimationGroup>
    {
    public:
        using Exception::Exception;
        UnknownAnimationCommand(
            std::string_view animation, std::string_view command, DebugInfo info)
            : Exception(info)
        {
            this->error("Unknown command '{}' in code of Animation '{}'");
            this->hint(
                "Try one of the following valid commands (DELAY, PLAY_GROUP, CALL)");
        }
    };

    class UnknownAnimation : public Exception<UnknownAnimation>
    {
    public:
        using Exception::Exception;
        UnknownAnimation(std::string_view animatorPath, std::string_view animation,
            const std::vector<std::string>& animations, DebugInfo info)
            : Exception(info)
        {
            this->error("Animator '{}' doesn't have any Animation named '{}'",
                animatorPath, animation);
            this->hint(
                "Try one of the following animations ({})", fmt::join(animations, ", "));
        }
    };

    class NoSelectedAnimation : public Exception<NoSelectedAnimation>
    {
    public:
        using Exception::Exception;
        NoSelectedAnimation(std::string_view animator, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "The Animator '{}' does not have any Animation selected", animator);
        }
    };

    class UnknownEasingFromEnum : public Exception<UnknownEasingFromEnum>
    {
    public:
        using Exception::Exception;
        UnknownEasingFromEnum(int enumValue, DebugInfo info)
            : Exception(info)
        {
            this->error("Enum with value {} could not be converted to an easing function",
                enumValue);
        }
    };

    class UnknownEasingFromString : public Exception<UnknownEasingFromString>
    {
    public:
        using Exception::Exception;
        UnknownEasingFromString(std::string_view easingName, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to retrieve an Easing function with the following "
                        "name : '{}'",
                easingName);
        }
    };

    class UnknownTargetScaleMode : public Exception<UnknownTargetScaleMode>
    {
    public:
        using Exception::Exception;
        UnknownTargetScaleMode(std::string_view targetScaleMode, DebugInfo info)
            : Exception(info)
        {
            this->error("TargetScaleMode '{}' does not exists", targetScaleMode);
        }
    };

    class InvalidAnimationFile : public Exception<InvalidAnimationFile>
    {
    public:
        using Exception::Exception;
        InvalidAnimationFile(std::string_view path, DebugInfo info)
            : Exception(info)
        {
            this->error("Error occured while loading Animation file '{}'", path);
        }
    };
}
