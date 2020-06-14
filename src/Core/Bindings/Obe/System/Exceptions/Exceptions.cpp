#include <Bindings/obe/System/Exceptions/Exceptions.hpp>

#include <System/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::System::Exceptions::Bindings
{
    void LoadClassInvalidMouseButtonEnumValue(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::InvalidMouseButtonEnumValue>
            bindInvalidMouseButtonEnumValue = ExceptionsNamespace.new_usertype<
                obe::System::Exceptions::InvalidMouseButtonEnumValue>(
                "InvalidMouseButtonEnumValue", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::InvalidMouseButtonEnumValue(
                    int, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassMountablePathIndexOverflow(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::MountablePathIndexOverflow>
            bindMountablePathIndexOverflow = ExceptionsNamespace.new_usertype<
                obe::System::Exceptions::MountablePathIndexOverflow>(
                "MountablePathIndexOverflow", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::MountablePathIndexOverflow(
                    std::size_t, std::size_t, const std::vector<std::string>&,
                    obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassMountFileMissing(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::MountFileMissing> bindMountFileMissing
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::MountFileMissing>(
                "MountFileMissing", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::MountFileMissing(
                    std::string_view, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassPackageAlreadyInstalled(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::PackageAlreadyInstalled>
            bindPackageAlreadyInstalled
            = ExceptionsNamespace
                  .new_usertype<obe::System::Exceptions::PackageAlreadyInstalled>(
                      "PackageAlreadyInstalled", sol::call_constructor,
                      sol::constructors<obe::System::Exceptions::PackageAlreadyInstalled(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassPackageFileNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::PackageFileNotFound>
            bindPackageFileNotFound
            = ExceptionsNamespace
                  .new_usertype<obe::System::Exceptions::PackageFileNotFound>(
                      "PackageFileNotFound", sol::call_constructor,
                      sol::constructors<obe::System::Exceptions::PackageFileNotFound(
                          std::string_view, obe::DebugInfo)>(),
                      sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassResourceNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::ResourceNotFound> bindResourceNotFound
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::ResourceNotFound>(
                "ResourceNotFound", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::ResourceNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownPackage(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::UnknownPackage> bindUnknownPackage
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::UnknownPackage>(
                "UnknownPackage", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::UnknownPackage(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
    void LoadClassUnknownWorkspace(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::UnknownWorkspace> bindUnknownWorkspace
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::UnknownWorkspace>(
                "UnknownWorkspace", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::UnknownWorkspace(
                    std::string_view, const std::vector<std::string>&, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};