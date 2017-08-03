#include <string>
#include <vector>

#include <vili/Vili.hpp>

#include <System/MountablePath.hpp>
#include <System/Package.hpp>
#include <System/Path.hpp>
#include <System/Workspace.hpp>

namespace obe
{
    namespace System
    {
        MountablePath::MountablePath(PathType pathType, const std::string& basePath, unsigned int priority)
        {
            this->pathType = pathType;
            this->basePath = basePath;
            this->priority = priority;
        }

        void MountPaths()
        {
            Path::MountedPaths.clear();
            vili::ViliParser mountedPaths;
            mountedPaths.parseFile("Mount.vili", true);
            for (std::string path : mountedPaths.at("Mount").getAll(vili::NodeType::ComplexNode))
            {
                vili::ComplexNode& currentElement = mountedPaths.at("Mount", path);
                std::string currentType = currentElement.at<vili::DataNode>("type").get<std::string>();
                std::string currentPath = currentElement.at<vili::DataNode>("path").get<std::string>();
                int currentPriority = currentElement.at<vili::DataNode>("priority").get<int>();
                if (currentType == "Path")
                {
                    Path::Mount(MountablePath(PathType::Path, currentPath, currentPriority));
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
            for (MountablePath& currentPath : Path::MountedPaths)
            {
                std::cout << "    <System> MountedPath : " << currentPath.basePath << std::endl;
            }
        }
    }
}
