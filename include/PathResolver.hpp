#pragma once

#include <string>
#include <typeinfo>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <kaguya/kaguya.hpp>
#include <vili/Vili.hpp>

#include "FileFunctions.hpp"
#include "Functions.hpp"
#include "Package.hpp"
#include "Workspace.hpp"

namespace obe
{
    namespace System
    {
	    /**
         * \brief Lambdas used to load different kind of resources using the System::Path
         */
        namespace Loaders
        {
	        /**
             * \brief Load a sf::Texture from a file
             */
            extern std::function<int(sf::Texture*, std::string)> textureLoader;
	        /**
             * \brief Load a vili::DataParser from a file
             */
            extern std::function<int(vili::DataParser*, std::string)> dataLoader;
	        /**
             * \brief Load a sf::Font from a file
             */
            extern std::function<int(sf::Font*, std::string)> fontLoader;
	        /**
             * \brief List all folders in the specified path
             */
            extern std::function<int(std::vector<std::string>*, std::string)> dirPathLoader;
	        /**
             * \brief List all files in the specified path
             */
            extern std::function<int(std::vector<std::string>*, std::string)> filePathLoader;
	        /**
             * \brief Load the Lua source from a file
             */
            extern std::function<int(kaguya::State*, std::string)> luaLoader;
	        /**
             * \brief Load a sf::SoundBuffer from a file
             */
            extern std::function<int(sf::SoundBuffer*, std::string)> soundLoader;
	        /**
             * \brief Load a sf::Music from a file
             */
            extern std::function<int(sf::Music*, std::string)> musicLoader;
        }

	    /**
            * \brief Defines the source of a mounted path
            */
        enum class PathType
        {
	        /**
                * \brief A standard path
                */
            Path,
	        /**
                * \brief The mounted path is a Package
                */
            Package,
	        /**
                * \brief The mounted path is a Workspace
                */
            Workspace
        };

	    /**
         * \brief Class used to encapsulate mounted Paths
         */
        class PriorizedPath
        {
        public:
	        /**
             * \brief Constructor of PriorizedPath
             * \param pathType Type of the mounted path
             * \param basePath Path to the mounted path
             * \param priority Priority of the mounted path
             */
            PriorizedPath(PathType pathType, const std::string& basePath, unsigned int priority = 0);
	        /**
             * \brief Type of the mounted path
             */
            PathType pathType;
	        /**
             * \brief Path of the mounted path
             */
            std::string basePath;
	        /**
             * \brief Priority of the mounted path (Higher priority means overriding lower priority Paths)
             */
            unsigned int priority;
        };

	    /**
         * \brief Class used to manipulate paths and dynamically load resources (Based on multiple mounted paths)
         */
        class Path
        {
        private:
            std::string m_path;
            static void orderPriorizedPaths();
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
            static void addPath(PriorizedPath path);
	        /**
             * \brief All the Mounted Paths
             */
            static std::vector<PriorizedPath> basePaths;
	        /**
             * \brief Access Mounted Paths
             * \return All the Mounted Paths
             */
            static std::vector<PriorizedPath>& Paths();
        };

	    /**
         * \brief Function called to Mount all Paths using 'Mount.vili' file
         */
        void MountPaths();

        template <typename R, typename F>
        std::string Path::loadResource(R* resource, F lambda, bool silent) const
        {
            int loadSum = 0;
            for (int i = 0; i < basePaths.size(); i++)
            {
                int loadResponse = 0;
                if (Functions::File::fileExists(basePaths[i].basePath + ((basePaths[i].basePath != "") ? "/" : "") + this->m_path))
                {
                    loadResponse = lambda(resource, basePaths[i].basePath + ((basePaths[i].basePath != "") ? "/" : "") + this->m_path);
                }

                loadSum += loadResponse;
                if (loadResponse == 1)
                    return basePaths[i].basePath;
            }
            if (loadSum > 0)
                return "*";
            throw aube::ErrorHandler::Raise("ObEngine.PathResolverHeader.Path.CantFindResource", {{"path", m_path}});
        }
    }
}
