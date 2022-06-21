---@meta

obe.script.exceptions = {};
---@class obe.script.exceptions.GameObjectScriptError : obe.Exception[obe.script.exceptions.GameObjectScriptError]
obe.script.exceptions._GameObjectScriptError = {};

--- obe.script.exceptions.GameObjectScriptError constructor
---
---@param object_type string #
---@param object_id string #
---@param callback string #
---@param info obe.DebugInfo #
---@return obe.script.exceptions.GameObjectScriptError
function obe.script.exceptions.GameObjectScriptError(object_type, object_id, callback, info) end



---@class obe.script.exceptions.InvalidScript : obe.Exception[obe.script.exceptions.InvalidScript]
obe.script.exceptions._InvalidScript = {};

--- obe.script.exceptions.InvalidScript constructor
---
---@param path string #
---@param error string #
---@param info obe.DebugInfo #
---@return obe.script.exceptions.InvalidScript
function obe.script.exceptions.InvalidScript(path, error, info) end



---@class obe.script.exceptions.LuaExecutionError : obe.Exception[obe.script.exceptions.LuaExecutionError]
obe.script.exceptions._LuaExecutionError = {};

--- obe.script.exceptions.LuaExecutionError constructor
---
---@param err std.exception #
---@param info obe.DebugInfo #
---@return obe.script.exceptions.LuaExecutionError
function obe.script.exceptions.LuaExecutionError(err, info) end



---@class obe.script.exceptions.LuaNestedExceptionError : obe.Exception[obe.script.exceptions.LuaNestedExceptionError]
obe.script.exceptions._LuaNestedExceptionError = {};

--- obe.script.exceptions.LuaNestedExceptionError constructor
---
---@param err std.exception #
---@param info obe.DebugInfo #
---@return obe.script.exceptions.LuaNestedExceptionError
function obe.script.exceptions.LuaNestedExceptionError(err, info) end



---@class obe.script.exceptions.NoSuchComponent : obe.Exception[obe.script.exceptions.NoSuchComponent]
obe.script.exceptions._NoSuchComponent = {};

--- obe.script.exceptions.NoSuchComponent constructor
---
---@param component_type string #
---@param object_type string #
---@param object_id string #
---@param info obe.DebugInfo #
---@return obe.script.exceptions.NoSuchComponent
function obe.script.exceptions.NoSuchComponent(component_type, object_type, object_id, info) end



---@class obe.script.exceptions.ObjectDefinitionNotFound : obe.Exception[obe.script.exceptions.ObjectDefinitionNotFound]
obe.script.exceptions._ObjectDefinitionNotFound = {};

--- obe.script.exceptions.ObjectDefinitionNotFound constructor
---
---@param object_type string #
---@param info obe.DebugInfo #
---@return obe.script.exceptions.ObjectDefinitionNotFound
function obe.script.exceptions.ObjectDefinitionNotFound(object_type, info) end



---@class obe.script.exceptions.ScriptFileNotFound : obe.Exception[obe.script.exceptions.ScriptFileNotFound]
obe.script.exceptions._ScriptFileNotFound = {};

--- obe.script.exceptions.ScriptFileNotFound constructor
---
---@param object_type string #
---@param object_id string #
---@param script_path string #
---@param info obe.DebugInfo #
---@return obe.script.exceptions.ScriptFileNotFound
function obe.script.exceptions.ScriptFileNotFound(object_type, object_id, script_path, info) end



---@class obe.script.exceptions.WrongSourceAttributeType : obe.Exception[obe.script.exceptions.WrongSourceAttributeType]
obe.script.exceptions._WrongSourceAttributeType = {};

--- obe.script.exceptions.WrongSourceAttributeType constructor
---
---@param object_type string #
---@param attribute_name string #
---@param expected_type string #
---@param real_type string #
---@param info obe.DebugInfo #
---@return obe.script.exceptions.WrongSourceAttributeType
function obe.script.exceptions.WrongSourceAttributeType(object_type, attribute_name, expected_type, real_type, info) end



return obe.script.exceptions;