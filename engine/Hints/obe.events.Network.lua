---@meta

obe.events.Network = {};
---@class obe.events.Network.Connected
---@field ip string #
---@field id string #
obe.events.Network._Connected = {};



---@class obe.events.Network.DataReceived
---@field content string #
---@field id string #
obe.events.Network._DataReceived = {};



---@class obe.events.Network.Disconnected
---@field id string #
obe.events.Network._Disconnected = {};



return obe.events.Network;