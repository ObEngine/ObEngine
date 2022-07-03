#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::file::bindings
{
    void load_function_get_directory_list(sol::state_view state);
    void load_function_get_file_list(sol::state_view state);
    void load_function_file_exists(sol::state_view state);
    void load_function_directory_exists(sol::state_view state);
    void load_function_create_directory(sol::state_view state);
    void load_function_create_file(sol::state_view state);
    void load_function_copy(sol::state_view state);
    void load_function_delete_file(sol::state_view state);
    void load_function_delete_directory(sol::state_view state);
    void load_function_get_current_directory(sol::state_view state);
    void load_function_separator(sol::state_view state);
    void load_function_get_executable_directory(sol::state_view state);
    void load_function_get_executable_path(sol::state_view state);
    void load_function_normalize_path(sol::state_view state);
    void load_function_canonical_path(sol::state_view state);
    void load_function_join(sol::state_view state);
};