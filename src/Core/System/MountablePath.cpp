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

namespace obe::system
{
    MountList MountablePath::MountedPaths;

    MountablePath::MountablePath(MountablePathType path_type, std::string_view base_path,
        std::string_view prefix, unsigned int priority, bool implicit, bool defer_resolution)
        : path_type(path_type)
        , base_path(base_path)
        , prefix(prefix)
        , priority(priority)
        , implicit(implicit)
        , deferred_resolution(defer_resolution)
    {
        if (!deferred_resolution)
        {
            this->resolve_base_path();
        }
    }

    bool MountablePath::operator==(const MountablePath& other) const
    {
        return (this->base_path == other.base_path && this->priority == other.priority
            && this->path_type == other.path_type && this->prefix == other.prefix);
    }

    void MountablePath::load_mount_file(bool from_cwd, bool from_exe)
    {
        MountablePath::unmount_all();

        if (!from_cwd && !from_exe)
        {
            throw Exceptions::MissingDefaultMountPoint(EXC_INFO);
        }

        MountablePath root_path(MountablePathType::Path, "", prefixes::root, priorities::defaults);
        MountablePath working_directory_path(
            MountablePathType::Path, ".", prefixes::cwd, priorities::defaults);
        MountablePath implicit_cwd_path(MountablePathType::Path, ".", "", priorities::defaults, true);
        MountablePath implicit_root_path(MountablePathType::Path, "", "", priorities::defaults, true); 
        MountablePath executable_path(MountablePathType::Path, utils::file::get_executable_directory(),
            prefixes::exe, priorities::defaults);

        const std::string engine_config_path
            = utils::file::join({ sago::getConfigHome(), "ObEngine" });
        if (!utils::file::directory_exists(engine_config_path))
        {
            utils::file::create_directory(engine_config_path);
        }
        const std::string engine_config_project_subdirectory
            = utils::file::join({ engine_config_path, "Projects" });
        if (!utils::file::directory_exists(engine_config_project_subdirectory))
        {
            utils::file::create_directory(engine_config_project_subdirectory);
        }

        MountablePath config_path(
            MountablePathType::Path, engine_config_path, prefixes::cfg, priorities::defaults);
        MountablePath::mount(root_path);
        MountablePath::mount(working_directory_path);
        MountablePath::mount(implicit_cwd_path);
        MountablePath::mount(implicit_root_path);
        MountablePath::mount(executable_path);
        MountablePath::mount(config_path);

        MountablePath base_path(MountablePathType::Path, "", prefixes::mount, priorities::defaults);
        if (from_cwd)
        {
            base_path.base_path = working_directory_path.base_path;
        }
        else
        {
            base_path.base_path = executable_path.base_path;
        }
        MountablePath::mount(base_path);

        MountablePath engine_path(
            MountablePathType::Path, executable_path.base_path, prefixes::obe, priorities::defaults);
        MountablePath::mount(engine_path);

        FindResult mount_file_path
            = Path(prefixes::mount, "mount.vili").find(obe::system::PathType::File);
        if (!mount_file_path)
        {
            auto string_paths = MountablePath::string_paths();
            std::transform(
                string_paths.begin(), string_paths.end(), string_paths.begin(), utils::string::quote);

            debug::Log->info("No 'mount.vili' file found in the following directories ({})",
                fmt::join(string_paths.begin(), string_paths.end(), ", "));
            return;
        }

        debug::Log->debug("Found 'mount.vili' file in '{}' (prefix: '{}')", mount_file_path.path(),
            mount_file_path.mount().prefix);

        vili::node mounted_paths;
        try
        {
            mounted_paths
                = vili::parser::from_file(mount_file_path);
        }
        catch (const vili::exceptions::file_not_found& e)
        {
            debug::Log->critical("<MountablePath> Unable to find 'mount.vili' : \n{}", e.what());
            throw Exceptions::MountFileMissing(utils::file::get_current_directory(), EXC_INFO);
        }
        catch (const std::exception& e)
        {
            debug::Log->critical("<MountablePath> Unable to load 'mount.vili' : \n{}", e.what());
            throw Exceptions::InvalidMountFile(mount_file_path.path(), EXC_INFO).nest(e);
        }
        vili::validator::validate_tree(config::validators::mount_validator(), mounted_paths);
        if (mounted_paths.contains("mounts"))
        {
            for (auto [mount_name, mount] : mounted_paths.at("mounts").items())
            {
                if (mount.is_string())
                {
                    MountablePath::mount(MountablePath(
                        MountablePathType::Path, mount, mount_name, priorities::mount));
                    debug::Log->info("<MountablePath> Mounted Path : '{0}' at '{1}://' "
                                     "with priority {2}",
                        mount, mount_name, 0);
                }
                else if (mount.is_object())
                {
                    std::string current_type = "Path";
                    if (mount.contains("type"))
                    {
                        current_type = mount.at("type");
                    }
                    const std::string current_path = mount.at("path");
                    std::string prefix = mount_name;
                    if (mount.contains("prefix"))
                    {
                        prefix = mount.at("prefix");
                    }
                    int current_priority = priorities::mount;
                    if (mount.contains("priority"))
                    {
                        current_priority = mount.at("priority");
                    }
                    bool implicit = false;
                    if (mount.contains("implicit"))
                    {
                        implicit = mount.at("implicit");
                    }
                    if (current_type == "Path")
                    {
                        MountablePath::mount(MountablePath(MountablePathType::Path, current_path,
                            prefix, current_priority, implicit));
                        debug::Log->info("<MountablePath> Mounted Path : '{0}' at '{1}://' "
                                         "with priority {2}",
                            current_path, prefix, current_priority);
                    }
                    else if (current_type == "Package")
                    {
                        package::load(current_path, prefix, current_priority);
                        debug::Log->info("<MountablePath> Mounted Package : '{0}' at '{1}://' "
                                         "with priority {2}",
                            current_path, prefix, current_priority);
                    }
                    else if (current_type == "Project")
                    {
                        project::load(current_path, prefix, current_priority);
                        debug::Log->info("<MountablePath> Mounted Project : '{0}' at '{1}://' "
                                         "with priority {2}",
                            current_path, prefix, current_priority);
                    }
                }
            }
        }
        if (mounted_paths.contains("project"))
        {
            project::load(mounted_paths.at("project"), prefixes::game.data(), priorities::project);
        }
        debug::Log->info("<MountablePath> List of mounted paths : ");
        for (const auto& current_path : MountablePath::MountedPaths)
        {
            debug::Log->info("<MountablePath> MountedPath : '{}' with prefix '{}'",
                current_path->base_path, current_path->prefix);
        }

        // If obe prefix has been redefined, extlibs will change accordingly
        std::string obe_path = MountablePath::from_prefix(prefixes::obe.data()).base_path;
        MountablePath extlibs_path(MountablePathType::Path, obe_path + "/Lib/Extlibs",
            prefixes::extlibs, priorities::defaults, false);
        MountablePath::mount(extlibs_path);
    }

    void MountablePath::mount(const MountablePath path, SamePrefixPolicy same_prefix_policy)
    {
        if (path.deferred_resolution)
        {
            throw Exceptions::InvalidDeferredMountablePath(path.prefix, EXC_INFO);
        }
        auto path_cmp = [&path](const auto& mounted_path) { return path == *mounted_path; };
        const bool path_already_exists
            = std::find_if(MountedPaths.begin(), MountedPaths.end(), path_cmp) != MountedPaths.end();
        if (path_already_exists)
        {
            debug::Log->warn("[MountablePath] Can't Mount the same path twice: "
                             "MountablePath(prefix={}, path={}, priority={}, implicit={})",
                path.prefix, path.base_path, path.priority, path.implicit);
            return;
        }
        if (same_prefix_policy == SamePrefixPolicy::Replace)
        {
            std::erase_if(MountedPaths,
                [path](const auto& mountable_path)
                { return mountable_path->prefix == path.prefix; });
            MountedPaths.push_back(std::make_shared<MountablePath>(path));
        }
        if (same_prefix_policy != SamePrefixPolicy::Skip)
        {
            MountedPaths.push_back(std::make_shared<MountablePath>(path));
        }
        else
        {
            const auto existing_prefix_it = std::find_if(MountedPaths.begin(), MountedPaths.end(),
                [path](const auto& mountable_path) { return mountable_path->prefix == path.prefix; });
            if (existing_prefix_it == MountedPaths.end())
            {
                MountedPaths.push_back(std::make_shared<MountablePath>(path));
            }
        }
        sort();
    }

    void MountablePath::unmount(const MountablePath path)
    {
        std::erase_if(MountedPaths,
            [path](const auto& mountable_path) { return *mountable_path == path; });
    }

    void MountablePath::unmount_all()
    {
        MountedPaths.clear();
    }

    const MountList& MountablePath::paths()
    {
        return MountedPaths;
    }

    std::vector<std::string> MountablePath::string_paths()
    {
        std::vector<std::string> mounted_paths;
        mounted_paths.reserve(MountedPaths.size());
        for (const auto& mounted_path : MountedPaths)
        {
            mounted_paths.push_back(mounted_path->base_path);
        }
        return mounted_paths;
    }

    void MountablePath::sort()
    {
        std::sort(MountedPaths.begin(), MountedPaths.end(),
            [](const auto& first, const auto& second)
            { return first->priority > second->priority; });
    }

    const MountablePath& MountablePath::from_prefix(const std::string& prefix)
    {
        for (const auto& mount : MountedPaths)
        {
            if (mount->prefix == prefix)
            {
                return *mount;
            }
        }
        throw Exceptions::UnknownPathPrefix(prefix, get_all_prefixes(), EXC_INFO);
    }

    std::vector<std::string> MountablePath::get_all_prefixes()
    {
        MountList mounts = MountedPaths;
        std::vector<std::string> all_prefixes;
        all_prefixes.reserve(mounts.size());
        std::transform(mounts.begin(), mounts.end(), std::back_inserter(all_prefixes),
            [](const auto& mount) { return mount->prefix; });
        return all_prefixes;
    }

    void MountablePath::resolve_base_path()
    {
        auto [_, prefix_in_path] = split_path_and_prefix(base_path, false);
        if (!prefix_in_path.empty())
        {
            base_path = system::Path(base_path).find(PathType::Directory).path();
        }
        base_path = utils::file::canonical_path(base_path);
        deferred_resolution = false;
    }
} // namespace obe::system
