#pragma once

#include <fmt/format.h>

#include <Exception.hpp>
#include <vector>

namespace obe::System::Exceptions
{
    class ResourceNotFound : public Exception<ResourceNotFound>
    {
    public:
        using Exception::Exception;
        ResourceNotFound(std::string_view path, std::string_view pathType,
            std::vector<std::string> mounts, DebugInfo info)
            : Exception(info)
        {
            this->error("{} at path '{}' not found", pathType, path);
            this->hint("The following paths were used to search for the resource : ({})",
                fmt::join(mounts, ", "));
        }
    };

    class InvalidMouseButtonEnumValue : public Exception<InvalidMouseButtonEnumValue>
    {
    public:
        using Exception::Exception;
        InvalidMouseButtonEnumValue(int enumValue, DebugInfo info)
            : Exception(info)
        {
            this->error("MouseButton enum should not have the following value : {}", enumValue);
        }
    };

    class MountFileMissing : public Exception<MountFileMissing>
    {
    public:
        using Exception::Exception;
        MountFileMissing(std::string_view currentPath, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Could not find mount.vili file in the execution directory : '{}'", currentPath);
        }
    };

    class InvalidMountFile : public Exception<InvalidMountFile>
    {
    public:
        using Exception::Exception;
        InvalidMountFile(std::string_view mountFilePath, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "An error occured while parsing 'mount.vili' file located at '{}'", mountFilePath);
        }
    };

    class MountablePathIndexOverflow : public Exception<MountablePathIndexOverflow>
    {
    public:
        using Exception::Exception;
        MountablePathIndexOverflow(std::size_t index, std::size_t maximum,
            const std::vector<std::string>& mounts, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to get MountablePath at index {} when there is only {} Paths",
                index, maximum);
            this->hint("Here is a list of available MountablePath ({})", fmt::join(mounts, ", "));
        }
    };

    class UnknownPackage : public Exception<UnknownPackage>
    {
    public:
        using Exception::Exception;
        UnknownPackage(
            std::string_view package, const std::vector<std::string>& allPackages, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to get Package '{}', please check it is correctly installed");
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(package.data(), allPackages, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), Utils::String::quote);
            this->hint("Maybe you meant to get one of these packages : ({})",
                fmt::join(suggestions, ", "));
        }
    };

    class PackageFileNotFound : public Exception<PackageFileNotFound>
    {
    public:
        using Exception::Exception;
        PackageFileNotFound(std::string_view path, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to find a Package file at following path : '{}'", path);
        }
    };

    class PackageAlreadyInstalled : public Exception<PackageAlreadyInstalled>
    {
    public:
        using Exception::Exception;
        PackageAlreadyInstalled(std::string_view package, DebugInfo info)
            : Exception(info)
        {
            this->error("A Package named '{}' is already installed", package);
        }
    };

    class UnknownProject : public Exception<UnknownProject>
    {
    public:
        using Exception::Exception;
        UnknownProject(
            std::string_view project, const std::vector<std::string>& allProjects, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to find Project '{}', please check it is correctly "
                        "indexed",
                project);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(project.data(), allProjects, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), Utils::String::quote);
            this->hint("Maybe you meant to get one of these projects : ({})",
                fmt::join(suggestions, ", "));
        }
    };

    class UnknownStretchMode : public Exception<UnknownStretchMode>
    {
    public:
        using Exception::Exception;
        UnknownStretchMode(std::string_view stretchMode, DebugInfo info)
            : Exception(info)
        {
            this->error("Stretch mode '{}' does not exist", stretchMode);
            this->hint("Maybe you meant to get one of these modes : (None, Center, Fit, "
                       "Stretch, KeepWidth, KeepHeight)");
        }
    };

    class UnknownPathPrefix : public Exception<UnknownPathPrefix>
    {
    public:
        using Exception::Exception;
        UnknownPathPrefix(
            std::string_view prefix, const std::vector<std::string> allPrefixes, DebugInfo info)
            : Exception(info)
        {
            this->error("Path prefix '{}' does not exist", prefix);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(prefix.data(), allPrefixes, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), Utils::String::quote);
            this->hint("Maybe you meant to use one of these prefixes : ({})",
                fmt::join(suggestions, ", "));
        }
    };

    class MissingDefaultMountPoint : public Exception<MissingDefaultMountPoint>
    {
    public:
        using Exception::Exception;
        explicit MissingDefaultMountPoint(DebugInfo info)
            : Exception(info)
        {
            this->error("Must at least choose cwd or executable path as default mount point");
        }
    };

    class PathError : public Exception<PathError>
    {
    public:
        using Exception::Exception;
        PathError(std::string_view prefix, std::string_view path, DebugInfo info)
            : Exception(info)
        {
            this->error("An error occured while loading path '{}://{}'", prefix, path);
        }
    };

    class InvalidProjectFile : public Exception<InvalidProjectFile>
    {
    public:
        using Exception::Exception;
        InvalidProjectFile(std::string_view projectFilePath, DebugInfo info)
            : Exception(info)
        {
            this->error("An error occured while parsing 'project.vili' file located at '{}'",
                projectFilePath);
        }
    };
}
