#pragma once

#include <set>
#include <string>
#include <vector>

#include <Config/Version.hpp>
#include <System/MountablePath.hpp>
#include <Types/Serializable.hpp>

/**
 * \brief Various functions to work with Projects
 */
namespace obe::System::Project
{
    namespace Prefixes
    {
        constexpr std::string_view objects = "objects";
        constexpr std::string_view scenes = "scenes";
    }
    /**
     * \brief Get the Location of the Project identified by projectName
     * \param projectName Name of the Project you want to get the path.
     * \return A std::string containing the path of the retrieved Project.
     */
    std::string GetProjectLocation(const std::string& projectName);
    /**
     * \brief Get if the Project exists or not.
     * \param projectName Name of the Project you want to check the
     *        existence.
     * \return true if the Project exists, false otherwise.
     */
    bool ProjectExists(const std::string& projectName);
    /**
     * \brief Load a new Project in the mounted paths
     * \param projectName Name of the Project to load.
     * \param prefix Prefix that can be used to reference Project root path
     * \param priority Priority of the path that will be mounted.
     * \return true if the Project has been successfully loaded, false
     *         otherwise.
     */
    bool Load(const std::string& projectName, const std::string& prefix,
        unsigned int priority = Priorities::project);
    std::vector<std::string> ListProjects();

    class ProjectURLs : Types::Serializable
    {
    public:
        std::string homepage;
        std::string issues;
        std::string readme;
        std::string documentation;
        std::string license;


        [[nodiscard]] vili::node schema() const override;
        /**
         * \brief Dumps the content of the Project URLs to a vili node
         */
        [[nodiscard]] vili::node dump() const override;
        /**
         * \brief Loads a Project URLs from a vili node
         * \param data vili node containing the data of the Project URLs
         */
        void load(const vili::node& data) override;
    };

    class Project : Types::Serializable
    {
    private:
        std::string m_id;
        config::Version m_obengineVersion;

        std::vector<std::string> m_include;
        std::vector<std::string> m_exclude;

        std::string m_source;
        bool m_standalone = false;

        // Metadata
        std::string m_name;
        std::string m_version;
        std::vector<std::string> m_authors;
        std::string m_description;
        std::set<std::string> m_keywords;
        std::set<std::string> m_categories;
        std::string m_license;
        ProjectURLs m_urls;
        MountList m_mounts;

    protected:
        void mountDefaults();

    public:
        Project();
        [[nodiscard]] vili::node schema() const override;
        /**
         * \brief Dumps the content of the Project to a vili node
         */
        [[nodiscard]] vili::node dump() const override;
        /**
         * \brief Loads a Project from a vili node
         * \param data vili node containing the data of the Project
         */
        void load(const vili::node& data) override;

        void loadFromFile(const std::string& path);

        void mount();
        void unmount();

        [[nodiscard]] std::string getId() const;
        [[nodiscard]] bool isStandalone() const;
    };
} // namespace obe::System::Project
