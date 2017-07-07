#pragma once

#include <vili/ErrorHandler.hpp>

#include <System/MountablePath.hpp>
#include <Utils/FileUtils.hpp>

namespace obe
{
    namespace System
    {
        /**
         * \brief Class used to manipulate paths and dynamically load resources (Based on multiple mounted paths)
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
	        explicit Path(const std::string& path);
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
            Path getPath(int index);
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
             * \param silent Defines the verbosity of the resource loading (false = verbose)
             * \return The Path used to load the resource in std::string form
             */
            template <typename R, typename F>
            std::string loadResource(R* resource, F lambda, bool silent = false) const;
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
        std::string Path::loadResource(R* resource, F lambda, bool silent) const
        {
            int loadSum = 0;
            for (MountablePath& mountedPath : MountedPaths)
            {
                int loadResponse = 0;
                if (Utils::File::fileExists(mountedPath.basePath + ((mountedPath.basePath != "") ? "/" : "") + this->m_path))
                {
                    loadResponse = lambda(resource, mountedPath.basePath + ((mountedPath.basePath != "") ? "/" : "") + this->m_path);
                }

                loadSum += loadResponse;
                if (loadResponse == 1)
                    return mountedPath.basePath;
            }
            if (loadSum > 0)
                return "*";
            throw aube::ErrorHandler::Raise("ObEngine.PathResolverHeader.Path.CantFindResource", {{"path", m_path}});
        }
    }
}