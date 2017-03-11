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
			std::function<int(std::vector<std::string>*, std::string)> dirPathLoader = [](std::vector<std::string>* obj, std::string path) -> int {
				std::vector<std::string> newPaths = Functions::File::listDirInDir(path);
				obj->insert(obj->end(), newPaths.begin(), newPaths.end());
				return 0x002;
			};
			std::function<int(std::vector<std::string>*, std::string)> filePathLoader = [](std::vector<std::string>* obj, std::string path) -> int {
				std::vector<std::string> newFiles = Functions::File::listFileInDir(path);
				obj->insert(obj->end(), newFiles.begin(), newFiles.end());
				return 0x002;
			};
			std::function<int(kaguya::State*, std::string)> luaLoader = [](kaguya::State* obj, std::string path) -> int { return obj->dofile(path); };
		}
		
		PriorizedPath::PriorizedPath(PathType::PathType pathType, std::string basePath, unsigned int priority)
		{
			this->pathType = pathType;
			this->basePath = basePath;
			this->priority = priority;
		}

		std::string PriorizedPath::getPath()
		{
			return basePath;
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
						std::iter_swap(basePaths.begin() + i, basePaths.begin() + i + 1);
						noChange = false;
					}
				}
			}
		}
		Path::Path()
		{
			this->path = "";
		}
		Path::Path(const Path& path)
		{
			this->path = path.toString();
		}
		Path::Path(std::string path)
		{
			this->path = path;
		}
		Path Path::add(std::string path)
		{
			return Path(this->path + "/" + path);
		}
		std::string Path::getPath(int index)
		{
			if (basePaths.size() > index)
				return basePaths[index].getPath() + ((basePaths[index].getPath() != "") ? "/" : "") + this->path;
			else
				std::cout << "<Error:PathResolver:Path>[getPath] : Can't find BasePath at index : " << index << std::endl;
		}
		std::string Path::toString() const
		{
			return this->path;
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
			for (std::string path : mountedPaths->at("Mount")->getAll(vili::Types::ComplexAttribute)) {
				vili::ComplexAttribute* currentElement = mountedPaths->at("Mount", path);
				std::string currentType = currentElement->at<vili::BaseAttribute>("type")->get<std::string>();
				std::string currentPath = currentElement->at<vili::BaseAttribute>("path")->get<std::string>();
				int currentPriority = currentElement->at<vili::BaseAttribute>("priority")->get<int>();
				if (currentType == "Path") {
					obe::System::Path::addPath(obe::System::PriorizedPath(obe::System::PathType::Path, currentPath, currentPriority));
					std::cout << "Mounted Path : <" << currentPath << "> with priority : " << currentPriority << std::endl;
				}
				else if (currentType == "Package") {
					System::Package::Load(currentPath, currentPriority);
					std::cout << "Mounted Package : <" << currentPath << "> with priority : " << currentPriority << std::endl;
				}
				else if (currentType == "Workspace") {
					System::Workspace::Load(currentPath, currentPriority);
					std::cout << "Mounted Workspace : <" << currentPath << "> with priority : " << currentPriority << std::endl;
				}
			}
			std::cout << "<System> List of mounted paths : " << std::endl;
			for (obe::System::PriorizedPath& currentPath : obe::System::Path::basePaths) {
				std::cout << "    <System> MountedPath : " << currentPath.getPath() << std::endl;
			}
		}
	}
}