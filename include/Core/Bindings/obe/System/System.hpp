#pragma once

namespace sol
{
    class state_view;
};
namespace obe::system::Bindings
{
    void LoadClassContextualPathFactory(sol::state_view state);
    void LoadClassCursor(sol::state_view state);
    void LoadClassCursorModel(sol::state_view state);
    void LoadClassFindResult(sol::state_view state);
    void LoadClassMountablePath(sol::state_view state);
    void LoadClassPath(sol::state_view state);
    void LoadClassPlugin(sol::state_view state);
    void LoadClassWindow(sol::state_view state);
    void LoadEnumCursorType(sol::state_view state);
    void LoadEnumMountablePathType(sol::state_view state);
    void LoadEnumSamePrefixPolicy(sol::state_view state);
    void LoadEnumPathType(sol::state_view state);
    void LoadEnumWindowContext(sol::state_view state);
    void LoadEnumStretchMode(sol::state_view state);
    void LoadFunctionSplitPathAndPrefix(sol::state_view state);
};