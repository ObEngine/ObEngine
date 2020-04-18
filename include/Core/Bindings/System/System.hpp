#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Bindings
{
    void LoadClassCursor(sol::state_view state);
    void LoadClassLoaderMultipleResult(sol::state_view state);
    void LoadClassLoaderResult(sol::state_view state);
    void LoadClassMountablePath(sol::state_view state);
    void LoadClassPath(sol::state_view state);
    void LoadClassPlugin(sol::state_view state);
    void LoadClassWindow(sol::state_view state);
    void LoadEnumMountablePathType(sol::state_view state);
    void LoadEnumPathType(sol::state_view state);
    void LoadEnumWindowContext(sol::state_view state);
};