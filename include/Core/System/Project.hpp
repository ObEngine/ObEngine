#pragma once

#include <string>
#include <vector>

/**
 * \brief Various functions to work with Projects
 */
namespace obe::System::Project
{
    /**
     * \brief Get the Location of the Project identified by projectName
     * \param projectName Name of the Project you want to get the path.
     * \return A std::string containing the path of the retrieved Project.
     */
    std::string GetProjectLocation(const std::string& projectName);
    /**
     * \brief Get if the Project exists or not.
     * \param projectName Name of the Project you want to check the
     *        existence.
     * \return true if the Project exists, false otherwise.
     */
    bool ProjectExists(const std::string& projectName);
    /**
     * \brief Load a new Project in the mounted paths
     * \param projectName Name of the Project to load.
     * \param prefix Prefix that can be used to reference Project root path
     * \param priority Priority of the path that will be mounted.
     * \return true if the Project has been successfully loaded, false
     *         otherwise.
     */
    bool Load(const std::string& projectName, const std::string& prefix,
        unsigned int priority = 1);
    std::vector<std::string> ListProjects();
} // namespace obe::System::Project
