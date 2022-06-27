#include <Bindings/obe/system/project/Project.hpp>

#include <System/Project.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::project::bindings
{
    void load_class_project(sol::state_view state)
    {
        sol::table project_namespace = state["obe"]["system"]["project"].get<sol::table>();
        sol::usertype<obe::system::project::Project> bind_project
            = project_namespace.new_usertype<obe::system::project::Project>("Project",
                sol::call_constructor, sol::constructors<obe::system::project::Project()>());
        bind_project["schema"] = &obe::system::project::Project::schema;
        bind_project["dump"] = &obe::system::project::Project::dump;
        bind_project["load"] = &obe::system::project::Project::load;
        bind_project["load_from_file"] = &obe::system::project::Project::load_from_file;
        bind_project["mount"] = &obe::system::project::Project::mount;
        bind_project["unmount"] = &obe::system::project::Project::unmount;
        bind_project["get_id"] = &obe::system::project::Project::get_id;
        bind_project["is_standalone"] = &obe::system::project::Project::is_standalone;
    }
    void load_class_project_ur_ls(sol::state_view state)
    {
        sol::table project_namespace = state["obe"]["system"]["project"].get<sol::table>();
        sol::usertype<obe::system::project::ProjectURLs> bind_project_ur_ls
            = project_namespace.new_usertype<obe::system::project::ProjectURLs>(
                "ProjectURLs", sol::call_constructor, sol::default_constructor);
        bind_project_ur_ls["schema"] = &obe::system::project::ProjectURLs::schema;
        bind_project_ur_ls["dump"] = &obe::system::project::ProjectURLs::dump;
        bind_project_ur_ls["load"] = &obe::system::project::ProjectURLs::load;
        bind_project_ur_ls["homepage"] = &obe::system::project::ProjectURLs::homepage;
        bind_project_ur_ls["issues"] = &obe::system::project::ProjectURLs::issues;
        bind_project_ur_ls["readme"] = &obe::system::project::ProjectURLs::readme;
        bind_project_ur_ls["documentation"] = &obe::system::project::ProjectURLs::documentation;
        bind_project_ur_ls["license"] = &obe::system::project::ProjectURLs::license;
    }
    void load_function_get_project_location(sol::state_view state)
    {
        sol::table project_namespace = state["obe"]["system"]["project"].get<sol::table>();
        project_namespace.set_function(
            "get_project_location", &obe::system::project::get_project_location);
    }
    void load_function_project_exists(sol::state_view state)
    {
        sol::table project_namespace = state["obe"]["system"]["project"].get<sol::table>();
        project_namespace.set_function("project_exists", &obe::system::project::project_exists);
    }
    void load_function_load(sol::state_view state)
    {
        sol::table project_namespace = state["obe"]["system"]["project"].get<sol::table>();
        project_namespace.set_function("load",
            sol::overload([](const std::string& project_name, const std::string& prefix) -> bool
                { return obe::system::project::load(project_name, prefix); },
                [](const std::string& project_name, const std::string& prefix,
                    unsigned int priority) -> bool
                { return obe::system::project::load(project_name, prefix, priority); }));
    }
    void load_function_list_projects(sol::state_view state)
    {
        sol::table project_namespace = state["obe"]["system"]["project"].get<sol::table>();
        project_namespace.set_function("list_projects", &obe::system::project::list_projects);
    }
};