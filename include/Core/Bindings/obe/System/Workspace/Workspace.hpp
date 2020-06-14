#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Workspace::Bindings
{
    void LoadFunctionGetWorkspaceLocation(sol::state_view state);
    void LoadFunctionWorkspaceExists(sol::state_view state);
    void LoadFunctionLoad(sol::state_view state);
    void LoadFunctionListWorkspaces(sol::state_view state);
};