#include <vili/parser.hpp>

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
} // namespace obe::System::Project