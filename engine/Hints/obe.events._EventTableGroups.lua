---@meta

obe.events._EventTableGroups = {};
---@class obe.events._EventTableGroups.Cursor
---@field Hold fun(evt:obe.events.Cursor.Hold) #
---@field Move fun(evt:obe.events.Cursor.Move) #
---@field Press fun(evt:obe.events.Cursor.Press) #
---@field Release fun(evt:obe.events.Cursor.Release) #
obe.events._EventTableGroups._Cursor = {};



---@class obe.events._EventTableGroups.Game
---@field End fun(evt:obe.events.Game.End) #
---@field Render fun(evt:obe.events.Game.Render) #
---@field Start fun(evt:obe.events.Game.Start) #
---@field Update fun(evt:obe.events.Game.Update) #
obe.events._EventTableGroups._Game = {};



---@class obe.events._EventTableGroups.Network
---@field Connected fun(evt:obe.events.Network.Connected) #
---@field DataReceived fun(evt:obe.events.Network.DataReceived) #
---@field Disconnected fun(evt:obe.events.Network.Disconnected) #
obe.events._EventTableGroups._Network = {};



---@class obe.events._EventTableGroups.Scene
---@field Loaded fun(evt:obe.events.Scene.Loaded) #
obe.events._EventTableGroups._Scene = {};



return obe.events._EventTableGroups;