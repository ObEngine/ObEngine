#include <vili/parser.hpp>
#include <vld8/exceptions.hpp>
#include <vld8/validator.hpp>

#include <Config/Validators.hpp>
#include <Debug/Logger.hpp>
#include <System/Path.hpp>
#include <System/Project.hpp>

namespace obe::System::Project
{
    std::string GetProjectLocation(const std::string& projectName)
    {
        if (ProjectExists(projectName))
        {
            const std::string projectsFileLocation = "obe://projects.vili"_fs;
            return vili::parser::from_file(projectsFileLocation)
                .at(projectName)
                .at("path");
        }
        throw Exceptions::UnknownProject(projectName, ListProjects(), EXC_INFO);
    }

    bool ProjectExists(const std::string& projectName)
    {
        const std::string projectsFileLocation = "obe://projects.vili"_fs;
        return vili::parser::from_file(projectsFileLocation).contains(projectName);
    }

    bool Load(const std::string& projectName, const std::string& prefix,
        const unsigned int priority)
    {
        Debug::Log->info(
            "<Project> Loading Project '{0}' with priority {1}", projectName, priority);
        if (ProjectExists(projectName))
        {
            MountablePath::Mount(MountablePath(MountablePathType::Project,
                GetProjectLocation(projectName), prefix, priority));
            return true;
        }
        throw Exceptions::UnknownProject(projectName, ListProjects(), EXC_INFO);
    }

    std::vector<std::string> ListProjects()
    {
        const std::string projectsFileLocation = "obe://projects.vili"_fs;
        vili::node projects = vili::parser::from_file(projectsFileLocation);
        std::vector<std::string> projectsNames;
        for (auto [projectName, _] : projects.items())
        {
            projectsNames.push_back(projectName);
        }
        return projectsNames;
    }

    vili::node Project::dump() const
    {
        vili::node mountDump = vili::object {};
        for (const auto& mount : m_mounts)
        {
            // TODO: handle priorities...
            mountDump.emplace(mount->prefix, mount->basePath);
        }

        // clang-format off
        return vili::object {
            { "id", m_id },
            { "name", m_name },
            { "authors", vili::array(m_authors.begin(), m_authors.end()) },
            { "description", m_description },
            { "obengine_version", m_obengineVersion.string() },
            { "keywords", vili::array(m_keywords.begin(), m_keywords.end()) },
            { "categories", vili::array(m_categories.begin(), m_categories.end()) },
            { "license", m_license },
            { "include", vili::array(m_include.begin(), m_include.end()) },
            { "exclude", vili::array(m_exclude.begin(), m_exclude.end()) },
            { "source", m_source },
            { "urls", m_urls.dump() },
            { "mounts", mountDump }
        };
        // clang-format on
    }

    void Project::load(const vili::node& data)
    {
        const auto validator = Config::Validators::ProjectValidator();
        try
        {
            vili::validator::validate_tree(validator, data);
        }
        catch (const vili::exceptions::base_exception& e)
        {
            throw Exceptions::InvalidProjectFile("<?>", EXC_INFO).nest(e);
        }
    }

    void Project::loadFromFile(const std::string& path)
    {
        vili::node project = vili::parser::from_file(path);
        const auto validator = Config::Validators::ProjectValidator();
        try
        {
            vili::validator::validate_tree(validator, project);
        }
        catch (const vili::exceptions::base_exception& e)
        {
            throw Exceptions::InvalidProjectFile(path, EXC_INFO).nest(e);
        }
    }
} // namespace obe::System::Project