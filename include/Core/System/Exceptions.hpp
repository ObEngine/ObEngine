#pragma once

#include <Exception.hpp>
#include <vector>

namespace obe::System::Exceptions
{
    class ResourceNotFound : public Exception
    {
    public:
        ResourceNotFound(
            std::string_view path, std::vector<std::string> mounts, DebugInfo info)
            : Exception("ResourceNotFound", info)
        {
            this->error("Resource at path '{}' not found");
            this->hint("The following paths were used to search for the resource : ({})",
                fmt::join(mounts, ", "));
        }
    };

    class InvalidMouseButtonEnumValue : public Exception
    {
    public:
        InvalidMouseButtonEnumValue(int enumValue, DebugInfo info)
            : Exception("InvalidMouseButtonEnumValue", info)
        {
            this->error(
                "MouseButton enum should not have the following value : {}", enumValue);
        }
    };

    class MountFileMissing : public Exception
    {
    public:
        MountFileMissing(std::string_view currentPath, DebugInfo info)
            : Exception("MountFileMissing", info)
        {
            this->error(
                "Could not find Mount.vili file in the execution directory : '{}'",
                currentPath);
        }
    };

    class MountablePathIndexOverflow : public Exception
    {
    public:
        MountablePathIndexOverflow(std::size_t index, std::size_t maximum,
            const std::vector<std::string>& mounts, DebugInfo info)
            : Exception("PathIndexOverflow", info)
        {
            this->error(
                "Impossible to get MountablePath at index {} when there is only {} Paths",
                index, maximum);
            this->hint("Here is a list of available MountablePath ({})",
                fmt::join(mounts, ", "));
        }
    };
}
