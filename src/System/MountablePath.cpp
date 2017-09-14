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
        MountablePath::MountablePath(MountablePathType pathType, const std::string& basePath, unsigned int priority)
        {
            this->pathType = pathType;
            this->basePath = basePath;
            this->priority = priority;
        }

        void MountPaths()
        {
            Path::MountedPaths.clear();
            vili::ViliParser mountedPaths;
            try
            {
                mountedPaths.parseFile("Mount.vili", true);
            }
            catch (...)
            {
                Debug::Log->critical("<MountablePath> Can't find 'Mount.vili' file, stopping ObEngine");
                throw aube::ErrorHandler::Raise("ObEngine.System.MountablePath.NoMountFile");
            }
            for (std::string path : mountedPaths.at("Mount").getAll(vili::NodeType::ComplexNode))
            {
                vili::ComplexNode& currentElement = mountedPaths.at("Mount", path);
                std::string currentType = currentElement.at<vili::DataNode>("type").get<std::string>();
                std::string currentPath = currentElement.at<vili::DataNode>("path").get<std::string>();
                int currentPriority = currentElement.at<vili::DataNode>("priority").get<int>();
                if (currentType == "Path")
                {
                    Path::Mount(MountablePath(MountablePathType::Path, currentPath, currentPriority));
                    Debug::Log->info("<MountablePath> Mounted Path : '{0}' with priority {1}", currentPath, currentPriority);
                }
                else if (currentType == "Package")
                {
                    Package::Load(currentPath, currentPriority);
                    Debug::Log->info("<MountablePath> Mounted Package : '{0}' with priority {1}", currentPath, currentPriority);
                }
                else if (currentType == "Workspace")
                {
                    Workspace::Load(currentPath, currentPriority);
                    Debug::Log->info("<MountablePath> Mounted Workspace : '{0}' with priority {1}", currentPath, currentPriority);
                }
            }
            Debug::Log->info("<MountablePath> List of mounted paths : ");
            for (MountablePath& currentPath : Path::MountedPaths)
            {
                Debug::Log->info("<MoutablePath> MountedPath : {0}", currentPath.basePath);
            }
        }
    }
}
