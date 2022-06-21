---@meta

vili.parser = {};
---@class vili.parser.node_in_stack
---@field item vili.node #
---@field indent number #
vili.parser._node_in_stack = {};

--- vili.parser.node_in_stack constructor
---
---@param node vili.node #
---@param indent number #
---@return vili.parser.node_in_stack
function vili.parser.node_in_stack(node, indent) end



---@class vili.parser.state
---@field root vili.node #
vili.parser._state = {};

--- vili.parser.state constructor
---
---@return vili.parser.state
function vili.parser.state() end

--- vili.parser.state constructor
---
---@param state vili.parser.state #
---@return vili.parser.state
function vili.parser.state(state) end

--- vili.parser.state constructor
---
---@param state vili.parser.state #
---@return vili.parser.state
function vili.parser.state(state) end


---@param indent number #
function vili.parser._state:set_indent(indent) end

function vili.parser._state:use_indent() end

---@param identifier string #
function vili.parser._state:set_active_identifier(identifier) end

function vili.parser._state:open_block() end

function vili.parser._state:close_block() end

---@param data vili.node #
function vili.parser._state:push(data) end


---@class vili.parser.error
vili.parser._error = {};




---@alias vili.parser.control tao.pegtl.must_if[vili.parser.error >.vili.parser.control[Rule]]
---@param data string #
---@param parser_state? vili.parser.state #
---@return vili.node
function vili.parser.from_string(data, parser_state) end

---@param path string #
---@return vili.node
function vili.parser.from_file(path) end

---@param self vili.parser.state #
---@param value vili.node #
function vili.parser.state_push_proxy(self, value) end

return vili.parser;