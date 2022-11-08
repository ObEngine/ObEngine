---@meta

obe.events.Keys = {};
---@class obe.events.Keys.Pressed
obe.events.Keys._Pressed = {};



---@class obe.events.Keys.StateChanged
---@field state obe.input.InputSourceState #
---@field previous_state obe.input.InputSourceState #
---@field input_source obe.input.InputSource #
obe.events.Keys._StateChanged = {};



return obe.events.Keys;