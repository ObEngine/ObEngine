---@meta

obe.network = {};
---@class obe.network.LuaPacket
obe.network._LuaPacket = {};



---@class obe.network.NetworkClient
obe.network._NetworkClient = {};

--- obe.network.NetworkClient constructor
---
---@param name string #
---@param socket sf.TcpSocket #
---@return obe.network.NetworkClient
function obe.network.NetworkClient(name, socket) end


---@param name string #
function obe.network._NetworkClient:rename(name) end

---@return string
function obe.network._NetworkClient:name() end

---@return string
function obe.network._NetworkClient:host() end

---@return sf.TcpSocket
function obe.network._NetworkClient:socket() end


---@class obe.network.NetworkEventManager
obe.network._NetworkEventManager = {};

--- obe.network.NetworkEventManager constructor
---
---@param event_namespace obe.event.EventNamespace.Ptr #
---@param spec vili.node #
---@return obe.network.NetworkEventManager
function obe.network.NetworkEventManager(event_namespace, spec) end


---@param current_name string #
---@param new_name string #
function obe.network._NetworkEventManager:rename_client(current_name, new_name) end

---@param port number #
function obe.network._NetworkEventManager:host(port) end

---@param host string #
---@param port number #
function obe.network._NetworkEventManager:connect(host, port) end

---@param event_group_name string #
---@param event_name string #
---@param data vili.node #
function obe.network._NetworkEventManager:emit(event_group_name, event_name, data) end

---@param recipient string #
---@param event_group_name string #
---@param event_name string #
---@param data vili.node #
function obe.network._NetworkEventManager:emit(recipient, event_group_name, event_name, data) end

function obe.network._NetworkEventManager:handle_events() end

---@return obe.event.EventNamespaceView
function obe.network._NetworkEventManager:get_event_namespace() end

---@return string
function obe.network._NetworkEventManager:get_client_name() end


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