#pragma once

#include <fmt/format.h>
#include <string_view>

#include <Animation/Animation.hpp>
#include <Exception.hpp>

namespace obe::Animation::Exceptions
{
    class UnknownAnimationPlayMode : public Exception
    {
    public:
        UnknownAnimationPlayMode(std::string_view playMode)
            : Exception("UnknownAnimationPlayMode")
        {
            this->error(
                "Unable to convert the string '{}' to an AnimationPlayMode", playMode);
            this->hint("Try one of the following values : (OneTime, Loop, Force)");
        }
    };

    class UnknownAnimationGroup : public Exception
    {
    public:
        UnknownAnimationGroup(std::string_view animation, std::string_view groupName,
            const std::vector<std::string>& groups)
            : Exception("UnknownAnimationGroup")
        {
            this->error("Unable to retrieve AnimationGroup '{}' from Animation '{}'",
                animation, groupName);
            this->hint("Existing groups are ({})", fmt::join(groups, ", "));
        }
    };

    class AnimationTextureIndexOverflow : public Exception
    {
    public:
        AnimationTextureIndexOverflow(
            std::string_view animation, unsigned int index, unsigned int maximum)
            : Exception("AnimationTextureIndexOverflow")
        {
            this->error("Tried to access Texture of Animation '{}' at index {} when it "
                        "only contains {} textures",
                animation, index, maximum);
        }
    };

    class NoSelectedAnimationGroup : public Exception
    {
    public:
        NoSelectedAnimationGroup(std::string_view animation)
            : Exception("NoSelectedAnimationGroup")
        {
            this->error("The Animation '{}' does not have any AnimationGroup selected",
                animation);
        }
    };
}
