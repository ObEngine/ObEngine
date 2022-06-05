#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Exceptions::Bindings
{
    void LoadClassInvalidDeferredMountablePath(sol::state_view state);
    void LoadClassInvalidMountFile(sol::state_view state);
    void LoadClassInvalidMouseButtonEnumValue(sol::state_view state);
    void LoadClassInvalidProjectFile(sol::state_view state);
    void LoadClassMissingDefaultMountPoint(sol::state_view state);
    void LoadClassMountFileMissing(sol::state_view state);
    void LoadClassMountablePathIndexOverflow(sol::state_view state);
    void LoadClassPackageAlreadyInstalled(sol::state_view state);
    void LoadClassPackageFileNotFound(sol::state_view state);
    void LoadClassPathError(sol::state_view state);
    void LoadClassResourceNotFound(sol::state_view state);
    void LoadClassUnknownPackage(sol::state_view state);
    void LoadClassUnknownPathPrefix(sol::state_view state);
    void LoadClassUnknownProject(sol::state_view state);
    void LoadClassUnknownStretchMode(sol::state_view state);
};