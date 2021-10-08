#include <Debug/Logger.hpp>
#include <System/Path.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::System
{
    std::string joinPath(const std::string& base, const std::string& path)
    {
        return base + ((!base.empty()) ? "/" : "") + path;
    }

    std::pair<std::string, std::string> splitPathAndPrefix(
        const std::string& path, bool warnOnMissingPrefix)
    {
        if (const auto prefixPos = path.find("://"); prefixPos != std::string::npos)
        {
            std::string prefix = path.substr(0, prefixPos);
            if (prefix == "*")
            {
                prefix.clear();
            }
            return std::make_pair(path.substr(prefixPos + 3), prefix);
        }

        if (warnOnMissingPrefix)
        {
            Debug::Log->warn("Path '{}' has no prefix, defaulting to '*://'", path);
        }
        return std::make_pair(path, "");
    }

    MountList filterMountablePathsWithPrefix(const MountList& mounts, const std::string& prefix)
    {
        std::vector<std::shared_ptr<MountablePath>> validMounts;
        for (const auto& mountablePath : mounts)
        {
            if (mountablePath->prefix == prefix || (prefix.empty() && mountablePath->implicit))
            {
                validMounts.push_back(mountablePath);
            }
        }
        if (validMounts.empty())
        {
            std::vector<std::string> allPrefixes;
            allPrefixes.reserve(mounts.size());
            std::transform(mounts.begin(), mounts.end(), std::back_inserter(allPrefixes),
                [](const auto& mount) { return mount->prefix; });
            throw Exceptions::UnknownPathPrefix(prefix, allPrefixes, EXC_INFO);
        }
        return validMounts;
    }

    std::unordered_map<std::string, FindResult> Path::PathCache;

    void FindResult::checkValidity() const
    {
        if (!success())
        {
            std::vector<std::string> mountsAsStrings;
            std::transform(m_mounts.begin(), m_mounts.end(), std::back_inserter(mountsAsStrings),
                [](const auto& mount)
                { return fmt::format("\"{}:// = {}\"", mount->prefix, mount->basePath); });
            throw Exceptions::ResourceNotFound(m_path, mountsAsStrings, EXC_INFO);
        }
    }

    FindResult::FindResult(
        const std::string& pathNotFound, const std::string& query, const MountList& mounts)
        : m_mounts(mounts)
    {
        m_path = pathNotFound;
        m_query = query;
    }

    FindResult::FindResult(PathType pathType, std::shared_ptr<MountablePath> mount,
        const std::string& path, const std::string& query, const std::string& element)
        : m_mount(std::move(mount))
    {
        m_type = pathType;
        m_path = path;
        m_query = query;
        if (element.empty())
        {
            m_element = element;
        }
        else
        {
            m_element = m_path;
        }
    }

    std::string FindResult::hypotheticalPath() const
    {
        if (success())
        {
            return m_path;
        }
        const auto [path, prefix] = splitPathAndPrefix(m_query, false);
        for (const auto& mount : m_mounts)
        {
            if (mount->prefix == prefix)
            {
                return Utils::File::join({ mount->basePath, path });
            }
        }

        return "";
    }

    const std::string& FindResult::path() const
    {
        checkValidity();
        return m_path;
    }

    const MountablePath& FindResult::mount() const
    {
        checkValidity();
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
        checkValidity();
        return m_path;
    }

    FindResult::operator const char*() const
    {
        checkValidity();
        return m_path.c_str();
    }

    FindResult::operator std::string_view() const
    {
        checkValidity();
        return m_path;
    }

    Path::Path()
        : m_mounts(&MountablePath::Paths())
    {
    }

    Path::Path(const MountList& mount)
        : m_mounts(&m_customMounts)
        , m_customMounts(mount)
    {
    }

    const MountList* Path::copyMountSource(const Path& path)
    {
        // Using the default mount source
        if (path.m_mounts == &MountablePath::Paths())
        {
            return &MountablePath::Paths();
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
        : m_mounts(copyMountSource(path))
    {
        this->m_path = path.toString();
        this->m_prefix = path.m_prefix;
        this->m_customMounts = path.m_customMounts;
    }

    Path::Path(std::string_view path)
        : m_mounts(&MountablePath::Paths())
    {
        std::tie(m_path, m_prefix) = splitPathAndPrefix(path.data());
    }

    Path::Path(std::string_view prefix, std::string_view path)
        : m_mounts(&MountablePath::Paths())
    {
        m_prefix = prefix;
        m_path = path;
    }

    Path& Path::set(const std::string& path)
    {
        std::tie(m_path, m_prefix) = splitPathAndPrefix(path);
        return *this;
    }

    Path Path::add(const std::string& path) const
    {
        return Path(
            m_prefix, m_path + ((!m_path.empty() && m_path.back() != '/') ? "/" : "") + path);
    }

    std::string Path::last() const
    {
        std::vector<std::string> splitPath = Utils::String::split(m_path, "/");
        return splitPath.back();
    }

    Path Path::getPath(const std::size_t index) const
    {
        if (index < m_mounts->size())
            return Path(m_mounts->at(index)->basePath).add(m_path);
        std::vector<std::string> mountNames;
        mountNames.reserve(m_mounts->size());
        for (const auto& mount : *m_mounts)
        {
            mountNames.push_back(mount->basePath);
        }
        throw Exceptions::MountablePathIndexOverflow(index, m_mounts->size(), mountNames, EXC_INFO);
    }

    std::vector<FindResult> Path::list(PathType pathType) const
    {
        std::vector<FindResult> results;
        const std::string query = fmt::format("{}://{}", m_prefix, m_path);
        const MountList validMounts = filterMountablePathsWithPrefix(*m_mounts, m_prefix);
        for (const auto& mountedPath : validMounts)
        {
            std::string fullPath = joinPath(mountedPath->basePath, m_path);

            if (Utils::File::directoryExists(fullPath))
            {
                if (pathType == PathType::All || pathType == PathType::Directory)
                {
                    std::vector<std::string> directories = Utils::File::getDirectoryList(fullPath);
                    for (const std::string& directory : directories)
                    {
                        results.emplace_back(PathType::Directory, mountedPath,
                            joinPath(fullPath, directory), query, directory);
                    }
                }
                else if (pathType == PathType::All || pathType == PathType::File)
                {
                    std::vector<std::string> files = Utils::File::getFileList(fullPath);
                    for (const std::string& file : files)
                    {
                        results.emplace_back(
                            PathType::File, mountedPath, joinPath(fullPath, file), query, file);
                    }
                }
            }
        }

        return results;
    }

    FindResult Path::find(PathType pathType) const
    {
        const std::string query = fmt::format("{}://{}", m_prefix, m_path);
        if (const auto cacheResult = PathCache.find(m_path); cacheResult != PathCache.end())
        {
            return cacheResult->second;
        }
        MountList validMounts;
        try
        {
            validMounts = filterMountablePathsWithPrefix(*m_mounts, m_prefix);
        }
        catch (const Exceptions::UnknownPathPrefix& exc)
        {
            throw Exceptions::PathError(m_prefix, m_path, EXC_INFO).nest(exc);
        }

        for (const auto& mountedPath : validMounts)
        {
            const std::string fullPath
                = mountedPath->basePath + ((!mountedPath->basePath.empty()) ? "/" : "") + m_path;
            if ((pathType == PathType::All || pathType == PathType::File)
                && Utils::File::fileExists(fullPath))
            {
                const std::string result = joinPath(mountedPath->basePath, m_path);
                return PathCache
                    .emplace(m_path, FindResult(PathType::File, mountedPath, result, query))
                    .first->second;
            }
            else if ((pathType == PathType::All || pathType == PathType::Directory)
                && Utils::File::directoryExists(fullPath))
            {
                const std::string result = joinPath(mountedPath->basePath, m_path);
                return PathCache
                    .emplace(m_path, FindResult(PathType::Directory, mountedPath, result, query))
                    .first->second;
            }
        }
        return FindResult(m_path, query, validMounts);
    }

    std::vector<FindResult> Path::findAll(PathType pathType) const
    {
        const std::string query = fmt::format("{}://{}", m_prefix, m_path);
        std::vector<FindResult> results;
        const MountList validMounts = filterMountablePathsWithPrefix(*m_mounts, m_prefix);
        for (const auto& mountedPath : validMounts)
        {
            const std::string fullPath = joinPath(mountedPath->basePath, m_path);
            if ((pathType == PathType::All || pathType == PathType::File)
                && Utils::File::fileExists(fullPath))
            {
                results.emplace_back(PathType::File, mountedPath, fullPath, query);
            }
            else if ((pathType == PathType::All || pathType == PathType::Directory)
                && Utils::File::directoryExists(fullPath))
            {
                results.emplace_back(PathType::Directory, mountedPath, fullPath, query);
            }
        }
        return results;
    }

    std::string Path::toString() const
    {
        return m_path;
    }

    Path& Path::operator=(const Path& path)
    {
        m_customMounts = path.m_customMounts;
        m_mounts = copyMountSource(path);
        m_path = path.m_path;
        m_prefix = path.m_prefix;
        return *this;
    }

    Path::operator std::string() const
    {
        return this->toString();
    }

    MountList ContextualPathFactory::makeMountList(const std::string& base)
    {
        MountList customMounts = MountablePath::Paths();
        customMounts.push_back(
            std::make_unique<System::MountablePath>(System::MountablePathType::Path, base, "self"));
        return customMounts;
    }

    MountList ContextualPathFactory::makeMountList(
        const std::string& base, const MountList& customMounts)
    {
        MountList _customMounts = customMounts;
        _customMounts.push_back(
            std::make_unique<System::MountablePath>(System::MountablePathType::Path, base, "self"));
        return _customMounts;
    }

    ContextualPathFactory::ContextualPathFactory(const std::string& base)
        : m_base(makeMountList(base))
    {
    }

    ContextualPathFactory::ContextualPathFactory(
        const std::string& base, const MountList& customMounts)
        : m_base(makeMountList(base, customMounts))
    {
    }

    Path ContextualPathFactory::operator()(const std::string& path) const
    {
        Path newPath = m_base;
        return newPath.set(path);
    }
} // namespace obe::System

obe::System::Path operator"" _path(const char* str, std::size_t len)
{
    return obe::System::Path(std::string(str, len));
}

std::string operator""_fs(const char* str, std::size_t len)
{
    return obe::System::Path(std::string(str, len)).find();
}
