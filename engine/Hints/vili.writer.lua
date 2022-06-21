---@meta

vili.writer = {};
---@class vili.writer.dump_options
---@field indent number #
---@field array vili.writer.dump_options._array #
---@field object vili.writer.dump_options._object #
---@field root boolean #
vili.writer._dump_options = {};



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
---@param options? vili.writer.dump_options #
---@return string
function vili.writer.dump_array(data, options) end

---@param data vili.node #
---@param options? vili.writer.dump_options #
---@return string
function vili.writer.dump_object(data, options) end

---@param data vili.node #
---@param options? vili.writer.dump_options #
---@return string
function vili.writer.dump(data, options) end


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
---@class vili.writer.comma_spacing_policy
vili.writer.comma_spacing_policy = {
    left_side = 0,
    right_side = 1,
    both = 2,
};

--- 
---
---@class vili.writer.object_style
vili.writer.object_style = {
    braces = 0,
    indent = 1,
};
return vili.writer;