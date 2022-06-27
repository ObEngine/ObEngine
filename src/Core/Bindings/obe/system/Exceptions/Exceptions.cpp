#include <Bindings/obe/system/Exceptions/Exceptions.hpp>

#include <System/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::Exceptions::bindings
{
    void load_class_invalid_deferred_mountable_path(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::InvalidDeferredMountablePath>
            bind_invalid_deferred_mountable_path = Exceptions_namespace.new_usertype<
                obe::system::Exceptions::InvalidDeferredMountablePath>(
                "InvalidDeferredMountablePath", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::InvalidDeferredMountablePath(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::InvalidDeferredMountablePath>,
                    obe::BaseException>());
    }
    void load_class_invalid_mount_file(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::InvalidMountFile> bind_invalid_mount_file
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::InvalidMountFile>(
                "InvalidMountFile", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::InvalidMountFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::InvalidMountFile>,
                    obe::BaseException>());
    }
    void load_class_invalid_mouse_button_enum_value(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::InvalidMouseButtonEnumValue>
            bind_invalid_mouse_button_enum_value = Exceptions_namespace.new_usertype<
                obe::system::Exceptions::InvalidMouseButtonEnumValue>("InvalidMouseButtonEnumValue",
                sol::call_constructor,
                sol::constructors<obe::system::Exceptions::InvalidMouseButtonEnumValue(
                    int, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::InvalidMouseButtonEnumValue>,
                    obe::BaseException>());
    }
    void load_class_invalid_project_file(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::InvalidProjectFile> bind_invalid_project_file
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::InvalidProjectFile>(
                "InvalidProjectFile", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::InvalidProjectFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::InvalidProjectFile>,
                    obe::BaseException>());
    }
    void load_class_missing_default_mount_point(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::MissingDefaultMountPoint>
            bind_missing_default_mount_point
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::MissingDefaultMountPoint>(
                "MissingDefaultMountPoint", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::MissingDefaultMountPoint(
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::MissingDefaultMountPoint>,
                    obe::BaseException>());
    }
    void load_class_mount_file_missing(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::MountFileMissing> bind_mount_file_missing
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::MountFileMissing>(
                "MountFileMissing", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::MountFileMissing(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::MountFileMissing>,
                    obe::BaseException>());
    }
    void load_class_mountable_path_index_overflow(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::MountablePathIndexOverflow>
            bind_mountable_path_index_overflow = Exceptions_namespace.new_usertype<
                obe::system::Exceptions::MountablePathIndexOverflow>("MountablePathIndexOverflow",
                sol::call_constructor,
                sol::constructors<obe::system::Exceptions::MountablePathIndexOverflow(
                    std::size_t, std::size_t, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::MountablePathIndexOverflow>,
                    obe::BaseException>());
    }
    void load_class_package_already_installed(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::PackageAlreadyInstalled>
            bind_package_already_installed
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::PackageAlreadyInstalled>(
                "PackageAlreadyInstalled", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::PackageAlreadyInstalled(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::PackageAlreadyInstalled>,
                    obe::BaseException>());
    }
    void load_class_package_file_not_found(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::PackageFileNotFound> bind_package_file_not_found
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::PackageFileNotFound>(
                "PackageFileNotFound", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::PackageFileNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::PackageFileNotFound>,
                    obe::BaseException>());
    }
    void load_class_path_error(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::PathError> bind_path_error
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::PathError>("PathError",
                sol::call_constructor,
                sol::constructors<obe::system::Exceptions::PathError(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::PathError>,
                    obe::BaseException>());
    }
    void load_class_resource_not_found(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::ResourceNotFound> bind_resource_not_found
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::ResourceNotFound>(
                "ResourceNotFound", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::ResourceNotFound(std::string_view,
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::ResourceNotFound>,
                    obe::BaseException>());
    }
    void load_class_unknown_package(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::UnknownPackage> bind_unknown_package
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::UnknownPackage>(
                "UnknownPackage", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::UnknownPackage(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::UnknownPackage>,
                    obe::BaseException>());
    }
    void load_class_unknown_path_prefix(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::UnknownPathPrefix> bind_unknown_path_prefix
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::UnknownPathPrefix>(
                "UnknownPathPrefix", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::UnknownPathPrefix(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::UnknownPathPrefix>,
                    obe::BaseException>());
    }
    void load_class_unknown_project(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["system"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::UnknownProject> bind_unknown_project
            = Exceptions_namespace.new_usertype<obe::system::Exceptions::UnknownProject>(
                "UnknownProject", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::UnknownProject(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::UnknownProject>,
                    obe::BaseException>());
    }
};