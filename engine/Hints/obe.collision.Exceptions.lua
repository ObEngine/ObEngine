---@meta

obe.collision.Exceptions = {};
---@class obe.collision.Exceptions.InvalidTagFormat : obe.Exception[obe.collision.Exceptions.InvalidTagFormat]
obe.collision.Exceptions._InvalidTagFormat = {};

--- obe.collision.Exceptions.InvalidTagFormat constructor
---
---@param collider_id string #
---@param tag_type string #
---@param data_type string #
---@param info obe.DebugInfo #
---@return obe.collision.Exceptions.InvalidTagFormat
function obe.collision.Exceptions.InvalidTagFormat(collider_id, tag_type, data_type, info) end



return obe.collision.Exceptions;