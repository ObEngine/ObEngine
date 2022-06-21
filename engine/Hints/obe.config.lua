---@meta

obe.config = {};
---@class obe.config.ConfigurationManager : vili.node
obe.config._ConfigurationManager = {};

--- obe.config.ConfigurationManager constructor
---
---@return obe.config.ConfigurationManager
function obe.config.ConfigurationManager() end


function obe.config._ConfigurationManager:load() end


---@class obe.config.Version
---@field major number #
---@field minor number #
---@field patch number #
obe.config._Version = {};

--- obe.config.Version constructor
---
---@param version_major number #
---@param version_minor number #
---@param version_patch number #
---@return obe.config.Version
function obe.config.Version(version_major, version_minor, version_patch) end

--- obe.config.Version constructor
---
---@param str string #
---@return obe.config.Version
function obe.config.Version(str) end


---@return string
function obe.config._Version:string() end


return obe.config;