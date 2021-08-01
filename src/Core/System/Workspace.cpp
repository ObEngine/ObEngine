#include <vili/parser.hpp>

#include <System/Path.hpp>
#include <System/Workspace.hpp>

namespace obe::System::Workspace
{
    std::string GetWorkspaceLocation(const std::string& workspaceName)
    {
        if (WorkspaceExists(workspaceName))
        {
            return vili::parser::from_file("Workspace/Workspaces.vili")
                .at(workspaceName)
                .at("path");
        }
        throw Exceptions::UnknownWorkspace(workspaceName, ListWorkspaces(), EXC_INFO);
    }

    bool WorkspaceExists(const std::string& workspaceName)
    {
        return vili::parser::from_file("Workspace/Workspaces.vili")
            .contains(workspaceName);
    }

    bool Load(const std::string& workspaceName, const std::string& prefix, const unsigned int priority)
    {
        Debug::Log->info("<Workspace> Loading Workspace '{0}' with priority {1}",
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
        vili::node workspaces = vili::parser::from_file("Workspace/Workspaces.vili");
        std::vector<std::string> workspacesNames;
        for (auto [workspaceName, _] : workspaces.items())
        {
            workspacesNames.push_back(workspaceName);
        }
        return workspacesNames;
    }
} // namespace obe::System::Workspace