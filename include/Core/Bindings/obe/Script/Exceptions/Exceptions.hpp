#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Script::Exceptions::Bindings
{
    void LoadClassGameObjectScriptError(sol::state_view state);
    void LoadClassInvalidScript(sol::state_view state);
    void LoadClassLuaExecutionError(sol::state_view state);
    void LoadClassNoSuchComponent(sol::state_view state);
    void LoadClassObjectDefinitionNotFound(sol::state_view state);
    void LoadClassScriptFileNotFound(sol::state_view state);
    void LoadClassWrongSourceAttributeType(sol::state_view state);
};