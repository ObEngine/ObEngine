#include <System/Path.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::System
{
    std::string joinPath(const std::string& base, const std::string& path)
    {
        return base + ((!base.empty()) ? "/" : "") + path;
    }

    std::unordered_map<std::string, FindResult> Path::PathCache;

    void FindResult::checkValidity() const
    {
        if (!success())
        {
            throw Exceptions::ResourceNotFound(
                m_path, MountablePath::StringPaths(), EXC_INFO);
        }
    }

    FindResult::FindResult(const std::string& pathNotFound)
    {
        m_path = pathNotFound;
    }

    FindResult::FindResult(PathType pathType, const std::string& root,
        const std::string& path, const std::string& element)
    {
        m_type = pathType;
        m_root = root;
        m_path = path;
        m_element = element;
    }

    const std::string& FindResult::path() const
    {
        checkValidity();
        return m_path;
    }

    const std::string& FindResult::root() const
    {
        checkValidity();
        return m_root;
    }

    const std::string& FindResult::element() const
    {
        return m_element;
    }

    bool FindResult::success() const
    {
        return m_type != PathType::All;
    }

    FindResult::operator bool() const
    {
        return this->success();
    }

    FindResult::operator const std::string &() const
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
        : m_mounts(MountablePath::Paths())
    {
    }

    Path::Path(const std::vector<MountablePath>& mount)
        : m_mounts(mount)
    {
    }

    Path::Path(const Path& path)
        : m_mounts(path.m_mounts)
    {
        this->m_path = path.toString();
    }

    Path::Path(std::string_view path)
        : m_mounts(MountablePath::Paths())
    {
        m_path = path;
    }

    Path& Path::set(const std::string& path)
    {
        m_path = path;
        return *this;
    }

    Path Path::add(const std::string& path) const
    {
        return Path(
            m_path + ((!m_path.empty() && m_path.back() != '/') ? "/" : "") + path);
    }

    std::string Path::last() const
    {
        std::vector<std::string> splitPath = Utils::String::split(m_path, "/");
        return splitPath.back();
    }

    Path Path::getPath(const std::size_t index) const
    {
        if (index < m_mounts.size())
            return Path(m_mounts[index].basePath).add(m_path);
        std::vector<std::string> mountNames;
        mountNames.reserve(m_mounts.size());
        for (const auto& mount : m_mounts)
        {
            mountNames.push_back(mount.basePath);
        }
        throw Exceptions::MountablePathIndexOverflow(
            index, m_mounts.size(), mountNames, EXC_INFO);
    }

    std::vector<FindResult> Path::list(PathType pathType) const
    {
        std::vector<FindResult> results;
        for (const MountablePath& mountedPath : m_mounts)
        {
            std::string fullPath = joinPath(mountedPath.basePath, m_path);

            if (Utils::File::directoryExists(fullPath))
            {
                if (pathType == PathType::All || pathType == PathType::Directory)
                {
                    std::vector<std::string> directories
                        = Utils::File::getDirectoryList(fullPath);
                    for (const std::string& directory : directories)
                    {
                        results.emplace_back(PathType::Directory, mountedPath.basePath,
                            joinPath(fullPath, directory), directory);
                    }
                }
                else if (pathType == PathType::All || pathType == PathType::File)
                {
                    std::vector<std::string> files = Utils::File::getFileList(fullPath);
                    for (const std::string& file : files)
                    {
                        results.emplace_back(PathType::File, mountedPath.basePath,
                            joinPath(fullPath, file), file);
                    }
                }
            }
        }

        return results;
    }

    FindResult Path::find(PathType pathType) const
    {
        if (const auto cacheResult = PathCache.find(m_path);
            cacheResult != PathCache.end())
        {
            return cacheResult->second;
        }
        for (const MountablePath& mountedPath : m_mounts)
        {
            const std::string fullPath = mountedPath.basePath
                + ((!mountedPath.basePath.empty()) ? "/" : "") + m_path;
            if ((pathType == PathType::All || pathType == PathType::File)
                && Utils::File::fileExists(fullPath))
            {
                const std::string result = joinPath(mountedPath.basePath, m_path);
                return PathCache
                    .emplace(m_path,
                        FindResult(PathType::File, mountedPath.basePath, result, m_path))
                    .first->second;
            }
            else if ((pathType == PathType::All || pathType == PathType::Directory)
                && Utils::File::directoryExists(fullPath))
            {
                const std::string result = joinPath(mountedPath.basePath, m_path);
                return PathCache
                    .emplace(m_path,
                        FindResult(
                            PathType::Directory, mountedPath.basePath, result, m_path))
                    .first->second;
            }
        }
        return FindResult(m_path);
    }

    std::vector<FindResult> Path::findAll(PathType pathType) const
    {
        std::vector<FindResult> results;
        for (const MountablePath& mountedPath : m_mounts)
        {
            const std::string fullPath = joinPath(mountedPath.basePath, m_path);
            if ((pathType == PathType::All || pathType == PathType::File)
                && Utils::File::fileExists(fullPath))
            {
                results.emplace_back(
                    PathType::File, mountedPath.basePath, fullPath, m_path);
            }
            else if ((pathType == PathType::All || pathType == PathType::Directory)
                && Utils::File::directoryExists(fullPath))
            {
                results.emplace_back(
                    PathType::Directory, mountedPath.basePath, fullPath, m_path);
            }
        }
        return results;
    }

    std::string Path::toString() const
    {
        return m_path;
    }

    void Path::operator=(const Path& path)
    {
        m_path = path.m_path;
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
