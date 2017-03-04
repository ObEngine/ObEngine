#pragma once

#include <string>
#include <vili/Vili.hpp>

#include "PathResolver.hpp"

namespace obe
{
	namespace System
	{
		class Workspace
		{
			private:
				static std::string GetWorkspaceLocation(std::string workspaceName);
				static bool WorkspaceExists(std::string workspaceName);
			public:
				static bool Load(std::string workspaceName, unsigned int priority = 1);
		};
	}
}
