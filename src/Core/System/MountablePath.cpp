#include <string>
#include <vector>

#include <Config/Templates/Mount.hpp>
#include <System/MountablePath.hpp>
#include <System/Package.hpp>
#include <System/Path.hpp>
#include <System/Workspace.hpp>

#include <vili/parser/parser.hpp>

namespace obe::System
{
    std::vector<MountablePath> MountablePath::MountedPaths = std::vector<MountablePath>();

    MountablePath::MountablePath(
        MountablePathType pathType, const std::string& basePath, unsigned int priority)
    {
        this->pathType = pathType;
        this->basePath = basePath;
        this->priority = priority;
    }

    bool MountablePath::operator==(const MountablePath& other) const
    {
        return (this->basePath == other.basePath && this->priority == other.priority
            && this->pathType == other.pathType);
    }

    void MountablePath::LoadMountFile()
    {
        MountablePath::MountedPaths.clear();
        vili::node mountedPaths;
        try
        {
            mountedPaths = vili::parser::from_file(
                "Mount.vili", Config::Templates::getMountTemplates());
        }
        catch (std::exception& e)
        {
            Debug::Log->critical(
                "<MountablePath> Unable to load 'Mount.vili' : \n{}", e.what());
            throw Exceptions::MountFileMissing(
                Utils::File::getCurrentDirectory(), EXC_INFO);
        }
        for (vili::node& path : mountedPaths.at("Mount"))
        {
            const std::string currentType = path.at("type");
            const std::string currentPath = path.at("path");
            int currentPriority = path.at("priority");
            if (currentType == "Path")
            {
                MountablePath::Mount(
                    MountablePath(MountablePathType::Path, currentPath, currentPriority));
                Debug::Log->info("<MountablePath> Mounted Path : '{0}' with priority {1}",
                    currentPath, currentPriority);
            }
            else if (currentType == "Package")
            {
                Package::Load(currentPath, currentPriority);
                Debug::Log->info(
                    "<MountablePath> Mounted Package : '{0}' with priority {1}",
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
        for (MountablePath& currentPath : MountablePath::MountedPaths)
        {
            Debug::Log->info("<MountablePath> MountedPath : {0}", currentPath.basePath);
        }
    }

    void MountablePath::Mount(const MountablePath path)
    {
        MountedPaths.push_back(path);
        Sort();
    }

    void MountablePath::Unmount(const MountablePath path)
    {
        MountedPaths.erase(
            std::remove_if(MountedPaths.begin(), MountedPaths.end(),
                [path](MountablePath& mountablePath) { return mountablePath == path; }),
            MountedPaths.end());
    }

    const std::vector<MountablePath>& MountablePath::Paths()
    {
        return MountedPaths;
    }

    std::vector<std::string> MountablePath::StringPaths()
    {
        std::vector<std::string> mountedPaths;
        mountedPaths.reserve(MountedPaths.size());
        for (auto& mountedPath : MountedPaths)
        {
            mountedPaths.push_back(mountedPath.basePath);
        }
        return mountedPaths;
    }

    void MountablePath::Sort()
    {
        std::sort(MountedPaths.begin(), MountedPaths.end(),
            [](const MountablePath& first, const MountablePath& second) {
                return first.priority > second.priority;
            });
    }
} // namespace obe::System