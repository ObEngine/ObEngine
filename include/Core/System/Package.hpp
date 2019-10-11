#pragma once

#include <string>

/**
 * \brief Various functions to manipulate Packages
 * @Bind
 */
namespace obe::System::Package
{
    /**
     * \brief Get the Location of the Package identified by packageName
     * \param packageName Name of the Package you want to get the path.
     * \return A std::string containing the path of the retrieved Package.
     */
    std::string GetPackageLocation(const std::string& packageName);
    /**
     * \brief Get if the Package exists or not.
     * \param packageName Name of the Package you want to check the existence.
     * \return true if the Package exists, false otherwise.
     */
    bool PackageExists(const std::string& packageName);
    /**
     * \brief Installs a Package
     * \param packageName Is the name of the .opaque file located in Package/
     * folder (without the .opaque extension) \return true if the Package has
     * been successfully installed, false otherwise
     */
    bool Install(const std::string& packageName);
    /**
     * \brief Load a new Package in the mounted paths
     * \param packageName Name of the Package to load.
     * \param priority Priority of the path that will be mounted.
     * \return true if the Package has been successfully loaded, false
     * otherwise.
     */
    bool Load(const std::string& packageName, unsigned int priority = 1);
} // namespace obe::System::Package