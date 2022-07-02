---@meta

obe.debug = {};

---@alias obe.debug.Logger spdlog.logger

---@alias obe.debug.LogLevelMeta obe.types.SmartEnum[obe.debug.LogLevel]
--- Initialize the Logger.
---
function obe.debug.init_logger() end

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
    Trace = 0,
    Debug = 1,
    Info = 2,
    Warn = 3,
    Error = 4,
    Critical = 5,
    Off = 6,
};
return obe.debug;