#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace obe::System
{
    namespace Prefixes
    {
        constexpr std::string_view obe = "obe";
        constexpr std::string_view cwd = "cwd";
        constexpr std::string_view exe = "exe";
        constexpr std::string_view cfg = "cfg";
        constexpr std::string_view base = "base";
        constexpr std::string_view extlibs = "extlibs";
    }

    /**
     * \brief Defines the source of a mounted path
     * \bind{MountablePathType}
     */
    enum class MountablePathType
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
         * \brief The mounted path is a Project
         */
        Project
    };

    class MountablePath;
    using MountList = std::vector<std::shared_ptr<MountablePath>>;
    /**
     * \brief Class used to encapsulate mounted Paths
     */
    class MountablePath
    {
    private:
        static MountList MountedPaths;

    public:
        /**
         * \brief Constructor of MountablePath
         * \param pathType Type of the mounted path
         * \param basePath Path to the mounted path
         * \param priority Priority of the mounted path
         */
        MountablePath(MountablePathType pathType, std::string_view basePath,
            std::string_view prefix, unsigned int priority = 0, bool implicit = true);
        /**
         * \brief Type of the mounted path
         */
        MountablePathType pathType;
        /**
         * \brief Path of the mounted path
         */
        std::string basePath;
        /**
         * \brief Prefix of the mounted path
         */
        std::string prefix;
        /**
         * \brief Priority of the mounted path (Higher priority means overriding
         *        lower priority Paths)
         */
        unsigned int priority;
        /**
         * \brief Allows the path to be used implicitly (without prefix)
         */
        bool implicit;

        bool operator==(const MountablePath& other) const;

    public:
        /**
         * \brief Function called to Mount all Paths using 'mount.vili' file
         */
        static void LoadMountFile(bool fromCWD = true, bool fromExe = true);
        /**
         * \brief Add a Path to Mounted Paths
         * \param path Path to mount
         */
        static void Mount(MountablePath path);
        /**
         * \brief Remove a Path from Mounted Paths
         * \param path Path to unmount
         */
        static void Unmount(MountablePath path);
        /**
         * \brief Remove all Paths from Mounted Paths
         */
        static void UnmountAll();
        /**
         * \brief All the Mounted Paths
         */
        static const MountList& Paths();
        /**
         * \brief All the Mounted Paths as strings
         */
        static std::vector<std::string> StringPaths();
        /**
         * \brief Sort the mounted paths based on their priorities
         */
        static void Sort();
        /**
         * \brief Retrieve a MountablePath based on the prefix
         */
        static const MountablePath& FromPrefix(const std::string& prefix);

        static const std::vector<std::string> GetAllPrefixes();
    };
} // namespace obe::System