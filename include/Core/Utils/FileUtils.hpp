#pragma once

#include <string>
#include <vector>

/**
 * \brief Various functions related to filesystem manipulation
 */
namespace obe::Utils::File
{
    /**
     * \brief Get a list of directories
     * \param path Path where you want to check the directories
     * \return A std::vector of std::string containing the name of all
     *         directories at the given path
     */
    std::vector<std::string> get_directory_list(const std::string& path);
    /**
     * \brief Get a list of files
     * \param path Path where you want to check the files
     * \return A std::vector of std::string containing the name of all files at
     *         the given path
     */
    std::vector<std::string> get_file_list(const std::string& path);
    /**
     * \brief Check if the file at the given path exists
     * \param path Path of the file you want to check the existence
     * \return true if the file has been found, false otherwise
     */
    bool file_exists(const std::string& path);
    /**
     * \brief Check if the directory at the given path exists
     * \param path Path of the directory you want to check the existence
     * \return true if the directory has been found, false otherwise
     */
    bool directory_exists(const std::string& path);
    /**
     * \brief Creates a directory at the given path
     * \param path Path of the directory you want to create
     * \return true if the creation is successful, false otherwise
     */
    bool create_directory(const std::string& path);
    /**
     * \brief Create an empty file at the given path
     * \param path Path of the empty file you want to create
     */
    void create_file(const std::string& path);
    /**
     * \brief Copy a file
     * \param source Path of the file you want to copy
     * \param target Path of the new copy
     */
    void copy(const std::string& source, const std::string& target);
    /**
     * \brief Deletes a file
     * \param path Path of the file you want to delete
     * \return true if the file has been successfully deleted, false otherwise
     */
    bool delete_file(const std::string& path);
    /**
     * \brief Deletes an empty directory
     * \param path Path of of the directory you want to delete
     * \return true if the directory has been successfully deleted, false
     *         otherwise
     */
    bool delete_directory(const std::string& path);

    /**
     * \brief Get the Current Working Directory (CWD)
     * \return A std::string containing the Current Working Directory
     */
    std::string get_current_directory();
    /**
     * \brief Returns the path separator of the current OS
     * \return A std::string containing the Path separator used by the Operating
     *         System
     */
    std::string separator();

    /**
     * \brief Returns the path to the directory of the current executable
     * \return A std::string containing the path to the directory of the current executable
     */
    std::string get_executable_directory();
    /**
     * \brief Returns the path of the current executable
     * \return A std::string containing the path of the current executable
     */
    std::string get_executable_path();
    /**
     * \brief Normalizes the path given in argument
              (replaces every separator with a forward slash)
     * \param path Path to normalize
     * \return Normalized path
     */
    std::string normalize_path(const std::string& path);

    std::string canonical_path(const std::string& path);

    std::string join(const std::vector<std::string> parts);
} // namespace obe::Utils::File
