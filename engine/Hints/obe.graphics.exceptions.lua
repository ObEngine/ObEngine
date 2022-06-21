---@meta

obe.graphics.exceptions = {};
---@class obe.graphics.exceptions.CanvasElementAlreadyExists : obe.Exception[obe.graphics.exceptions.CanvasElementAlreadyExists]
obe.graphics.exceptions._CanvasElementAlreadyExists = {};

--- obe.graphics.exceptions.CanvasElementAlreadyExists constructor
---
---@param id string #
---@param new_element_type string #
---@param existing_element_type string #
---@param info obe.DebugInfo #
---@return obe.graphics.exceptions.CanvasElementAlreadyExists
function obe.graphics.exceptions.CanvasElementAlreadyExists(id, new_element_type, existing_element_type, info) end



---@class obe.graphics.exceptions.ImageFileNotFound : obe.Exception[obe.graphics.exceptions.ImageFileNotFound]
obe.graphics.exceptions._ImageFileNotFound = {};

--- obe.graphics.exceptions.ImageFileNotFound constructor
---
---@param path string #
---@param info obe.DebugInfo #
---@return obe.graphics.exceptions.ImageFileNotFound
function obe.graphics.exceptions.ImageFileNotFound(path, info) end



---@class obe.graphics.exceptions.InvalidColorName : obe.Exception[obe.graphics.exceptions.InvalidColorName]
obe.graphics.exceptions._InvalidColorName = {};

--- obe.graphics.exceptions.InvalidColorName constructor
---
---@param color string #
---@param info obe.DebugInfo #
---@return obe.graphics.exceptions.InvalidColorName
function obe.graphics.exceptions.InvalidColorName(color, info) end



---@class obe.graphics.exceptions.InvalidHexFormat : obe.Exception[obe.graphics.exceptions.InvalidHexFormat]
obe.graphics.exceptions._InvalidHexFormat = {};

--- obe.graphics.exceptions.InvalidHexFormat constructor
---
---@param hex_code string #
---@param info obe.DebugInfo #
---@return obe.graphics.exceptions.InvalidHexFormat
function obe.graphics.exceptions.InvalidHexFormat(hex_code, info) end



---@class obe.graphics.exceptions.InvalidHsvFormat : obe.Exception[obe.graphics.exceptions.InvalidHsvFormat]
obe.graphics.exceptions._InvalidHsvFormat = {};

--- obe.graphics.exceptions.InvalidHsvFormat constructor
---
---@param H number #
---@param S number #
---@param V number #
---@param info obe.DebugInfo #
---@return obe.graphics.exceptions.InvalidHsvFormat
function obe.graphics.exceptions.InvalidHsvFormat(H, S, V, info) end



---@class obe.graphics.exceptions.InvalidRgbFormat : obe.Exception[obe.graphics.exceptions.InvalidRgbFormat]
obe.graphics.exceptions._InvalidRgbFormat = {};

--- obe.graphics.exceptions.InvalidRgbFormat constructor
---
---@param r number #
---@param g number #
---@param b number #
---@param a number #
---@param info obe.DebugInfo #
---@return obe.graphics.exceptions.InvalidRgbFormat
function obe.graphics.exceptions.InvalidRgbFormat(r, g, b, a, info) end



---@class obe.graphics.exceptions.InvalidSpriteColorType : obe.Exception[obe.graphics.exceptions.InvalidSpriteColorType]
obe.graphics.exceptions._InvalidSpriteColorType = {};

--- obe.graphics.exceptions.InvalidSpriteColorType constructor
---
---@param type string #
---@param value string #
---@param info obe.DebugInfo #
---@return obe.graphics.exceptions.InvalidSpriteColorType
function obe.graphics.exceptions.InvalidSpriteColorType(type, value, info) end



---@class obe.graphics.exceptions.ReadOnlyTexture : obe.Exception[obe.graphics.exceptions.ReadOnlyTexture]
obe.graphics.exceptions._ReadOnlyTexture = {};

--- obe.graphics.exceptions.ReadOnlyTexture constructor
---
---@param method string #
---@param info obe.DebugInfo #
---@return obe.graphics.exceptions.ReadOnlyTexture
function obe.graphics.exceptions.ReadOnlyTexture(method, info) end



return obe.graphics.exceptions;