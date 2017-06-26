#pragma once

#include <string>
#include <vili/Vili.hpp>

#include "PathResolver.hpp"

namespace obe
{
    namespace System
    {
	    /**
         * \brief A Class contained static functions to work with the Workspaces
         */
        namespace Workspace
		{
	        /**
             * \brief Get the Location of the Workspace identified by workspaceName
             * \param workspaceName Name of the Workspace you want to get the path.
             * \return A std::string containing the path of the retrieved Workspace.
             */
            std::string GetWorkspaceLocation(const std::string& workspaceName);
	        /**
             * \brief Get if the Workspace exists or not.
             * \param workspaceName Name of the Workspace you want to check the existence.
             * \return true if the Workspace exists, false otherwise.
             */
            bool WorkspaceExists(const std::string& workspaceName);
	        /**
             * \brief Load a new Workspace in the mounted paths
             * \param workspaceName Name of the Workspace to load.
             * \param priority Priority of the path that will be mounted.
             * \return true if the Workspace has been successfully loaded, false otherwise.
             */
            bool Load(const std::string& workspaceName, unsigned int priority = 1);
        }
    }
}