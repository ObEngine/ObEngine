#pragma once

namespace obe
{
    namespace System
    {
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
        class MountablePath
        {
        public:
	        /**
             * \brief Constructor of MountablePath
             * \param pathType Type of the mounted path
             * \param basePath Path to the mounted path
             * \param priority Priority of the mounted path
             */
            MountablePath(PathType pathType, const std::string& basePath, unsigned int priority = 0);
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
         * \brief Function called to Mount all Paths using 'Mount.vili' file
         */
        void MountPaths();
    }
}