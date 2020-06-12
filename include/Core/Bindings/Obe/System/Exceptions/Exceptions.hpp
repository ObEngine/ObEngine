#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Exceptions::Bindings
{
    void LoadClassInvalidMouseButtonEnumValue(sol::state_view state);
    void LoadClassMountablePathIndexOverflow(sol::state_view state);
    void LoadClassMountFileMissing(sol::state_view state);
    void LoadClassPackageAlreadyInstalled(sol::state_view state);
    void LoadClassPackageFileNotFound(sol::state_view state);
    void LoadClassResourceNotFound(sol::state_view state);
    void LoadClassUnknownPackage(sol::state_view state);
    void LoadClassUnknownWorkspace(sol::state_view state);
};