#include <Bindings/obe/System/Project/Project.hpp>

#include <System/Project.hpp>

#include <Bindings/Config.hpp>

namespace obe::System::Project::Bindings
{
    void LoadClassProject(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        sol::usertype<obe::System::Project::Project> bindProject
            = ProjectNamespace.new_usertype<obe::System::Project::Project>("Project",
                sol::call_constructor, sol::constructors<obe::System::Project::Project()>());
        bindProject["dump"] = &obe::System::Project::Project::dump;
        bindProject["load"] = &obe::System::Project::Project::load;
        bindProject["loadFromFile"] = &obe::System::Project::Project::loadFromFile;
        bindProject["mount"] = &obe::System::Project::Project::mount;
        bindProject["unmount"] = &obe::System::Project::Project::unmount;
    }
    void LoadClassProjectURLs(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        sol::usertype<obe::System::Project::ProjectURLs> bindProjectURLs
            = ProjectNamespace.new_usertype<obe::System::Project::ProjectURLs>(
                "ProjectURLs", sol::call_constructor, sol::default_constructor);
        bindProjectURLs["dump"] = &obe::System::Project::ProjectURLs::dump;
        bindProjectURLs["load"] = &obe::System::Project::ProjectURLs::load;
        bindProjectURLs["homepage"] = &obe::System::Project::ProjectURLs::homepage;
        bindProjectURLs["issues"] = &obe::System::Project::ProjectURLs::issues;
        bindProjectURLs["readme"] = &obe::System::Project::ProjectURLs::readme;
        bindProjectURLs["documentation"] = &obe::System::Project::ProjectURLs::documentation;
        bindProjectURLs["license"] = &obe::System::Project::ProjectURLs::license;
    }
    void LoadFunctionGetProjectLocation(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        ProjectNamespace.set_function(
            "GetProjectLocation", &obe::System::Project::GetProjectLocation);
    }
    void LoadFunctionProjectExists(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        ProjectNamespace.set_function("ProjectExists", &obe::System::Project::ProjectExists);
    }
    void LoadFunctionLoad(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        ProjectNamespace.set_function("Load",
            sol::overload([](const std::string& projectName, const std::string& prefix)
                              -> bool { return obe::System::Project::Load(projectName, prefix); },
                [](const std::string& projectName, const std::string& prefix, unsigned int priority)
                    -> bool { return obe::System::Project::Load(projectName, prefix, priority); }));
    }
    void LoadFunctionListProjects(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        ProjectNamespace.set_function("ListProjects", &obe::System::Project::ListProjects);
    }
};