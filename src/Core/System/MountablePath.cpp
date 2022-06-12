#include <string>

#include <platformfolders/platform_folders.h>
#include <vili/parser.hpp>
#include <vld8/validator.hpp>

#include <Config/Validators.hpp>
#include <Debug/Logger.hpp>
#include <System/MountablePath.hpp>
#include <System/Package.hpp>
#include <System/Path.hpp>
#include <System/Project.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::System
{
    MountList MountablePath::MountedPaths;

    MountablePath::MountablePath(MountablePathType pathType, std::string_view basePath,
        std::string_view prefix, unsigned int priority, bool implicit, bool deferResolution)
        : pathType(pathType)
        , basePath(basePath)
        , prefix(prefix)
        , priority(priority)
        , implicit(implicit)
        , deferredResolution(deferResolution)
    {
        if (!deferredResolution)
        {
            this->resolveBasePath();
        }
    }

    bool MountablePath::operator==(const MountablePath& other) const
    {
        return (this->basePath == other.basePath && this->priority == other.priority
            && this->pathType == other.pathType && this->prefix == other.prefix);
    }

    void MountablePath::LoadMountFile(bool fromCWD, bool fromExe)
    {
        MountablePath::UnmountAll();

        if (!fromCWD && !fromExe)
        {
            throw Exceptions::MissingDefaultMountPoint(EXC_INFO);
        }

        MountablePath rootPath(MountablePathType::Path, "", Prefixes::root, Priorities::defaults);
        MountablePath workingDirectoryPath(
            MountablePathType::Path, ".", Prefixes::cwd, Priorities::defaults);
        MountablePath implicitCWDPath(MountablePathType::Path, ".", "", Priorities::defaults, true);
        MountablePath implicitRootPath(MountablePathType::Path, "", "", Priorities::defaults, true); 
        MountablePath executablePath(MountablePathType::Path, Utils::File::getExecutableDirectory(),
            Prefixes::exe, Priorities::defaults);

        const std::string engineConfigPath
            = Utils::File::join({ sago::getConfigHome(), "ObEngine" });
        if (!Utils::File::directoryExists(engineConfigPath))
        {
            Utils::File::createDirectory(engineConfigPath);
        }
        const std::string engineConfigProjectSubdirectory
            = Utils::File::join({ engineConfigPath, "Projects" });
        if (!Utils::File::directoryExists(engineConfigProjectSubdirectory))
        {
            Utils::File::createDirectory(engineConfigProjectSubdirectory);
        }

        MountablePath configPath(
            MountablePathType::Path, engineConfigPath, Prefixes::cfg, Priorities::defaults);
        MountablePath::Mount(rootPath);
        MountablePath::Mount(workingDirectoryPath);
        MountablePath::Mount(implicitCWDPath);
        MountablePath::Mount(implicitRootPath);
        MountablePath::Mount(executablePath);
        MountablePath::Mount(configPath);

        MountablePath basePath(MountablePathType::Path, "", Prefixes::mount, Priorities::defaults);
        if (fromCWD)
        {
            basePath.basePath = workingDirectoryPath.basePath;
        }
        else
        {
            basePath.basePath = executablePath.basePath;
        }
        MountablePath::Mount(basePath);

        MountablePath enginePath(
            MountablePathType::Path, executablePath.basePath, Prefixes::obe, Priorities::defaults);
        MountablePath::Mount(enginePath);

        FindResult mountFilePath
            = Path(Prefixes::mount, "mount.vili").find(obe::System::PathType::File);
        if (!mountFilePath)
        {
            auto stringPaths = MountablePath::StringPaths();
            std::transform(
                stringPaths.begin(), stringPaths.end(), stringPaths.begin(), Utils::String::quote);

            debug::Log->info("No 'mount.vili' file found in the following directories ({})",
                fmt::join(stringPaths.begin(), stringPaths.end(), ", "));
            return;
        }

        debug::Log->debug("Found 'mount.vili' file in '{}' (prefix: '{}')", mountFilePath.path(),
            mountFilePath.mount().prefix);

        vili::node mountedPaths;
        try
        {
            mountedPaths
                = vili::parser::from_file(mountFilePath);
        }
        catch (const vili::exceptions::file_not_found& e)
        {
            debug::Log->critical("<MountablePath> Unable to find 'mount.vili' : \n{}", e.what());
            throw Exceptions::MountFileMissing(Utils::File::getCurrentDirectory(), EXC_INFO);
        }
        catch (const std::exception& e)
        {
            debug::Log->critical("<MountablePath> Unable to load 'mount.vili' : \n{}", e.what());
            throw Exceptions::InvalidMountFile(mountFilePath.path(), EXC_INFO).nest(e);
        }
        vili::validator::validate_tree(config::validators::mount_validator(), mountedPaths);
        if (mountedPaths.contains("mounts"))
        {
            for (auto [mountName, mount] : mountedPaths.at("mounts").items())
            {
                if (mount.is_string())
                {
                    MountablePath::Mount(MountablePath(
                        MountablePathType::Path, mount, mountName, Priorities::mount));
                    debug::Log->info("<MountablePath> Mounted Path : '{0}' at '{1}://' "
                                     "with priority {2}",
                        mount, mountName, 0);
                }
                else if (mount.is_object())
                {
                    std::string currentType = "Path";
                    if (mount.contains("type"))
                    {
                        currentType = mount.at("type");
                    }
                    const std::string currentPath = mount.at("path");
                    std::string prefix = mountName;
                    if (mount.contains("prefix"))
                    {
                        prefix = mount.at("prefix");
                    }
                    int currentPriority = Priorities::mount;
                    if (mount.contains("priority"))
                    {
                        currentPriority = mount.at("priority");
                    }
                    bool implicit = false;
                    if (mount.contains("implicit"))
                    {
                        implicit = mount.at("implicit");
                    }
                    if (currentType == "Path")
                    {
                        MountablePath::Mount(MountablePath(MountablePathType::Path, currentPath,
                            prefix, currentPriority, implicit));
                        debug::Log->info("<MountablePath> Mounted Path : '{0}' at '{1}://' "
                                         "with priority {2}",
                            currentPath, prefix, currentPriority);
                    }
                    else if (currentType == "Package")
                    {
                        Package::Load(currentPath, prefix, currentPriority);
                        debug::Log->info("<MountablePath> Mounted Package : '{0}' at '{1}://' "
                                         "with priority {2}",
                            currentPath, prefix, currentPriority);
                    }
                    else if (currentType == "Project")
                    {
                        Project::Load(currentPath, prefix, currentPriority);
                        debug::Log->info("<MountablePath> Mounted Project : '{0}' at '{1}://' "
                                         "with priority {2}",
                            currentPath, prefix, currentPriority);
                    }
                }
            }
        }
        if (mountedPaths.contains("project"))
        {
            Project::Load(mountedPaths.at("project"), Prefixes::game.data(), Priorities::project);
        }
        debug::Log->info("<MountablePath> List of mounted paths : ");
        for (const auto& currentPath : MountablePath::MountedPaths)
        {
            debug::Log->info("<MountablePath> MountedPath : '{}' with prefix '{}'",
                currentPath->basePath, currentPath->prefix);
        }

        // If obe prefix has been redefined, extlibs will change accordingly
        std::string obePath = MountablePath::FromPrefix(Prefixes::obe.data()).basePath;
        MountablePath extlibsPath(MountablePathType::Path, obePath + "/Lib/Extlibs",
            Prefixes::extlibs, Priorities::defaults, false);
        MountablePath::Mount(extlibsPath);
    }

    void MountablePath::Mount(const MountablePath path, SamePrefixPolicy samePrefixPolicy)
    {
        if (path.deferredResolution)
        {
            throw Exceptions::InvalidDeferredMountablePath(path.prefix, EXC_INFO);
        }
        auto pathCmp = [&path](const auto& mountedPath) { return path == *mountedPath; };
        bool pathAlreadyExists
            = std::find_if(MountedPaths.begin(), MountedPaths.end(), pathCmp) != MountedPaths.end();
        if (pathAlreadyExists)
        {
            debug::Log->warn("[MountablePath] Can't Mount the same path twice: "
                             "MountablePath(prefix={}, path={}, priority={}, implicit={})",
                path.prefix, path.basePath, path.priority, path.implicit);
            return;
        }
        if (samePrefixPolicy == SamePrefixPolicy::Replace)
        {
            MountedPaths.erase(std::remove_if(MountedPaths.begin(), MountedPaths.end(),
                                   [path](const auto& mountablePath)
                                   { return mountablePath->prefix == path.prefix; }),
                MountedPaths.end());
            MountedPaths.push_back(std::make_shared<MountablePath>(path));
        }
        if (samePrefixPolicy != SamePrefixPolicy::Skip)
        {
            MountedPaths.push_back(std::make_shared<MountablePath>(path));
        }
        else
        {
            const auto existingPrefixIt = std::find_if(MountedPaths.begin(), MountedPaths.end(),
                [path](const auto& mountablePath) { return mountablePath->prefix == path.prefix; });
            if (existingPrefixIt == MountedPaths.end())
            {
                MountedPaths.push_back(std::make_shared<MountablePath>(path));
            }
        }
        Sort();
    }

    void MountablePath::Unmount(const MountablePath path)
    {
        MountedPaths.erase(
            std::remove_if(MountedPaths.begin(), MountedPaths.end(),
                [path](const auto& mountablePath) { return *mountablePath == path; }),
            MountedPaths.end());
    }

    void MountablePath::UnmountAll()
    {
        MountedPaths.clear();
    }

    const MountList& MountablePath::Paths()
    {
        return MountedPaths;
    }

    std::vector<std::string> MountablePath::StringPaths()
    {
        std::vector<std::string> mountedPaths;
        mountedPaths.reserve(MountedPaths.size());
        for (auto& mountedPath : MountedPaths)
        {
            mountedPaths.push_back(mountedPath->basePath);
        }
        return mountedPaths;
    }

    void MountablePath::Sort()
    {
        std::sort(MountedPaths.begin(), MountedPaths.end(),
            [](const auto& first, const auto& second)
            { return first->priority > second->priority; });
    }

    const MountablePath& MountablePath::FromPrefix(const std::string& prefix)
    {
        for (const auto& mount : MountedPaths)
        {
            if (mount->prefix == prefix)
            {
                return *mount;
            }
        }
        throw Exceptions::UnknownPathPrefix(prefix, GetAllPrefixes(), EXC_INFO);
    }

    const std::vector<std::string> MountablePath::GetAllPrefixes()
    {
        MountList mounts = MountedPaths;
        std::vector<std::string> allPrefixes;
        allPrefixes.reserve(mounts.size());
        std::transform(mounts.begin(), mounts.end(), std::back_inserter(allPrefixes),
            [](const auto& mount) { return mount->prefix; });
        return allPrefixes;
    }

    void MountablePath::resolveBasePath()
    {
        auto [_, prefixInPath] = splitPathAndPrefix(basePath, false);
        if (!prefixInPath.empty())
        {
            basePath = System::Path(basePath).find(PathType::Directory).path();
        }
        basePath = Utils::File::canonicalPath(basePath);
        deferredResolution = false;
    }
} // namespace obe::System
