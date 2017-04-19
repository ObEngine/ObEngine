#include "Workspace.hpp"

namespace obe
{
	namespace System
	{
		std::string Workspace::GetWorkspaceLocation(std::string workspaceName)
		{
			if (WorkspaceExists(workspaceName))
				return (vili::DataParser("Workspace/Workspaces.vili")->at<vili::BaseAttribute>(workspaceName, "path")->get<std::string>());
			throw aube::ErrorHandler::Raise("ObEngine.Workspace.Workspace.InexistantWorkspace", { {"workspace", workspaceName} });
		}

		bool Workspace::WorkspaceExists(std::string workspaceName)
		{
			return (vili::DataParser("Workspace/Workspaces.vili")->contains(vili::Types::ComplexAttribute, workspaceName));
		}

		bool Workspace::Load(std::string workspaceName, unsigned int priority)
		{
			if (WorkspaceExists(workspaceName)) {
				Path::addPath(obe::System::PriorizedPath(obe::System::PathType::Workspace, GetWorkspaceLocation(workspaceName), priority));
				std::cout << "<System> Mounting Workspace : " << workspaceName << " : " << GetWorkspaceLocation(workspaceName) << std::endl;
				return true;
			}
			throw aube::ErrorHandler::Raise("ObEngine.Workspace.Workspace.InexistantWorkspace", { { "workspace", workspaceName } });
		}
	}
}
