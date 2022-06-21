---@meta

obe.config.Exceptions = {};
---@class obe.config.Exceptions.ConfigError : obe.Exception[obe.config.Exceptions.ConfigError]
obe.config.Exceptions._ConfigError = {};

--- obe.config.Exceptions.ConfigError constructor
---
---@param config_files string[] #
---@param info obe.DebugInfo #
---@return obe.config.Exceptions.ConfigError
function obe.config.Exceptions.ConfigError(config_files, info) end



---@class obe.config.Exceptions.InvalidVersionFormat : obe.Exception[obe.config.Exceptions.InvalidVersionFormat]
obe.config.Exceptions._InvalidVersionFormat = {};

--- obe.config.Exceptions.InvalidVersionFormat constructor
---
---@param detail string #
---@param info obe.DebugInfo #
---@return obe.config.Exceptions.InvalidVersionFormat
function obe.config.Exceptions.InvalidVersionFormat(detail, info) end



return obe.config.Exceptions;