#pragma once

#include <string>

namespace obe::config
{
    class Version
    {
    public:
        int major = 0;
        int minor = 0;
        int patch = 0;

        constexpr Version(int version_major, int version_minor, int version_patch)
            : major(version_major)
            , minor(version_minor)
            , patch(version_patch) {};
        Version(const std::string& str);
        [[nodiscard]] std::string string() const;
    };

    inline constexpr bool operator==(const Version& lhs, const Version& rhs)
    {
        return (lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch == rhs.patch);
    }

    inline constexpr bool operator!=(const Version& lhs, const Version& rhs)
    {
        return !(lhs == rhs);
    }

    inline constexpr bool operator<(const Version& lhs, const Version& rhs)
    {
        if (lhs.major < rhs.major)
            return true;
        if (lhs.major > rhs.major)
            return false;
        if (lhs.minor < rhs.minor)
            return true;
        if (lhs.minor > rhs.minor)
            return false;
        return (lhs.patch < rhs.patch);
    }

    inline constexpr bool operator<=(const Version& lhs, const Version& rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }

    inline constexpr bool operator>(const Version& lhs, const Version& rhs)
    {
        return rhs < lhs;
    }

    inline constexpr bool operator>=(const Version& lhs, const Version& rhs)
    {
        return (lhs > rhs) || (lhs == rhs);
    }
} // namespace obe::config
