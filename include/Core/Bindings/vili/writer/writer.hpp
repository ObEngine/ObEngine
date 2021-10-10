#pragma once

namespace sol
{
    class state_view;
};
namespace vili::writer::Bindings
{
    void LoadClassDumpOptions(sol::state_view state);
    void LoadEnumDelimiterNewlinePolicy(sol::state_view state);
    void LoadEnumCommaSpacingPolicy(sol::state_view state);
    void LoadEnumObjectStyle(sol::state_view state);
    void LoadFunctionDumpInteger(sol::state_view state);
    void LoadFunctionDumpNumber(sol::state_view state);
    void LoadFunctionDumpBoolean(sol::state_view state);
    void LoadFunctionDumpString(sol::state_view state);
    void LoadFunctionDumpArray(sol::state_view state);
    void LoadFunctionDumpObject(sol::state_view state);
    void LoadFunctionDump(sol::state_view state);
};