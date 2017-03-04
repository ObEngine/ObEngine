#include "Workspace.hpp"

namespace obe
{
	namespace System
	{
		std::string Workspace::GetWorkspaceLocation(std::string workspaceName)
		{
			if (WorkspaceExists(workspaceName)) {
				return (vili::DataParser("Workspace/Workspaces.vili")->at<vili::BaseAttribute>(workspaceName, "path")->get<std::string>());
			}
			else {
				std::cout << "<Error:Workspace:Workspace>[GetWorkspaceLocation] : Workspace <" << workspaceName << "> does not exists" << std::endl;
			}
			return std::string();
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
			else {
				std::cout << "<Error:Workspace:Workspace>[Load] : Workspace <" << workspaceName << "> does not exists" << std::endl;
				return false;
			}
		}
	}
}
