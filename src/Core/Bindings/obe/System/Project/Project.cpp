#include <Bindings/obe/System/Project/Project.hpp>

#include <System/Project.hpp>

#include <Bindings/Config.hpp>

namespace obe::System::Project::Bindings
{
    void LoadFunctionGetProjectLocation(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        ProjectNamespace.set_function(
            "GetProjectLocation", obe::System::Project::GetProjectLocation);
    }
    void LoadFunctionProjectExists(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        ProjectNamespace.set_function("ProjectExists", obe::System::Project::ProjectExists);
    }
    void LoadFunctionLoad(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        ProjectNamespace.set_function("Load", obe::System::Project::Load);
    }
    void LoadFunctionListProjects(sol::state_view state)
    {
        sol::table ProjectNamespace = state["obe"]["System"]["Project"].get<sol::table>();
        ProjectNamespace.set_function("ListProjects", obe::System::Project::ListProjects);
    }
};
