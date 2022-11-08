---@meta

vili.msgpack = {};

---@alias vili.msgpack.MsgPackBuffer number[]
---@param msgpack string #
---@return vili.node
function vili.msgpack.from_string(msgpack) end

---@param node vili.node #
---@return string
function vili.msgpack.to_string(node) end

---@param buffer vili.msgpack.MsgPackBuffer #
---@param element vili.node #
function vili.msgpack.dump_element(buffer, element) end

return vili.msgpack;