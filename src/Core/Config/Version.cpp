#include <Config/Exceptions.hpp>
#include <Config/Version.hpp>

namespace obe::config
{
    Version::Version(const std::string& str)
    {
        std::vector<std::string> parts = utils::string::split(str, ".");
        if (parts.size() != 3)
        {
            throw exceptions::InvalidVersionFormat(
                "Wrong number of components for version string. Expecting version "
                "string of the form v?MAJOR.MINOR.PATCH");
        }
        // Skip first letter from version string ( 'v' )
        if (!utils::string::is_string_numeric(parts[0]) && parts[0].size() >= 2)
        {
            if (parts[0][0] != 'v')
            {
                throw exceptions::InvalidVersionFormat(
                    "Wrong prefix for version string, only \"v0.1.1\" is allowed.");
            }
            parts[0] = parts[0].substr(1);
        }

        major = std::stoi(parts[0]);
        minor = std::stoi(parts[1]);
        patch = std::stoi(parts[2]);
    }

    std::string Version::string() const
    {
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }
} // namespace obe::config
