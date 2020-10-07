#pragma once

#include <Debug/Logger.hpp>
#include <System/Exceptions.hpp>
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

    class FindResult
    {
    private:
        PathType m_type = PathType::All;
        std::string m_root;
        std::string m_path;
        std::string m_element;

        void checkValidity() const;

    public:
        FindResult(const std::string& pathNotFound);
        FindResult(PathType pathType, const std::string& root, const std::string& path,
            const std::string& element);
        [[nodiscard]] const std::string& path() const;
        [[nodiscard]] const std::string& root() const;
        [[nodiscard]] const std::string& element() const;
        [[nodiscard]] bool success() const;
        operator bool() const;
        operator const std::string &() const;
        operator const char*() const;
        operator std::string_view() const;
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

        static std::unordered_map<std::string, FindResult> PathCache;

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
        [[nodiscard]] std::vector<FindResult> list(
            PathType pathType = PathType::All) const;
        [[nodiscard]] FindResult find(PathType pathType = PathType::All) const;
        [[nodiscard]] std::vector<FindResult> findAll(
            PathType pathType = PathType::All) const;
        /**
         * \brief Get the current path in string form
         * \return The Path in std::string form
         */
        [[nodiscard]] std::string toString() const;

        void operator=(const Path& path);
    };
} // namespace obe::System

obe::System::Path operator"" _path(const char* str, std::size_t len);
std::string operator"" _fs(const char* str, std::size_t len);