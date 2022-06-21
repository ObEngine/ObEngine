---@meta

obe.network = {};
---@class obe.network.LuaPacket
obe.network._LuaPacket = {};



---@class obe.network.NetworkHandler
obe.network._NetworkHandler = {};

--- obe.network.NetworkHandler constructor
---
---@param event_namespace obe.event.EventNamespace #
---@return obe.network.NetworkHandler
function obe.network.NetworkHandler(event_namespace) end


function obe.network._NetworkHandler:handle_events() end


---@class obe.network.TcpServer
obe.network._TcpServer = {};

--- obe.network.TcpServer constructor
---
---@param event_namespace obe.event.EventNamespace #
---@param port number #
---@return obe.network.TcpServer
function obe.network.TcpServer(event_namespace, port) end


function obe.network._TcpServer:update() end

---@param max_buffer_size number #
function obe.network._TcpServer:set_buffer_size(max_buffer_size) end


---@class obe.network.TcpSocket : sf.TcpSocket
obe.network._TcpSocket = {};



return obe.network;