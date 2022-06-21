---@meta

obe.Component = {};
---@class obe.Component.ComponentBase : obe.Types.Identifiable, obe.Types.Serializable
---@field ComponentType string #
obe.Component._ComponentBase = {};

--- obe.Component.ComponentBase constructor
---
---@param id string #
---@return obe.Component.ComponentBase
function obe.Component.ComponentBase(id) end


function obe.Component._ComponentBase:remove() end

--- Dumps the content of the Serializable object to a vili node.
---
---@return vili.node
function obe.Component._ComponentBase:dump() end

--- Loads an object from a vili node.
---
---@param data vili.node #vili node containing the data of the object
function obe.Component._ComponentBase:load(data) end

---@return string
function obe.Component._ComponentBase:type() end

---@return sol.lua_value
function obe.Component._ComponentBase:cast() end


return obe.Component;