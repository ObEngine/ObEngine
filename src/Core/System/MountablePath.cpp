#include <string>
#include <vector>

#include <vili/Vili.hpp>

#include <System/MountablePath.hpp>
#include <System/Package.hpp>
#include <System/Path.hpp>
#include <System/Workspace.hpp>

namespace obe::System
{
    MountablePath::MountablePath(
        MountablePathType pathType, const std::string& basePath, unsigned int priority)
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
            Debug::Log->critical("<MountablePath> Can't find 'Mount.vili' "
                                 "file, stopping ObEngine");
            throw aube::ErrorHandler::Raise("ObEngine.System.MountablePath.NoMountFile");
        }
        for (vili::ComplexNode* path : mountedPaths.at("Mount").getAll<vili::ComplexNode>())
        {
            const std::string currentType = path->at<vili::DataNode>("type").get<std::string>();
            const std::string currentPath = path->at<vili::DataNode>("path").get<std::string>();
            int currentPriority = path->at<vili::DataNode>("priority").get<int>();
            if (currentType == "Path")
            {
                Path::Mount(MountablePath(MountablePathType::Path, currentPath, currentPriority));
                Debug::Log->info("<MountablePath> Mounted Path : '{0}' with priority {1}",
                    currentPath, currentPriority);
            }
            else if (currentType == "Package")
            {
                Package::Load(currentPath, currentPriority);
                Debug::Log->info("<MountablePath> Mounted Package : '{0}' with priority {1}",
                    currentPath, currentPriority);
            }
            else if (currentType == "Workspace")
            {
                Workspace::Load(currentPath, currentPriority);
                Debug::Log->info("<MountablePath> Mounted Workspace : '{0}' "
                                 "with priority {1}",
                    currentPath, currentPriority);
            }
        }
        Debug::Log->info("<MountablePath> List of mounted paths : ");
        for (MountablePath& currentPath : Path::MountedPaths)
        {
            Debug::Log->info("<MoutablePath> MountedPath : {0}", currentPath.basePath);
        }
    }
} // namespace obe::System