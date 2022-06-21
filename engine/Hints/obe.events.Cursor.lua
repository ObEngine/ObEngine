---@meta

obe.events.Cursor = {};
---@class obe.events.Cursor.Hold
---@field x number #
---@field y number #
---@field left boolean #
---@field middle boolean #
---@field right boolean #
---@field id string #
obe.events.Cursor._Hold = {};



---@class obe.events.Cursor.Move
---@field x number #
---@field y number #
---@field previous_x number #
---@field previous_y number #
---@field id string #
obe.events.Cursor._Move = {};



---@class obe.events.Cursor.Press
---@field x number #
---@field y number #
---@field left boolean #
---@field middle boolean #
---@field right boolean #
---@field id string #
obe.events.Cursor._Press = {};



---@class obe.events.Cursor.Release
---@field x number #
---@field y number #
---@field left boolean #
---@field middle boolean #
---@field right boolean #
---@field id string #
obe.events.Cursor._Release = {};



return obe.events.Cursor;