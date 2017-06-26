#include "PathResolver.hpp"

namespace obe
{
    namespace System
    {
        namespace Loaders
        {
            std::function<int(sf::Texture*, std::string)> textureLoader = [](sf::Texture* obj, std::string path) -> int { return obj->loadFromFile(path); };
            std::function<int(vili::DataParser*, std::string)> dataLoader = [](vili::DataParser* obj, std::string path) -> int { return obj->parseFile(path); };
            std::function<int(sf::Font*, std::string)> fontLoader = [](sf::Font* obj, std::string path) -> int { return obj->loadFromFile(path); };
            std::function<int(std::vector<std::string>*, std::string)> dirPathLoader = [](std::vector<std::string>* obj, std::string path) -> int
            {
                std::vector<std::string> newPaths = Functions::File::getDirectoryList(path);
                obj->insert(obj->end(), newPaths.begin(), newPaths.end());
                return 0x002;
            };
            std::function<int(std::vector<std::string>*, std::string)> filePathLoader = [](std::vector<std::string>* obj, std::string path) -> int
            {
                std::vector<std::string> newFiles = Functions::File::getFileList(path);
                obj->insert(obj->end(), newFiles.begin(), newFiles.end());
                return 0x002;
            };
            std::function<int(kaguya::State*, std::string)> luaLoader = [](kaguya::State* obj, std::string path) -> int { return obj->dofile(path); };
            std::function<int(sf::SoundBuffer*, std::string)> soundLoader = [](sf::SoundBuffer* sound, std::string path) -> int { return sound->loadFromFile(path); };
            std::function<int(sf::Music*, std::string)> musicLoader = [](sf::Music* music, std::string path) -> int { return music->openFromFile(path); };
        }

        PriorizedPath::PriorizedPath(PathType::PathType pathType, const std::string& basePath, unsigned int priority)
        {
            this->pathType = pathType;
            this->basePath = basePath;
            this->priority = priority;
        }

        std::vector<PriorizedPath> Path::basePaths = std::vector<PriorizedPath>();

        void Path::orderPriorizedPaths()
        {
            bool noChange = false;
            while (noChange == false)
            {
                noChange = true;
                for (unsigned int i = 0; i < basePaths.size(); i++)
                {
                    if (i != basePaths.size() - 1 && basePaths[i].priority < basePaths[i + 1].priority)
                    {
                        iter_swap(basePaths.begin() + i, basePaths.begin() + i + 1);
                        noChange = false;
                    }
                }
            }
        }

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
            std::vector<std::string> splittedPath = Functions::String::split(m_path, "/");
            return splittedPath.back();
        }

        Path Path::getPath(int index)
        {
			if (basePaths.size() > index)
				return Path(basePaths[index].basePath).add(m_path);
            throw aube::ErrorHandler::Raise("ObEngine.PathResolver.Path.UnknownPathAtIndex", {{"index", std::to_string(index)}, {"path", m_path}});
        }

	    std::string Path::toString() const
	    {
			return m_path;
	    }

        void Path::addPath(PriorizedPath path)
        {
            basePaths.push_back(path);
            orderPriorizedPaths();
        }

        std::vector<PriorizedPath>& Path::Paths()
        {
            return basePaths;
        }

        void MountPaths()
        {
            Path::basePaths.clear();
            vili::DataParser mountedPaths;
            mountedPaths.parseFile("Mount.vili", true);
            mountedPaths.writeFile("MountExport.vili");
            for (std::string path : mountedPaths.at("Mount").getAll(vili::Types::ComplexAttribute))
            {
                vili::ComplexAttribute& currentElement = mountedPaths.at("Mount", path);
                std::string currentType = currentElement.at<vili::BaseAttribute>("type").get<std::string>();
                std::string currentPath = currentElement.at<vili::BaseAttribute>("path").get<std::string>();
                int currentPriority = currentElement.at<vili::BaseAttribute>("priority").get<int>();
                if (currentType == "Path")
                {
                    Path::addPath(PriorizedPath(PathType::Path, currentPath, currentPriority));
                    std::cout << "Mounted Path : <" << currentPath << "> with priority : " << currentPriority << std::endl;
                }
                else if (currentType == "Package")
                {
                    Package::Load(currentPath, currentPriority);
                    std::cout << "Mounted Package : <" << currentPath << "> with priority : " << currentPriority << std::endl;
                }
                else if (currentType == "Workspace")
                {
                    Workspace::Load(currentPath, currentPriority);
                    std::cout << "Mounted Workspace : <" << currentPath << "> with priority : " << currentPriority << std::endl;
                }
            }
            std::cout << "<System> List of mounted paths : " << std::endl;
            for (PriorizedPath& currentPath : Path::basePaths)
            {
                std::cout << "    <System> MountedPath : " << currentPath.basePath << std::endl;
            }
        }
    }
}
