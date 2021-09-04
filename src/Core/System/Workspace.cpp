#include <vili/parser.hpp>

#include <Debug/Logger.hpp>
#include <System/Path.hpp>
#include <System/Workspace.hpp>

namespace obe::System::Workspace
{
    std::string GetWorkspaceLocation(const std::string& workspaceName)
    {
        if (WorkspaceExists(workspaceName))
        {
            const std::string projectsFileLocation = "obe://Projects.vili"_fs;
            return vili::parser::from_file(projectsFileLocation)
                .at(workspaceName)
                .at("path");
        }
        throw Exceptions::UnknownWorkspace(workspaceName, ListWorkspaces(), EXC_INFO);
    }

    bool WorkspaceExists(const std::string& workspaceName)
    {
        const std::string projectsFileLocation = "obe://Projects.vili"_fs;
        return vili::parser::from_file(projectsFileLocation)
            .contains(workspaceName);
    }

    bool Load(const std::string& workspaceName, const std::string& prefix, const unsigned int priority)
    {
        Debug::Log->info("<Project> Loading Project '{0}' with priority {1}",
            workspaceName, priority);
        if (WorkspaceExists(workspaceName))
        {
            MountablePath::Mount(MountablePath(MountablePathType::Workspace,
                GetWorkspaceLocation(workspaceName), prefix, priority));
            return true;
        }
        throw Exceptions::UnknownWorkspace(workspaceName, ListWorkspaces(), EXC_INFO);
    }

    std::vector<std::string> ListWorkspaces()
    {
        const std::string projectsFileLocation = "obe://Projects.vili"_fs;
        vili::node workspaces = vili::parser::from_file(projectsFileLocation);
        std::vector<std::string> workspacesNames;
        for (auto [workspaceName, _] : workspaces.items())
        {
            workspacesNames.push_back(workspaceName);
        }
        return workspacesNames;
    }
} // namespace obe::System::Workspace