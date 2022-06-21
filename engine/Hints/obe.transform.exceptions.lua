---@meta

obe.transform.exceptions = {};
---@class obe.transform.exceptions.PolygonNotEnoughPoints : obe.Exception[obe.transform.exceptions.PolygonNotEnoughPoints]
obe.transform.exceptions._PolygonNotEnoughPoints = {};

--- obe.transform.exceptions.PolygonNotEnoughPoints constructor
---
---@param polygon nil #
---@param points number #
---@param info obe.DebugInfo #
---@return obe.transform.exceptions.PolygonNotEnoughPoints
function obe.transform.exceptions.PolygonNotEnoughPoints(polygon, points, info) end



---@class obe.transform.exceptions.PolygonPointIndexOverflow : obe.Exception[obe.transform.exceptions.PolygonPointIndexOverflow]
obe.transform.exceptions._PolygonPointIndexOverflow = {};

--- obe.transform.exceptions.PolygonPointIndexOverflow constructor
---
---@param polygon nil #
---@param index number #
---@param maximum number #
---@param info obe.DebugInfo #
---@return obe.transform.exceptions.PolygonPointIndexOverflow
function obe.transform.exceptions.PolygonPointIndexOverflow(polygon, index, maximum, info) end



---@class obe.transform.exceptions.UnknownReferential : obe.Exception[obe.transform.exceptions.UnknownReferential]
obe.transform.exceptions._UnknownReferential = {};

--- obe.transform.exceptions.UnknownReferential constructor
---
---@param referential string #
---@param info obe.DebugInfo #
---@return obe.transform.exceptions.UnknownReferential
function obe.transform.exceptions.UnknownReferential(referential, info) end



return obe.transform.exceptions;