#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace obe::system
{
    namespace prefixes
    {
        constexpr std::string_view obe = "obe";
        constexpr std::string_view cwd = "cwd";
        constexpr std::string_view exe = "exe";
        constexpr std::string_view cfg = "cfg";
        constexpr std::string_view mount = "mount";
        constexpr std::string_view extlibs = "extlibs";
        constexpr std::string_view intlibs = "intlibs";
        constexpr std::string_view root = "root";
        constexpr std::string_view game = "game";
    } // namespace prefixes

    /**
     * \brief contains default priorities of mounts
     *
     * High-priority user defined(>5) > High-priority(5) > ProjectMount(4) > Project(3) > Mount(2) > Defaults(1) > Low-priority(0) > Low-priority user defined(<0)
     */
    namespace priorities
    {
        constexpr int high = 5;
        constexpr int projectmount = 4;
        constexpr int project = 3;
        constexpr int mount = 2;
        constexpr int defaults = 1;
        constexpr int low = 0;
    } // namespace priorities

    /**
     * \brief Defines the source of a mounted path
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

    /**
     * \brief action to take whenever two MountablePath with the same prefix are mounted
     */
    enum class SamePrefixPolicy
    {
        /**
         * \brief keep both MountablePath with the same prefix
         */
        KeepBoth,
        /**
         * \brief discard the new MountablePath
         */
        Skip,
        /**
         * \brief discard the old MountablePath
         */
        Replace
    };

    class MountablePath;
    using MountList = std::vector<std::shared_ptr<MountablePath>>;
    /**
     * \brief Class used to encapsulate mounted Paths
     *
     * \loadpriority{12} (before obe::system::Path)
     */
    class MountablePath
    {
    private:
        static MountList MountedPaths;

        static void mount_additional_prefixes();

    public:
        /**
         * \brief Constructor of MountablePath
         * \param path_type Type of the mounted path
         * \param base_path Path to the mounted path
         * \param prefix
         * \param priority Priority of the mounted path
         * \param implicit is taken into account when no prefix is provided
         * \param defer_resolution whether or not to resolve base_path on construction
         */
        MountablePath(MountablePathType path_type, std::string_view base_path,
            std::string_view prefix, unsigned int priority = 0, bool implicit = false,
            bool defer_resolution = false);
        /**
         * \brief Type of the mounted path
         */
        MountablePathType path_type;
        /**
         * \brief Path of the mounted path
         */
        std::string base_path;
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

        /**
         * \brief Allows to defer base_path resolution to a later time
         */
        bool deferred_resolution = false;

        bool operator==(const MountablePath& other) const;

    public:
        /**
         * \brief Function called to Mount all Paths using 'mount.vili' file
         */
        static void load_mount_file(
            bool from_cwd = true, bool from_exe = true, const std::string& project_override = "");
        /**
         * \brief Add a Path to Mounted Paths
         * \param path Path to mount
         * \param same_prefix_policy action to take whenever two or more MountablePath with the same prefix are found
         */
        static void mount(
            MountablePath path, SamePrefixPolicy same_prefix_policy = SamePrefixPolicy::KeepBoth);
        /**
         * \brief Remove a Path from Mounted Paths
         * \param path Path to unmount
         */
        static void unmount(MountablePath path);
        /**
         * \brief Remove all Paths from Mounted Paths
         */
        static void unmount_all();
        /**
         * \brief All the Mounted Paths
         */
        static const MountList& paths();
        /**
         * \brief All the Mounted Paths as strings
         */
        static std::vector<std::string> string_paths();
        /**
         * \brief Sort the mounted paths based on their priorities
         */
        static void sort();
        /**
         * \brief Retrieve a MountablePath based on the prefix
         */
        static const MountablePath& from_prefix(const std::string& prefix);

        static std::vector<std::string> get_all_prefixes();

        void resolve_base_path();
    };
} // namespace obe::system
