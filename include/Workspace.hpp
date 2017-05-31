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
        public:
            static std::string GetWorkspaceLocation(std::string workspaceName);
            static bool WorkspaceExists(std::string workspaceName);
            static bool Load(std::string workspaceName, unsigned int priority = 1);
        };
    }
}
