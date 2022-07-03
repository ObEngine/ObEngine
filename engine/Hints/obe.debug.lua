---@meta

obe.debug = {};

---@alias obe.debug.Logger spdlog.logger

---@alias obe.debug.LogLevelMeta obe.types.SmartEnum[obe.debug.LogLevel]
--- Initialize the Logger.
---
---@param dump_log_to_file boolean #
function obe.debug.init_logger(dump_log_to_file) end

---@param content string #
function obe.debug.trace(content) end

---@param content string #
function obe.debug.debug(content) end

---@param content string #
function obe.debug.info(content) end

---@param content string #
function obe.debug.warn(content) end

---@param content string #
function obe.debug.error(content) end

---@param content string #
function obe.debug.critical(content) end


---@type obe.debug.Logger
obe.debug.Log = {};

--- 
---
---@class obe.debug.LogLevel
obe.debug.LogLevel = {
    ---@type obe.debug.LogLevel
    Trace = 0,
    ---@type obe.debug.LogLevel
    Debug = 1,
    ---@type obe.debug.LogLevel
    Info = 2,
    ---@type obe.debug.LogLevel
    Warn = 3,
    ---@type obe.debug.LogLevel
    Error = 4,
    ---@type obe.debug.LogLevel
    Critical = 5,
    ---@type obe.debug.LogLevel
    Off = 6,
};
return obe.debug;