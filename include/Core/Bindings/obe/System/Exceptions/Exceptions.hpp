#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::Exceptions::bindings
{
    void load_class_invalid_deferred_mountable_path(sol::state_view state);
    void load_class_invalid_mount_file(sol::state_view state);
    void load_class_invalid_mouse_button_enum_value(sol::state_view state);
    void load_class_invalid_project_file(sol::state_view state);
    void load_class_missing_default_mount_point(sol::state_view state);
    void load_class_mount_file_missing(sol::state_view state);
    void load_class_mountable_path_index_overflow(sol::state_view state);
    void load_class_package_already_installed(sol::state_view state);
    void load_class_package_file_not_found(sol::state_view state);
    void load_class_path_error(sol::state_view state);
    void load_class_resource_not_found(sol::state_view state);
    void load_class_unknown_package(sol::state_view state);
    void load_class_unknown_path_prefix(sol::state_view state);
    void load_class_unknown_project(sol::state_view state);
};