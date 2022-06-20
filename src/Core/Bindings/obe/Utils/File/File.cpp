#include <Bindings/obe/utils/file/File.hpp>

#include <Utils/FileUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::file::bindings
{
    void load_function_get_directory_list(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("get_directory_list", &obe::utils::file::get_directory_list);
    }
    void load_function_get_file_list(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("get_file_list", &obe::utils::file::get_file_list);
    }
    void load_function_file_exists(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("file_exists", &obe::utils::file::file_exists);
    }
    void load_function_directory_exists(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("directory_exists", &obe::utils::file::directory_exists);
    }
    void load_function_create_directory(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("create_directory", &obe::utils::file::create_directory);
    }
    void load_function_create_file(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("create_file", &obe::utils::file::create_file);
    }
    void load_function_copy(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("copy", &obe::utils::file::copy);
    }
    void load_function_delete_file(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("delete_file", &obe::utils::file::delete_file);
    }
    void load_function_delete_directory(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("delete_directory", &obe::utils::file::delete_directory);
    }
    void load_function_get_current_directory(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function(
            "get_current_directory", &obe::utils::file::get_current_directory);
    }
    void load_function_separator(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("separator", &obe::utils::file::separator);
    }
    void load_function_get_executable_directory(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function(
            "get_executable_directory", &obe::utils::file::get_executable_directory);
    }
    void load_function_get_executable_path(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("get_executable_path", &obe::utils::file::get_executable_path);
    }
    void load_function_normalize_path(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("normalize_path", &obe::utils::file::normalize_path);
    }
    void load_function_canonical_path(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("canonical_path", &obe::utils::file::canonical_path);
    }
    void load_function_join(sol::state_view state)
    {
        sol::table file_namespace = state["obe"]["utils"]["file"].get<sol::table>();
        file_namespace.set_function("join", &obe::utils::file::join);
    }
};