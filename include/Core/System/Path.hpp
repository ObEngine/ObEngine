#pragma once

#include <vili/ErrorHandler.hpp>

#include <Debug/Logger.hpp>
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
    * \brief Class used to manipulate paths and dynamically load resources (Based on multiple mounted paths)
    * @Bind
    */
    class Path
    {
    private:
        std::string m_path;
        static void orderMountedPaths();
    public:
        /**
        * \brief Default constructor of Path
        */
        Path();
        /**
        * \brief Build a path from an other path (Copy constructor)
        * \param path The Path to build the new Path from
        */
        Path(const Path& path);
        /**
        * \brief Build a path from a std::string
        * \param path Path in std::string form
        */
        Path(const std::string& path);
        /**
        * \brief Returns a new Path which is the current one concatened with the given string
        * \param path String containing the path part to add
        * \return The new path which is the result of the base concatened with the path parameter
        */
        Path add(const std::string& path) const;
        /**
        * \brief Get the last part of a Path
        * \return The last part of the Path (terminal directory)
        */
        std::string last() const;
        /**
        * \brief Build a path using the current path and the BasePath at given index
        * \param index Index of the BasePath to use
        * \return The full path based on the current path and the BasePath at index
        */
        Path getPath(unsigned int index);
        /*
        * \brief Finds the most priorized file corresponding to the Path
        * \return The full path to the most priorized file
        */
        std::string find(PathType pathType = PathType::All) const;
        /**
        * \brief Get the current path in string form
        * \return The Path in std::string form
        */
        std::string toString() const;
        /**
        * \brief 
        * \tparam R Pointer where the resource will be loaded
        * \tparam F Loader which is a lambda (Called if the file is found to load the resource)
        * \param resource Pointer where the resource will be loaded
        * \param lambda Loader which is a lambda (Called if the file is found to load the resource)
        * \return The Path used to load the resource in std::string form
        */
        template <typename R, typename F>
        std::string loadResource(R* resource, F lambda, bool allowFailure = false) const;
        /**
        * \brief Add a Path to Mounted Paths
        * \param path Path to mount
        */
        static void Mount(MountablePath path);
        /**
        * \brief All the Mounted Paths
        */
        static std::vector<MountablePath> MountedPaths;
        /**
        * \brief Access Mounted Paths
        * \return All the Mounted Paths
        */
        static std::vector<MountablePath>& Paths();
    };

    template <typename R, typename F>
    std::string Path::loadResource(R* resource, F lambda, bool allowFailure) const
    {
        int loadSum = 0;
        for (MountablePath& mountedPath : MountedPaths)
        {
            int loadResponse = 0;
            std::string loadPath = mountedPath.basePath + ((mountedPath.basePath != "") ? "/" : "") + this->m_path;
            if (Utils::File::fileExists(loadPath) || Utils::File::directoryExists(loadPath))
            {
                Debug::Log->debug("<Path> Loading resource at : {0}", loadPath);
                loadResponse = lambda(resource, loadPath);
            }

            loadSum += loadResponse;
            if (loadResponse == 1)
                return mountedPath.basePath;
        }
        if (loadSum > 0)
            return "*";
		if (!allowFailure)
			throw aube::ErrorHandler::Raise("ObEngine.System.Path.CantFindResource", { {"path", m_path} });
		else
			return "";
    }
}