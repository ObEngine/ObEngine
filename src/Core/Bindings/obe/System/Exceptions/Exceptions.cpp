#include <Bindings/obe/System/Exceptions/Exceptions.hpp>

#include <System/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::system::Exceptions::Bindings
{
    void LoadClassInvalidDeferredMountablePath(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::InvalidDeferredMountablePath>
            bindInvalidDeferredMountablePath = ExceptionsNamespace.new_usertype<
                obe::system::Exceptions::InvalidDeferredMountablePath>(
                "InvalidDeferredMountablePath", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::InvalidDeferredMountablePath(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::InvalidDeferredMountablePath>,
                    obe::BaseException>());
    }
    void LoadClassInvalidMountFile(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::InvalidMountFile> bindInvalidMountFile
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::InvalidMountFile>(
                "InvalidMountFile", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::InvalidMountFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::InvalidMountFile>,
                    obe::BaseException>());
    }
    void LoadClassInvalidMouseButtonEnumValue(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::InvalidMouseButtonEnumValue>
            bindInvalidMouseButtonEnumValue = ExceptionsNamespace.new_usertype<
                obe::system::Exceptions::InvalidMouseButtonEnumValue>("InvalidMouseButtonEnumValue",
                sol::call_constructor,
                sol::constructors<obe::system::Exceptions::InvalidMouseButtonEnumValue(
                    int, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::InvalidMouseButtonEnumValue>,
                    obe::BaseException>());
    }
    void LoadClassInvalidProjectFile(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::InvalidProjectFile> bindInvalidProjectFile
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::InvalidProjectFile>(
                "InvalidProjectFile", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::InvalidProjectFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::InvalidProjectFile>,
                    obe::BaseException>());
    }
    void LoadClassMissingDefaultMountPoint(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::MissingDefaultMountPoint>
            bindMissingDefaultMountPoint
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::MissingDefaultMountPoint>(
                "MissingDefaultMountPoint", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::MissingDefaultMountPoint(
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::MissingDefaultMountPoint>,
                    obe::BaseException>());
    }
    void LoadClassMountFileMissing(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::MountFileMissing> bindMountFileMissing
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::MountFileMissing>(
                "MountFileMissing", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::MountFileMissing(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::MountFileMissing>,
                    obe::BaseException>());
    }
    void LoadClassMountablePathIndexOverflow(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::MountablePathIndexOverflow>
            bindMountablePathIndexOverflow
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::MountablePathIndexOverflow>(
                "MountablePathIndexOverflow", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::MountablePathIndexOverflow(
                    std::size_t, std::size_t, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::MountablePathIndexOverflow>,
                    obe::BaseException>());
    }
    void LoadClassPackageAlreadyInstalled(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::PackageAlreadyInstalled> bindPackageAlreadyInstalled
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::PackageAlreadyInstalled>(
                "PackageAlreadyInstalled", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::PackageAlreadyInstalled(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::PackageAlreadyInstalled>,
                    obe::BaseException>());
    }
    void LoadClassPackageFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::PackageFileNotFound> bindPackageFileNotFound
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::PackageFileNotFound>(
                "PackageFileNotFound", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::PackageFileNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::PackageFileNotFound>,
                    obe::BaseException>());
    }
    void LoadClassPathError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::PathError> bindPathError
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::PathError>("PathError",
                sol::call_constructor,
                sol::constructors<obe::system::Exceptions::PathError(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::PathError>,
                    obe::BaseException>());
    }
    void LoadClassResourceNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::ResourceNotFound> bindResourceNotFound
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::ResourceNotFound>(
                "ResourceNotFound", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::ResourceNotFound(std::string_view,
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::ResourceNotFound>,
                    obe::BaseException>());
    }
    void LoadClassUnknownPackage(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::UnknownPackage> bindUnknownPackage
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::UnknownPackage>(
                "UnknownPackage", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::UnknownPackage(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::UnknownPackage>,
                    obe::BaseException>());
    }
    void LoadClassUnknownPathPrefix(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::UnknownPathPrefix> bindUnknownPathPrefix
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::UnknownPathPrefix>(
                "UnknownPathPrefix", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::UnknownPathPrefix(
                    std::string_view, const std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::UnknownPathPrefix>,
                    obe::BaseException>());
    }
    void LoadClassUnknownProject(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["system"]["exceptions"].get<sol::table>();
        sol::usertype<obe::system::Exceptions::UnknownProject> bindUnknownProject
            = ExceptionsNamespace.new_usertype<obe::system::Exceptions::UnknownProject>(
                "UnknownProject", sol::call_constructor,
                sol::constructors<obe::system::Exceptions::UnknownProject(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::system::Exceptions::UnknownProject>,
                    obe::BaseException>());
    }
};