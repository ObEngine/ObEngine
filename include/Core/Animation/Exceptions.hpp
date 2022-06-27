#pragma once

#include <Exception.hpp>

/**
 * \nobind
 */
namespace obe::animation::exceptions
{
    class UnknownAnimationGroup : public Exception<UnknownAnimationGroup>
    {
    public:
        using Exception::Exception;
        UnknownAnimationGroup(std::string_view animation, std::string_view group_name,
            const std::vector<std::string>& groups, DebugInfo info)
            : Exception(info)
        {
            this->error("Unable to retrieve AnimationGroup '{}' from animation '{}'", animation,
                group_name);
            this->hint("Existing groups are ({})", fmt::join(groups, ", "));
        }
    };

    class AnimationTextureIndexOverflow : public Exception<AnimationTextureIndexOverflow>
    {
    public:
        using Exception::Exception;
        AnimationTextureIndexOverflow(
            std::string_view animation, std::size_t index, std::size_t maximum, DebugInfo info)
            : Exception(info)
        {
            this->error("Tried to access Texture of animation '{}' at index {} when it "
                        "only contains {} textures",
                animation, index, maximum);
        }
    };

    class AnimationGroupTextureIndexOverflow : public Exception<AnimationGroupTextureIndexOverflow>
    {
    public:
        using Exception::Exception;
        AnimationGroupTextureIndexOverflow(
            std::string_view group_name, std::size_t index, std::size_t maximum, DebugInfo info)
            : Exception(info)
        {
            this->error("Tried to access Texture of AnimationGroup '{}' at index {} when it "
                        "only contains {} textures",
                group_name, index, maximum);
        }
    };

    class NoSelectedAnimationGroup : public Exception<NoSelectedAnimationGroup>
    {
    public:
        using Exception::Exception;
        NoSelectedAnimationGroup(std::string_view animation, DebugInfo info)
            : Exception(info)
        {
            this->error("The animation '{}' does not have any AnimationGroup selected", animation);
        }
    };

    class UnknownAnimation : public Exception<UnknownAnimation>
    {
    public:
        using Exception::Exception;
        UnknownAnimation(std::string_view animator_path, std::string_view animation,
            const std::vector<std::string>& animations, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Animator '{}' doesn't have any animation named '{}'", animator_path, animation);
            this->hint("Try one of the following animations ({})", fmt::join(animations, ", "));
        }
    };

    class NoSelectedAnimation : public Exception<NoSelectedAnimation>
    {
    public:
        using Exception::Exception;
        NoSelectedAnimation(std::string_view animator, DebugInfo info)
            : Exception(info)
        {
            this->error("The Animator '{}' does not have any animation selected", animator);
        }
    };

    class UnknownEasingFromEnum : public Exception<UnknownEasingFromEnum>
    {
    public:
        using Exception::Exception;
        UnknownEasingFromEnum(int enum_value, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Enum with value {} could not be converted to an easing function", enum_value);
        }
    };

    class UnknownEasingFromString : public Exception<UnknownEasingFromString>
    {
    public:
        using Exception::Exception;
        UnknownEasingFromString(std::string_view easing_name,
            const std::vector<std::string>& all_easings, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to retrieve an Easing function with the following "
                        "name : '{}'",
                easing_name);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(easing_name.data(), all_easings, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), utils::string::quote);
            suggestions.emplace_back("...");
            this->hint("Try one of the Easings with name ({})", fmt::join(suggestions, ", "));
        }
    };

    class InvalidAnimationFile : public Exception<InvalidAnimationFile>
    {
    public:
        using Exception::Exception;
        InvalidAnimationFile(std::string_view path, DebugInfo info)
            : Exception(info)
        {
            this->error("Error occured while loading animation file '{}'", path);
        }
    };

    class InvalidEasingFunction : public Exception<InvalidEasingFunction>
    {
    public:
        using Exception::Exception;
        InvalidEasingFunction(DebugInfo info)
            : Exception(info)
        {
            this->error("Invalid easing function");
        }
    };
}
