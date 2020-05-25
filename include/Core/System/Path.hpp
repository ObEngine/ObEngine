#pragma once

#include <Debug/Logger.hpp>
#include <System/Exceptions.hpp>
#include <System/Loaders.hpp>
#include <System/MountablePath.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::System
{
    enum class PathType
    {
        All,
        Directory,
        File
    };
    /**
     * \brief Class used to manipulate paths and dynamically load resources
     *        (Based on multiple mounted paths)
     * \bind{Path}
     */
    class Path
    {
    private:
        std::string m_path;
        const std::vector<MountablePath>& m_mounts;

    public:
        /**
         * \brief Default constructor of Path
         */
        Path();
        /**
         * \brief Build a path from an other path (Copy constructor)
         * \param mount A reference containing the mount points the Path should be using
         */
        Path(const std::vector<MountablePath>& mount);
        /**
         * \brief Build a path from an other path (Copy constructor)
         * \param path The Path to build the new Path from
         */
        Path(const Path& path);
        /**
         * \brief Build a path from a std::string
         * \param path Path in std::string form
         */
        Path(std::string_view path);
        Path& set(const std::string& path);
        /**
         * \brief Returns a new Path which is the current one concatenated with
         *        the given string
         * \param path String containing the path part to add
         * \return The new path which is the result of the base concatenated with
         *         the path parameter
         */
        [[nodiscard]] Path add(const std::string& path) const;
        /**
         * \brief Get the last part of a Path
         * \return The last part of the Path (terminal directory)
         */
        [[nodiscard]] std::string last() const;
        /**
         * \brief Build a path using the current path and the BasePath at given
         *        index
         * \param index Index of the BasePath to use
         * \return The full path based on the current path and the BasePath at index
         */
        Path getPath(std::size_t index) const;
        /**
         * \brief Finds the most prioritized file corresponding to the Path
         * \return The full path to the most prioritized file
         */
        [[nodiscard]] std::string find(PathType pathType = PathType::All) const;
        [[nodiscard]] std::vector<std::string> findAll(
            PathType pathType = PathType::All) const;
        /**
         * \brief Get the current path in string form
         * \return The Path in std::string form
         */
        [[nodiscard]] std::string toString() const;

        void operator=(const Path& path);

        template <template <class ResourceType> class LoaderType, class ResourceType>
        LoaderResult load(const LoaderType<ResourceType>& loader, ResourceType& resource,
            bool allowFailure = false) const;

        template <template <class ResourceType> class LoaderType, class ResourceType>
        LoaderMultipleResult loadAll(const LoaderType<ResourceType>& loader,
            ResourceType& resource, bool allowFailure = false) const;
    };

    template <template <class ResourceType> class LoaderType, class ResourceType>
    inline LoaderResult Path::load(const LoaderType<ResourceType>& loader,
        ResourceType& resource, bool allowFailure) const
    {
        for (const MountablePath& mountedPath : m_mounts)
        {
            std::string loadPath = mountedPath.basePath
                + ((!mountedPath.basePath.empty()) ? "/" : "") + this->m_path;
            if (Utils::File::fileExists(loadPath)
                || Utils::File::directoryExists(loadPath))
            {
                Debug::Log->debug("<Path> Loading resource at : {0}", loadPath);
                if (loader.load(resource, loadPath))
                {
                    return LoaderResult(loadPath);
                }
            }
        }
        if (allowFailure)
            return LoaderResult();
        else
            throw Exceptions::ResourceNotFound(
                m_path, MountablePath::StringPaths(), EXC_INFO);
    }

    template <template <class ResourceType> class LoaderType, class ResourceType>
    inline LoaderMultipleResult Path::loadAll(const LoaderType<ResourceType>& loader,
        ResourceType& resource, bool allowFailure) const
    {
        std::vector<std::string> paths;
        for (const MountablePath& mountedPath : m_mounts)
        {
            std::string loadPath = mountedPath.basePath
                + ((!mountedPath.basePath.empty()) ? "/" : "") + this->m_path;
            if (Utils::File::fileExists(loadPath)
                || Utils::File::directoryExists(loadPath))
            {
                Debug::Log->debug("<Path> Loading resource at : {0}", loadPath);
                if (loader.load(resource, loadPath))
                {
                    paths.push_back(loadPath);
                }
            }
        }
        if (!allowFailure && paths.empty())
            throw Exceptions::ResourceNotFound(
                m_path, MountablePath::StringPaths(), EXC_INFO);
        else
            return LoaderMultipleResult(paths);
    }
} // namespace obe::System

obe::System::Path operator"" _path(const char* str, std::size_t len);
std::string operator"" _fs(const char* str, std::size_t len);