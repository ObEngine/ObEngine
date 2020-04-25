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
        {
            return (vili::ViliParser("Workspace/Workspaces.vili")
                        ->at<vili::DataNode>(workspaceName, "path")
                        .get<std::string>());
        }
        throw Exceptions::UnknownWorkspace(workspaceName, ListWorkspaces(), EXC_INFO);
    }

    bool WorkspaceExists(const std::string& workspaceName)
    {
        return (vili::ViliParser("Workspace/Workspaces.vili")
                    ->contains(vili::NodeType::ComplexNode, workspaceName));
    }

    bool Load(const std::string& workspaceName, const unsigned int priority)
    {
        Debug::Log->info("<Workspace> Loading Workspace '{0}' with priority {1}",
            workspaceName, priority);
        if (WorkspaceExists(workspaceName))
        {
            MountablePath::Mount(MountablePath(MountablePathType::Workspace,
                GetWorkspaceLocation(workspaceName), priority));
            return true;
        }
        throw Exceptions::UnknownWorkspace(workspaceName, ListWorkspaces(), EXC_INFO);
    }

    std::vector<std::string> ListWorkspaces()
    {
        const vili::ViliParser workspaces("Workspace/Workspaces.vili");
        auto nodes = workspaces->getAll(vili::NodeType::ComplexNode);
        std::vector<std::string> workspacesNames;
        std::transform(nodes.begin(), nodes.end(), std::back_inserter(workspacesNames),
            [](const vili::Node* node) { return node->getId(); });
        return workspacesNames;
    }
} // namespace obe::System::Workspace