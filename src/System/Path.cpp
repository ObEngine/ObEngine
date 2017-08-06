#include <System/Path.hpp>
#include <Utils/StringUtils.hpp>

namespace obe
{
    namespace System
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
            return Path(m_path + ((m_path != "" && m_path.back() != '/') ? "/" : "") + path);
        }

        std::string Path::last() const
        {
            std::vector<std::string> splittedPath = Utils::String::split(m_path, "/");
            return splittedPath.back();
        }

        Path Path::getPath(int index)
        {
            if (MountedPaths.size() > index)
                return Path(MountedPaths[index].basePath).add(m_path);
            throw aube::ErrorHandler::Raise("ObEngine.System.Path.UnknownPathAtIndex", {{"index", std::to_string(index)}, {"path", m_path}});
        }

		std::string Path::find() const
        {
			for (MountablePath& mountedPath : MountedPaths)
			{
				int loadResponse = 0;
				if (Utils::File::fileExists(mountedPath.basePath + ((mountedPath.basePath != "") ? "/" : "") + this->m_path))
				{
					return mountedPath.basePath + ((mountedPath.basePath != "") ? "/" : "") + this->m_path;
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
            bool noChange = false;
            while (noChange == false)
            {
                noChange = true;
                for (unsigned int i = 0; i < MountedPaths.size(); i++)
                {
                    if (i != MountedPaths.size() - 1 && MountedPaths[i].priority < MountedPaths[i + 1].priority)
                    {
                        iter_swap(MountedPaths.begin() + i, MountedPaths.begin() + i + 1);
                        noChange = false;
                    }
                }
            }
        }
    }
}
