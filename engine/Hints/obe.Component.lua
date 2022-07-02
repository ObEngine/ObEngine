---@meta

obe.component = {};
---@class obe.component.ComponentBase : obe.types.Identifiable, obe.types.Serializable
---@field ComponentType string #
obe.component._ComponentBase = {};

--- obe.component.ComponentBase constructor
---
---@param id string #
---@return obe.component.ComponentBase
function obe.component.ComponentBase(id) end


function obe.component._ComponentBase:remove() end

--- Dumps the content of the Serializable object to a vili node.
---
---@return vili.node
function obe.component._ComponentBase:dump() end

--- Loads an object from a vili node.
---
---@param data vili.node #vili node containing the data of the object
function obe.component._ComponentBase:load(data) end

---@return string
function obe.component._ComponentBase:type() end

---@return sol.lua_value
function obe.component._ComponentBase:cast() end


return obe.component;