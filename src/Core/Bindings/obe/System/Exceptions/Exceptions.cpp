#include <Bindings/obe/System/Exceptions/Exceptions.hpp>

#include <System/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::System::Exceptions::Bindings
{
    void LoadClassInvalidMountFile(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::InvalidMountFile> bindInvalidMountFile
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::InvalidMountFile>(
                "InvalidMountFile", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::InvalidMountFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<InvalidMountFile>, obe::BaseException>());
    }
    void LoadClassInvalidMouseButtonEnumValue(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::InvalidMouseButtonEnumValue>
            bindInvalidMouseButtonEnumValue = ExceptionsNamespace.new_usertype<
                obe::System::Exceptions::InvalidMouseButtonEnumValue>("InvalidMouseButtonEnumValue",
                sol::call_constructor,
                sol::constructors<obe::System::Exceptions::InvalidMouseButtonEnumValue(
                    int, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<InvalidMouseButtonEnumValue>, obe::BaseException>());
    }
    void LoadClassInvalidProjectFile(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::InvalidProjectFile> bindInvalidProjectFile
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::InvalidProjectFile>(
                "InvalidProjectFile", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::InvalidProjectFile(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<InvalidProjectFile>, obe::BaseException>());
    }
    void LoadClassMissingDefaultMountPoint(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::MissingDefaultMountPoint>
            bindMissingDefaultMountPoint
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::MissingDefaultMountPoint>(
                "MissingDefaultMountPoint", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::MissingDefaultMountPoint(
                    obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<MissingDefaultMountPoint>, obe::BaseException>());
    }
    void LoadClassMountFileMissing(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::MountFileMissing> bindMountFileMissing
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::MountFileMissing>(
                "MountFileMissing", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::MountFileMissing(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<MountFileMissing>, obe::BaseException>());
    }
    void LoadClassMountablePathIndexOverflow(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::MountablePathIndexOverflow>
            bindMountablePathIndexOverflow
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::MountablePathIndexOverflow>(
                "MountablePathIndexOverflow", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::MountablePathIndexOverflow(
                    std::size_t, std::size_t, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<MountablePathIndexOverflow>, obe::BaseException>());
    }
    void LoadClassPackageAlreadyInstalled(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::PackageAlreadyInstalled> bindPackageAlreadyInstalled
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::PackageAlreadyInstalled>(
                "PackageAlreadyInstalled", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::PackageAlreadyInstalled(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<PackageAlreadyInstalled>, obe::BaseException>());
    }
    void LoadClassPackageFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::PackageFileNotFound> bindPackageFileNotFound
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::PackageFileNotFound>(
                "PackageFileNotFound", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::PackageFileNotFound(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<PackageFileNotFound>, obe::BaseException>());
    }
    void LoadClassPathError(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::PathError> bindPathError
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::PathError>("PathError",
                sol::call_constructor,
                sol::constructors<obe::System::Exceptions::PathError(
                    std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception<PathError>, obe::BaseException>());
    }
    void LoadClassResourceNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::ResourceNotFound> bindResourceNotFound
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::ResourceNotFound>(
                "ResourceNotFound", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::ResourceNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<ResourceNotFound>, obe::BaseException>());
    }
    void LoadClassUnknownPackage(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::UnknownPackage> bindUnknownPackage
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::UnknownPackage>(
                "UnknownPackage", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::UnknownPackage(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<UnknownPackage>, obe::BaseException>());
    }
    void LoadClassUnknownPathPrefix(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::UnknownPathPrefix> bindUnknownPathPrefix
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::UnknownPathPrefix>(
                "UnknownPathPrefix", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::UnknownPathPrefix(
                    std::string_view, const std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<UnknownPathPrefix>, obe::BaseException>());
    }
    void LoadClassUnknownProject(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::UnknownProject> bindUnknownProject
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::UnknownProject>(
                "UnknownProject", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::UnknownProject(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<UnknownProject>, obe::BaseException>());
    }
    void LoadClassUnknownStretchMode(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::UnknownStretchMode> bindUnknownStretchMode
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::UnknownStretchMode>(
                "UnknownStretchMode", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::UnknownStretchMode(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<UnknownStretchMode>, obe::BaseException>());
    }
};