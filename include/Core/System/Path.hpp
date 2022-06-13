#pragma once

#include <System/Exceptions.hpp>
#include <System/MountablePath.hpp>
#include <Types/SmartEnum.hpp>

namespace obe::system
{
    std::pair<std::string, std::string> split_path_and_prefix(
        const std::string& path, bool warn_on_missing_prefix = true);

    enum class PathType
    {
        All,
        Directory,
        File
    };

    using PathTypeMeta = Types::SmartEnum<PathType>;

    /**
     * \brief represents the result of the `find`, `findAll` and `list` operations of Path
     *
     * \loadpriority{11} (before obe::system::Path)
     */
    class FindResult
    {
    private:
        PathType m_type = PathType::All;
        std::shared_ptr<MountablePath> m_mount;
        std::string m_path;
        std::string m_query;
        std::string m_element;
        MountList m_mounts;

        void check_validity() const;

    public:
        FindResult(PathType path_type, const std::string& path_not_found, const std::string& query,
            const MountList& mounts);
        FindResult(PathType path_type, std::shared_ptr<MountablePath> mount, const std::string& path,
            const std::string& query, const std::string& element = "");
        [[nodiscard]] std::string hypothetical_path() const;
        [[nodiscard]] const std::string& path() const;
        [[nodiscard]] const MountablePath& mount() const;
        [[nodiscard]] const std::string& query() const;
        [[nodiscard]] const std::string& element() const;
        [[nodiscard]] bool success() const;
        operator bool() const;
        operator const std::string&() const;
        operator const char*() const;
        operator std::string_view() const;
    };

    /**
     * \brief Class used to manipulate paths and dynamically load resources
     *        (Based on multiple mounted paths)
     * \loadpriority{10}
     * \helper{obe://Lib/Internal/Require.lua}
     * \helper{obe://Lib/Internal/Filesystem.lua}
     */
    class Path
    {
    private:
        std::string m_path;
        std::string m_prefix;
        // TODO: Change to std::span when available
        const MountList* m_mounts;
        MountList m_customMounts;

        static std::unordered_map<std::string, FindResult> PathCache;
        const MountList* copy_mount_source(const Path& path) const;

    public:
        /**
         * \brief Default constructor of Path
         */
        Path();
        /**
         * \brief Build a path with a custom registry of MountablePath that it will be able to search from
         * \param mount A reference containing the mount points the Path should be using
         */
        Path(const MountList& mount);
        /**
         * \brief Build a path from an other path (Copy constructor)
         * \param path The Path to build the new Path from
         */
        Path(const Path& path);
        /**
         * \brief Build a path from a std::string_view
         * \param path Path in std::string_view form
         */
        Path(std::string_view path);
        /**
         * \brief Build a path with explicit prefix
         * \param prefix Prefix in std::string_view form
         * \param path Path in std::string_view form
         */
        Path(std::string_view prefix, std::string_view path);
        /**
         * \brief Replaces Path's value with a new one
         * \param path New value for Path
         */
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
        [[nodiscard]] Path get_path(std::size_t index) const;
        /**
         * \brief Finds the most prioritized file corresponding to the Path
         * \return The full path to the most prioritized file
         */
        [[nodiscard]] std::vector<FindResult> list(PathType path_type = PathType::All) const;
        [[nodiscard]] FindResult find(PathType path_type = PathType::All) const;
        [[nodiscard]] std::vector<FindResult> find_all(PathType path_type = PathType::All) const;
        /**
         * \brief Get the current path in string form
         * \return The Path in std::string form
         */
        [[nodiscard]] std::string to_string() const;
        operator std::string() const;
        Path& operator=(const Path& path);
    };

    class ContextualPathFactory
    {
    private:
        Path m_base;
        MountList make_mount_list(const std::string& base) const;
        MountList make_mount_list(const std::string& base, const MountList& custom_mounts) const;

    public:
        ContextualPathFactory(const std::string& base);
        ContextualPathFactory(const std::string& base, const MountList& custom_mounts);

        Path operator()(const std::string& path) const;
    };
} // namespace obe::system

obe::system::Path operator"" _path(const char* str, std::size_t len);
std::string operator"" _fs(const char* str, std::size_t len);
