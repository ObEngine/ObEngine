#include <Debug/Logger.hpp>
#include <System/Path.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::system
{
    std::pair<std::string, std::string> split_path_and_prefix(
        const std::string& path, bool warn_on_missing_prefix)
    {
        if (const auto prefix_pos = path.find("://"); prefix_pos != std::string::npos)
        {
            std::string prefix = path.substr(0, prefix_pos);
            if (prefix == "*")
            {
                prefix.clear();
            }
            return std::make_pair(path.substr(prefix_pos + 3), prefix);
        }

        if (warn_on_missing_prefix)
        {
            debug::Log->debug("Path '{}' has no prefix, defaulting to '*://'", path);
        }
        return std::make_pair(path, "");
    }

    MountList filter_mountable_paths_with_prefix(const MountList& mounts, const std::string& prefix)
    {
        std::vector<std::shared_ptr<MountablePath>> valid_mounts;
        for (const auto& mountable_path : mounts)
        {
            if (mountable_path->prefix == prefix || (prefix.empty() && mountable_path->implicit))
            {
                valid_mounts.push_back(mountable_path);
            }
        }
        if (valid_mounts.empty())
        {
            std::vector<std::string> all_prefixes;
            all_prefixes.reserve(mounts.size());
            std::transform(mounts.begin(), mounts.end(), std::back_inserter(all_prefixes),
                [](const auto& mount) { return mount->prefix; });
            throw exceptions::UnknownPathPrefix(prefix, all_prefixes, EXC_INFO);
        }
        return valid_mounts;
    }

    std::unordered_map<std::string, FindResult> Path::PathCache;

    void FindResult::check_validity() const
    {
        if (!success())
        {
            std::vector<std::string> mounts_as_strings;
            std::transform(m_mounts.begin(), m_mounts.end(), std::back_inserter(mounts_as_strings),
                [](const auto& mount) {
                    return fmt::format("\"{}:// = {}\"", mount->prefix, mount->base_path);
                });
            std::string path_type;
            if (m_type == PathType::All)
            {
                path_type = "Resource";
            }
            else
            {
                path_type = PathTypeMeta::to_string(m_type);
            }
            throw exceptions::ResourceNotFound(m_path, path_type, mounts_as_strings, EXC_INFO);
        }
    }

    FindResult::FindResult(PathType path_type, const std::string& path_not_found,
        const std::string& query, const MountList& mounts)
        : m_type(path_type)
        , m_path(path_not_found)
        , m_query(query)
        , m_mounts(mounts)
    {
    }

    FindResult::FindResult(PathType path_type, std::shared_ptr<MountablePath> mount,
        const std::string& path, const std::string& query, const std::string& element)
        : m_type(path_type)
        , m_mount(std::move(mount))
        , m_path(path)
        , m_query(query)
    {
        if (element.empty())
        {
            m_element = element;
        }
        else
        {
            m_element = m_path;
        }
    }

    std::string FindResult::hypothetical_path() const
    {
        if (success())
        {
            return m_path;
        }
        const auto [path, prefix] = split_path_and_prefix(m_query, false);
        for (const auto& mount : m_mounts)
        {
            if (mount->prefix == prefix)
            {
                return utils::file::join({ mount->base_path, path });
            }
        }

        return "";
    }

    std::string FindResult::path() const
    {
        check_validity();
        const std::string canonical_path = utils::file::canonical_path(m_path);
        return utils::file::normalize_path(canonical_path);
    }

    const MountablePath& FindResult::mount() const
    {
        check_validity();
        return *m_mount;
    }

    const std::string& FindResult::query() const
    {
        return m_query;
    }

    const std::string& FindResult::element() const
    {
        return m_element;
    }

    bool FindResult::success() const
    {
        return static_cast<bool>(m_mount);
    }

    FindResult::operator bool() const
    {
        return this->success();
    }

    FindResult::operator const std::string&() const
    {
        check_validity();
        return m_path;
    }

    FindResult::operator const char*() const
    {
        check_validity();
        return m_path.c_str();
    }

    FindResult::operator std::string_view() const
    {
        check_validity();
        return m_path;
    }

    Path::Path()
        : m_mounts(&MountablePath::paths())
    {
    }

    Path::Path(const MountList& mount)
        : m_mounts(&m_customMounts)
        , m_customMounts(mount)
    {
    }

    const MountList* Path::copy_mount_source(const Path& path) const
    {
        // Using the default mount source
        if (path.m_mounts == &MountablePath::paths())
        {
            return &MountablePath::paths();
        }
        // Pointing to own custom mounts
        if (path.m_mounts == &path.m_customMounts)
        {
            return &this->m_customMounts;
        }
        // Unknown origin, keeping as-is
        return path.m_mounts;
    }

    Path::Path(const Path& path)
        : m_prefix(path.m_prefix)
        , m_mounts(copy_mount_source(path))
        , m_customMounts(path.m_customMounts)
    {
        this->m_path = path.to_string();
    }

    Path::Path(std::string_view path)
        : m_mounts(&MountablePath::paths())
    {
        std::tie(m_path, m_prefix) = split_path_and_prefix(path.data());
    }

    Path::Path(std::string_view prefix, std::string_view path)
        : m_path(path)
        , m_prefix(prefix)
        , m_mounts(&MountablePath::paths())
    {
    }

    Path& Path::set(const std::string& path)
    {
        std::tie(m_path, m_prefix) = split_path_and_prefix(path);
        return *this;
    }

    Path Path::add(const std::string& path) const
    {
        return Path(
            m_prefix, m_path + ((!m_path.empty() && m_path.back() != '/') ? "/" : "") + path);
    }

    std::string Path::last() const
    {
        std::vector<std::string> split_path = utils::string::split(m_path, "/");
        return split_path.back();
    }

    Path Path::get_path(const std::size_t index) const
    {
        if (index < m_mounts->size())
            return Path(m_mounts->at(index)->base_path).add(m_path);
        std::vector<std::string> mount_names;
        mount_names.reserve(m_mounts->size());
        for (const auto& mount : *m_mounts)
        {
            mount_names.push_back(mount->base_path);
        }
        throw exceptions::MountablePathIndexOverflow(
            index, m_mounts->size(), mount_names, EXC_INFO);
    }

    std::vector<FindResult> Path::list(PathType path_type) const
    {
        std::vector<FindResult> results;
        const std::string query = fmt::format("{}://{}", m_prefix, m_path);
        const MountList valid_mounts = filter_mountable_paths_with_prefix(*m_mounts, m_prefix);
        for (const auto& mounted_path : valid_mounts)
        {
            std::string full_path = utils::file::join({ mounted_path->base_path, m_path });

            if (utils::file::directory_exists(full_path))
            {
                if (path_type == PathType::All || path_type == PathType::Directory)
                {
                    std::vector<std::string> directories
                        = utils::file::get_directory_list(full_path);
                    for (const std::string& directory : directories)
                    {
                        results.emplace_back(PathType::Directory, mounted_path,
                            utils::file::join({ full_path, directory }), query, directory);
                    }
                }
                else if (path_type == PathType::All || path_type == PathType::File)
                {
                    std::vector<std::string> files = utils::file::get_file_list(full_path);
                    for (const std::string& file : files)
                    {
                        results.emplace_back(PathType::File, mounted_path,
                            utils::file::join({ full_path, file }), query, file);
                    }
                }
            }
        }

        return results;
    }

    FindResult Path::find(PathType path_type) const
    {
        const std::string query = fmt::format("{}://{}", m_prefix, m_path);
        if (const auto cache_result = PathCache.find(query); cache_result != PathCache.end())
        {
            return cache_result->second;
        }
        MountList valid_mounts;
        try
        {
            valid_mounts = filter_mountable_paths_with_prefix(*m_mounts, m_prefix);
        }
        catch (const exceptions::UnknownPathPrefix& exc)
        {
            throw exceptions::PathError(m_prefix, m_path, EXC_INFO).nest(exc);
        }

        for (const auto& mounted_path : valid_mounts)
        {
            const std::string full_path = mounted_path->base_path
                + ((!mounted_path->base_path.empty()) ? "/" : "") + m_path;
            if ((path_type == PathType::All || path_type == PathType::File)
                && utils::file::file_exists(full_path))
            {
                const std::string result = utils::file::join({ mounted_path->base_path, m_path });
                return PathCache
                    .emplace(query, FindResult(PathType::File, mounted_path, result, query))
                    .first->second;
            }
            else if ((path_type == PathType::All || path_type == PathType::Directory)
                && utils::file::directory_exists(full_path))
            {
                const std::string result = utils::file::join({ mounted_path->base_path, m_path });
                return PathCache
                    .emplace(query, FindResult(PathType::Directory, mounted_path, result, query))
                    .first->second;
            }
        }
        return FindResult(path_type, m_path, query, valid_mounts);
    }

    std::vector<FindResult> Path::find_all(PathType path_type) const
    {
        const std::string query = fmt::format("{}://{}", m_prefix, m_path);
        std::vector<FindResult> results;
        const MountList valid_mounts = filter_mountable_paths_with_prefix(*m_mounts, m_prefix);
        for (const auto& mounted_path : valid_mounts)
        {
            const std::string full_path = utils::file::join({ mounted_path->base_path, m_path });
            if ((path_type == PathType::All || path_type == PathType::File)
                && utils::file::file_exists(full_path))
            {
                results.emplace_back(PathType::File, mounted_path, full_path, query);
            }
            else if ((path_type == PathType::All || path_type == PathType::Directory)
                && utils::file::directory_exists(full_path))
            {
                results.emplace_back(PathType::Directory, mounted_path, full_path, query);
            }
        }
        return results;
    }

    std::string Path::to_string() const
    {
        return m_path;
    }

    Path& Path::operator=(const Path& path)
    {
        m_customMounts = path.m_customMounts;
        m_mounts = copy_mount_source(path);
        m_path = path.m_path;
        m_prefix = path.m_prefix;
        return *this;
    }

    Path::operator std::string() const
    {
        return this->to_string();
    }

    MountList ContextualPathFactory::make_mount_list(const std::string& base) const
    {
        MountList custom_mounts = MountablePath::paths();
        custom_mounts.push_back(
            std::make_unique<system::MountablePath>(system::MountablePathType::Path, base, "self"));
        return custom_mounts;
    }

    MountList ContextualPathFactory::make_mount_list(
        const std::string& base, const MountList& custom_mounts) const
    {
        MountList _customMounts = custom_mounts;
        _customMounts.push_back(
            std::make_unique<system::MountablePath>(system::MountablePathType::Path, base, "self"));
        return _customMounts;
    }

    ContextualPathFactory::ContextualPathFactory(const std::string& base)
        : m_base(make_mount_list(base))
    {
    }

    ContextualPathFactory::ContextualPathFactory(
        const std::string& base, const MountList& custom_mounts)
        : m_base(make_mount_list(base, custom_mounts))
    {
    }

    Path ContextualPathFactory::operator()(const std::string& path) const
    {
        Path new_path = m_base;
        return new_path.set(path);
    }
} // namespace obe::system

obe::system::Path operator"" _path(const char* str, std::size_t len)
{
    return obe::system::Path(std::string(str, len));
}

std::string operator""_fs(const char* str, std::size_t len)
{
    return obe::system::Path(std::string(str, len)).find();
}
