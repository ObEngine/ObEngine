---@meta

obe.events.Network = {};
---@class obe.events.Network.ClientRename
---@field client_name string #
---@field id string #
obe.events.Network._ClientRename = {};



---@class obe.events.Network.Connected
---@field ip string #
---@field port number #
---@field remote_port number #
---@field client_name string #
---@field id string #
obe.events.Network._Connected = {};



---@class obe.events.Network.Disconnected
---@field id string #
obe.events.Network._Disconnected = {};



---@class obe.events.Network.Message
---@field client_name string #
---@field event_group_name string #
---@field event_name string #
---@field data vili.node #
---@field id string #
obe.events.Network._Message = {};



return obe.events.Network;