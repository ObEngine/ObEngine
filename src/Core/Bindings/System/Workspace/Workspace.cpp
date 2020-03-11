#include <Bindings/System/Workspace/Workspace.hpp>

#include <System/Workspace.hpp>

#include <sol/sol.hpp>

namespace obe::System::Workspace::Bindings
{
    void LoadFunctionGetWorkspaceLocation(sol::state_view state)
    {
        sol::table WorkspaceNamespace
            = state["obe"]["System"]["Workspace"].get<sol::table>();
        WorkspaceNamespace.set_function(
            "GetWorkspaceLocation", obe::System::Workspace::GetWorkspaceLocation);
    }
    void LoadFunctionWorkspaceExists(sol::state_view state)
    {
        sol::table WorkspaceNamespace
            = state["obe"]["System"]["Workspace"].get<sol::table>();
        WorkspaceNamespace.set_function(
            "WorkspaceExists", obe::System::Workspace::WorkspaceExists);
    }
    void LoadFunctionLoad(sol::state_view state)
    {
        sol::table WorkspaceNamespace
            = state["obe"]["System"]["Workspace"].get<sol::table>();
        WorkspaceNamespace.set_function("Load", obe::System::Workspace::Load);
    }
};