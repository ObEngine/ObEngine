#pragma once

namespace sol
{
    class state_view;
};
namespace obe::script::exceptions::bindings
{
    void load_class_game_object_script_error(sol::state_view state);
    void load_class_invalid_script(sol::state_view state);
    void load_class_lua_execution_error(sol::state_view state);
    void load_class_lua_nested_exception_error(sol::state_view state);
    void load_class_no_such_component(sol::state_view state);
    void load_class_object_definition_not_found(sol::state_view state);
    void load_class_script_file_not_found(sol::state_view state);
    void load_class_wrong_source_attribute_type(sol::state_view state);
};