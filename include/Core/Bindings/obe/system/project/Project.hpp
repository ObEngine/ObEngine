#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::project::bindings
{
    void load_class_project(sol::state_view state);
    void load_class_project_ur_ls(sol::state_view state);
    void load_function_get_project_location(sol::state_view state);
    void load_function_project_exists(sol::state_view state);
    void load_function_load(sol::state_view state);
    void load_function_list_projects(sol::state_view state);
};