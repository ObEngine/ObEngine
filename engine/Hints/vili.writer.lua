---@meta

vili.writer = {};
---@class vili.writer.dump_options
---@field indent number #
---@field array vili.writer.dump_options._array #
---@field object vili.writer.dump_options._object #
vili.writer._dump_options = {};



---@class vili.writer.dump_state
---@field root boolean #
---@field depth number #
---@field object_mode vili.writer.object_style #
vili.writer._dump_state = {};



---@param data vili.node #
---@return string
function vili.writer.dump_integer(data) end

---@param data vili.node #
---@return string
function vili.writer.dump_number(data) end

---@param data vili.node #
---@return string
function vili.writer.dump_boolean(data) end

---@param data vili.node #
---@return string
function vili.writer.dump_string(data) end

---@param data vili.node #
---@param options vili.writer.dump_options #
---@param state vili.writer.dump_state #
---@return string
function vili.writer.dump_array(data, options, state) end

---@param data vili.node #
---@param options vili.writer.dump_options #
---@param state vili.writer.dump_state #
---@return string
function vili.writer.dump_object(data, options, state) end

---@param data vili.node #
---@param options? vili.writer.dump_options #
---@param state? vili.writer.dump_state #
---@return string
function vili.writer.dump(data, options, state) end


--- 
---
---@class vili.writer.delimiter_newline_policy
vili.writer.delimiter_newline_policy = {
    never = 0,
    only_if_multiline = 1,
    always = 2,
};

--- 
---
---@class vili.writer.object_style
vili.writer.object_style = {
    braces = 0,
    indent = 1,
};
return vili.writer;