#include <System/Path.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::System
{
    std::vector<MountablePath> Path::MountedPaths = std::vector<MountablePath>();

    Path::Path()
    {
        this->m_path = "";
    }

    Path::Path(const Path& path)
    {
        this->m_path = path.toString();
    }

    Path::Path(const std::string& path)
    {
        m_path = path;
    }

    Path Path::add(const std::string& path) const
    {
        return Path(m_path + ((!m_path.empty() && m_path.back() != '/') ? "/" : "") + path);
    }

    std::string Path::last() const
    {
        std::vector<std::string> splittedPath = Utils::String::split(m_path, "/");
        return splittedPath.back();
    }

    Path Path::getPath(const unsigned int index)
    {
        if (index < MountedPaths.size())
            return Path(MountedPaths[index].basePath).add(m_path);
        throw aube::ErrorHandler::Raise("ObEngine.System.Path.UnknownPathAtIndex",
            { { "index", std::to_string(index) }, { "path", m_path } });
    }

    std::string Path::find(PathType pathType) const
    {
        for (MountablePath& mountedPath : MountedPaths)
        {
            if ((pathType == PathType::All || pathType == PathType::File)
                && Utils::File::fileExists(mountedPath.basePath
                       + ((!mountedPath.basePath.empty()) ? "/" : "") + this->m_path))
            {
                return mountedPath.basePath + ((!mountedPath.basePath.empty()) ? "/" : "")
                    + this->m_path;
            }
            else if ((pathType == PathType::All || pathType == PathType::Directory)
                && Utils::File::directoryExists(mountedPath.basePath
                       + ((!mountedPath.basePath.empty()) ? "/" : "") + this->m_path))
            {
                return mountedPath.basePath + ((!mountedPath.basePath.empty()) ? "/" : "")
                    + this->m_path;
            }
        }
        return "";
    }

    std::string Path::toString() const
    {
        return m_path;
    }

    void Path::Mount(MountablePath path)
    {
        MountedPaths.push_back(path);
        orderMountedPaths();
    }

    std::vector<MountablePath>& Path::Paths()
    {
        return MountedPaths;
    }

    void Path::orderMountedPaths()
    {
        std::sort(MountedPaths.begin(), MountedPaths.end(),
            [](const MountablePath& first, const MountablePath& second) {
                return first.priority > second.priority;
            });
    }
} // namespace obe::System