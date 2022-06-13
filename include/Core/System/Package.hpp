#pragma once

#include <string>
#include <vector>

/**
 * \brief Various functions to manipulate Packages
 */
namespace obe::system::package
{
    /**
     * \brief Get the Location of the Package identified by package_name
     * \param package_name Name of the Package you want to get the path.
     * \return A std::string containing the path of the retrieved Package.
     */
    std::string get_package_location(const std::string& package_name);
    /**
     * \brief Get if the Package exists or not.
     * \param package_name Name of the Package you want to check the existence.
     * \return true if the Package exists, false otherwise.
     */
    bool package_exists(const std::string& package_name);
    std::vector<std::string> list_packages();
    /**
     * \brief Installs a Package
     * \param package_name Is the name of the .opaque file located in Package/
     *        folder (without the .opaque extension)
     * \return true if the Package has
     *         been successfully installed, false otherwise
     */
    bool install(const std::string& package_name);
    /**
     * \brief Load a new Package in the mounted paths
     * \param package_name Name of the Package to load.
     * \param prefix Prefix that can be used to reference Package root path
     * \param priority Priority of the path that will be mounted.
     * \return true if the Package has been successfully loaded, false
     *         otherwise.
     */
    bool load(const std::string& package_name, const std::string& prefix, unsigned int priority = 1);
} // namespace obe::system::package
