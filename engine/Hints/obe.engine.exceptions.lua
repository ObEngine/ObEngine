---@meta

obe.engine.exceptions = {};
---@class obe.engine.exceptions.BootScriptExecutionError : obe.Exception[obe.engine.exceptions.BootScriptExecutionError]
obe.engine.exceptions._BootScriptExecutionError = {};

--- obe.engine.exceptions.BootScriptExecutionError constructor
---
---@param info obe.DebugInfo #
---@return obe.engine.exceptions.BootScriptExecutionError
function obe.engine.exceptions.BootScriptExecutionError(info) end



---@class obe.engine.exceptions.BootScriptLoadingError : obe.Exception[obe.engine.exceptions.BootScriptLoadingError]
obe.engine.exceptions._BootScriptLoadingError = {};

--- obe.engine.exceptions.BootScriptLoadingError constructor
---
---@param error_message string #
---@param info obe.DebugInfo #
---@return obe.engine.exceptions.BootScriptLoadingError
function obe.engine.exceptions.BootScriptLoadingError(error_message, info) end



---@class obe.engine.exceptions.BootScriptMissing : obe.Exception[obe.engine.exceptions.BootScriptMissing]
obe.engine.exceptions._BootScriptMissing = {};

--- obe.engine.exceptions.BootScriptMissing constructor
---
---@param mounted_paths string[] #
---@param info obe.DebugInfo #
---@return obe.engine.exceptions.BootScriptMissing
function obe.engine.exceptions.BootScriptMissing(mounted_paths, info) end



---@class obe.engine.exceptions.FontNotFound : obe.Exception[obe.engine.exceptions.FontNotFound]
obe.engine.exceptions._FontNotFound = {};

--- obe.engine.exceptions.FontNotFound constructor
---
---@param path string #
---@param mounts string[] #
---@param info obe.DebugInfo #
---@return obe.engine.exceptions.FontNotFound
function obe.engine.exceptions.FontNotFound(path, mounts, info) end



---@class obe.engine.exceptions.TextureNotFound : obe.Exception[obe.engine.exceptions.TextureNotFound]
obe.engine.exceptions._TextureNotFound = {};

--- obe.engine.exceptions.TextureNotFound constructor
---
---@param path string #
---@param info obe.DebugInfo #
---@return obe.engine.exceptions.TextureNotFound
function obe.engine.exceptions.TextureNotFound(path, info) end



---@class obe.engine.exceptions.UnitializedEngine : obe.Exception[obe.engine.exceptions.UnitializedEngine]
obe.engine.exceptions._UnitializedEngine = {};

--- obe.engine.exceptions.UnitializedEngine constructor
---
---@param info obe.DebugInfo #
---@return obe.engine.exceptions.UnitializedEngine
function obe.engine.exceptions.UnitializedEngine(info) end



return obe.engine.exceptions;