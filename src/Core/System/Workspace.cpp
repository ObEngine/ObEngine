#include <vili/Vili.hpp>

#include <Debug/Logger.hpp>
#include <System/MountablePath.hpp>
#include <System/Path.hpp>
#include <System/Workspace.hpp>

namespace obe::System::Workspace
{
    std::string GetWorkspaceLocation(const std::string& workspaceName)
    {
        if (WorkspaceExists(workspaceName))
            return (vili::ViliParser("Workspace/Workspaces.vili")
                        ->at<vili::DataNode>(workspaceName, "path")
                        .get<std::string>());
        throw aube::ErrorHandler::Raise(
            "ObEngine.Workspace.Workspace.InexistantWorkspace", { { "workspace", workspaceName } });
    }

    bool WorkspaceExists(const std::string& workspaceName)
    {
        return (vili::ViliParser("Workspace/Workspaces.vili")
                    ->contains(vili::NodeType::ComplexNode, workspaceName));
    }

    bool Load(const std::string& workspaceName, const unsigned int priority)
    {
        Debug::Log->info(
            "<Workspace> Loading Workspace '{0}' with priority {1}", workspaceName, priority);
        if (WorkspaceExists(workspaceName))
        {
            Path::Mount(MountablePath(
                MountablePathType::Workspace, GetWorkspaceLocation(workspaceName), priority));
            return true;
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.System.Workspace.InexistantWorkspace", { { "workspace", workspaceName } });
    }
} // namespace obe::System::Workspace