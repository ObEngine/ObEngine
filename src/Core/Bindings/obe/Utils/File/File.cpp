#include <Bindings/obe/Utils/File/File.hpp>

#include <Utils/FileUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::Utils::File::Bindings
{
    void LoadFunctionGetDirectoryList(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("get_directory_list", &obe::Utils::File::get_directory_list);
    }
    void LoadFunctionGetFileList(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("get_file_list", &obe::Utils::File::get_file_list);
    }
    void LoadFunctionFileExists(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("file_exists", &obe::Utils::File::file_exists);
    }
    void LoadFunctionDirectoryExists(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("directory_exists", &obe::Utils::File::directory_exists);
    }
    void LoadFunctionCreateDirectory(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("create_directory", &obe::Utils::File::create_directory);
    }
    void LoadFunctionCreateFile(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("create_file", &obe::Utils::File::create_file);
    }
    void LoadFunctionCopy(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("copy", &obe::Utils::File::copy);
    }
    void LoadFunctionDeleteFile(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("delete_file", &obe::Utils::File::delete_file);
    }
    void LoadFunctionDeleteDirectory(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("delete_directory", &obe::Utils::File::delete_directory);
    }
    void LoadFunctionGetCurrentDirectory(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("get_current_directory", &obe::Utils::File::get_current_directory);
    }
    void LoadFunctionSeparator(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("separator", &obe::Utils::File::separator);
    }
    void LoadFunctionGetExecutableDirectory(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function(
            "get_executable_directory", &obe::Utils::File::get_executable_directory);
    }
    void LoadFunctionGetExecutablePath(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("get_executable_path", &obe::Utils::File::get_executable_path);
    }
    void LoadFunctionNormalizePath(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("normalize_path", &obe::Utils::File::normalize_path);
    }
    void LoadFunctionCanonicalPath(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("canonical_path", &obe::Utils::File::canonical_path);
    }
    void LoadFunctionJoin(sol::state_view state)
    {
        sol::table FileNamespace = state["obe"]["Utils"]["File"].get<sol::table>();
        FileNamespace.set_function("join", &obe::Utils::File::join);
    }
};