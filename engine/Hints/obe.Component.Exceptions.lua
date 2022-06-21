---@meta

obe.Component.Exceptions = {};
---@class obe.Component.Exceptions.ComponentIdAlreadyTaken : obe.Exception[obe.Component.Exceptions.ComponentIdAlreadyTaken]
obe.Component.Exceptions._ComponentIdAlreadyTaken = {};

--- obe.Component.Exceptions.ComponentIdAlreadyTaken constructor
---
---@param id string #
---@param info obe.DebugInfo #
---@return obe.Component.Exceptions.ComponentIdAlreadyTaken
function obe.Component.Exceptions.ComponentIdAlreadyTaken(id, info) end



---@class obe.Component.Exceptions.UnknownComponentType : obe.Exception[obe.Component.Exceptions.UnknownComponentType]
obe.Component.Exceptions._UnknownComponentType = {};

--- obe.Component.Exceptions.UnknownComponentType constructor
---
---@param component_type string #
---@param info obe.DebugInfo #
---@return obe.Component.Exceptions.UnknownComponentType
function obe.Component.Exceptions.UnknownComponentType(component_type, info) end



return obe.Component.Exceptions;