#include <Bindings/obe/System/Project/Project.hpp>

#include <System/Project.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::project::Bindings
{
    void LoadClassProject(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["system"]["project"].get<sol::table>();
        sol::usertype<obe::system::project::Project> bindProject
            = ProjectNamespace.new_usertype<obe::system::project::Project>("project",
                sol::call_constructor, sol::constructors<obe::system::project::Project()>());
        bindProject["dump"] = &obe::system::project::Project::dump;
        bindProject["load"] = &obe::system::project::Project::load;
        bindProject["load_from_file"] = &obe::system::project::Project::load_from_file;
        bindProject["mount"] = &obe::system::project::Project::mount;
        bindProject["unmount"] = &obe::system::project::Project::unmount;
        bindProject["get_id"] = &obe::system::project::Project::get_id;
        bindProject["is_standalone"] = &obe::system::project::Project::is_standalone;
    }
    void LoadClassProjectURLs(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["system"]["project"].get<sol::table>();
        sol::usertype<obe::system::project::ProjectURLs> bindProjectURLs
            = ProjectNamespace.new_usertype<obe::system::project::ProjectURLs>(
                "ProjectURLs", sol::call_constructor, sol::default_constructor);
        bindProjectURLs["dump"] = &obe::system::project::ProjectURLs::dump;
        bindProjectURLs["load"] = &obe::system::project::ProjectURLs::load;
        bindProjectURLs["homepage"] = &obe::system::project::ProjectURLs::homepage;
        bindProjectURLs["issues"] = &obe::system::project::ProjectURLs::issues;
        bindProjectURLs["readme"] = &obe::system::project::ProjectURLs::readme;
        bindProjectURLs["documentation"] = &obe::system::project::ProjectURLs::documentation;
        bindProjectURLs["license"] = &obe::system::project::ProjectURLs::license;
    }
    void LoadFunctionGetProjectLocation(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["system"]["project"].get<sol::table>();
        ProjectNamespace.set_function(
            "get_project_location", &obe::system::project::get_project_location);
    }
    void LoadFunctionProjectExists(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["system"]["project"].get<sol::table>();
        ProjectNamespace.set_function("project_exists", &obe::system::project::project_exists);
    }
    void LoadFunctionLoad(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["system"]["project"].get<sol::table>();
        ProjectNamespace.set_function("load",
            sol::overload([](const std::string& projectName, const std::string& prefix)
                              -> bool { return obe::system::project::load(projectName, prefix); },
                [](const std::string& projectName, const std::string& prefix, unsigned int priority)
                    -> bool { return obe::system::project::load(projectName, prefix, priority); }));
    }
    void LoadFunctionListProjects(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["system"]["project"].get<sol::table>();
        ProjectNamespace.set_function("list_projects", &obe::system::project::list_projects);
    }
};