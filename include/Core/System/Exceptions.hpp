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
            this->error("Resource at path '{}' not found", path);
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

    class UnknownPackage : public Exception
    {
    public:
        UnknownPackage(std::string_view package,
            const std::vector<std::string>& allPackages, DebugInfo info)
            : Exception("UnknownPackage", info)
        {
            this->error(
                "Impossible to get Package '{}', please check it is correctly installed");
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(package.data(), allPackages, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Maybe you meant to get one of these packages : ({})",
                fmt::join(suggestions, ", "));
        }
    };

    class PackageFileNotFound : public Exception
    {
    public:
        PackageFileNotFound(std::string_view path, DebugInfo info)
            : Exception("PackageFileNotFound", info)
        {
            this->error(
                "Impossible to find a Package file at following path : '{}'", path);
        }
    };

    class PackageAlreadyInstalled : public Exception
    {
    public:
        PackageAlreadyInstalled(std::string_view package, DebugInfo info)
            : Exception("PackageAlreadyInstalled", info)
        {
            this->error("A Package named '{}' is already installed", package);
        }
    };

    class UnknownWorkspace : public Exception
    {
    public:
        UnknownWorkspace(std::string_view workspace,
            const std::vector<std::string>& allWorkspaces, DebugInfo info)
            : Exception("UnknownWorkspace", info)
        {
            this->error("Impossible to get Workspace '{}', please check it is correctly "
                        "indexed", workspace);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(workspace.data(), allWorkspaces, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Maybe you meant to get one of these workspaces : ({})",
                fmt::join(suggestions, ", "));
        }
    };
}
