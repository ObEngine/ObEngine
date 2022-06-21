---@meta

vili.exceptions = {};
---@class vili.exceptions.array_index_overflow : vili.exceptions.exception[vili.exceptions.array_index_overflow]
vili.exceptions._array_index_overflow = {};

--- vili.exceptions.array_index_overflow constructor
---
---@param index number #
---@param maximum number #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.array_index_overflow
function vili.exceptions.array_index_overflow(index, maximum, info) end



---@class vili.exceptions.base_exception : std.exception
vili.exceptions._base_exception = {};


---@return string
function vili.exceptions._base_exception:what() end

---@param args Args &&... #
function vili.exceptions._base_exception:error(args) end

---@param args Args &&... #
function vili.exceptions._base_exception:hint(args) end


---@class vili.exceptions.debug_info
---@field file string #
---@field line number #
---@field function string #
vili.exceptions._debug_info = {};

--- vili.exceptions.debug_info constructor
---
---@param file string #
---@param line number #
---@param funcname string #
---@return vili.exceptions.debug_info
function vili.exceptions.debug_info(file, line, funcname) end



---@class vili.exceptions.file_not_found : vili.exceptions.exception[vili.exceptions.file_not_found]
vili.exceptions._file_not_found = {};

--- vili.exceptions.file_not_found constructor
---
---@param path string #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.file_not_found
function vili.exceptions.file_not_found(path, info) end



---@class vili.exceptions.inconsistent_indentation : vili.exceptions.exception[vili.exceptions.inconsistent_indentation]
vili.exceptions._inconsistent_indentation = {};

--- vili.exceptions.inconsistent_indentation constructor
---
---@param indent_level number #
---@param base_indentation number #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.inconsistent_indentation
function vili.exceptions.inconsistent_indentation(indent_level, base_indentation, info) end



---@class vili.exceptions.integer_dump_error : vili.exceptions.exception[vili.exceptions.integer_dump_error]
vili.exceptions._integer_dump_error = {};

--- vili.exceptions.integer_dump_error constructor
---
---@param value vili.integer #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.integer_dump_error
function vili.exceptions.integer_dump_error(value, info) end



---@class vili.exceptions.invalid_cast : vili.exceptions.exception[vili.exceptions.invalid_cast]
vili.exceptions._invalid_cast = {};

--- vili.exceptions.invalid_cast constructor
---
---@param cast string #
---@param real_type string #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.invalid_cast
function vili.exceptions.invalid_cast(cast, real_type, info) end



---@class vili.exceptions.invalid_data_type : vili.exceptions.exception[vili.exceptions.invalid_data_type]
vili.exceptions._invalid_data_type = {};

--- vili.exceptions.invalid_data_type constructor
---
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.invalid_data_type
function vili.exceptions.invalid_data_type(info) end



---@class vili.exceptions.invalid_merge : vili.exceptions.exception[vili.exceptions.invalid_merge]
vili.exceptions._invalid_merge = {};

--- vili.exceptions.invalid_merge constructor
---
---@param merge_base_type string #
---@param merge_type string #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.invalid_merge
function vili.exceptions.invalid_merge(merge_base_type, merge_type, info) end



---@class vili.exceptions.invalid_node_type : vili.exceptions.exception[vili.exceptions.invalid_node_type]
vili.exceptions._invalid_node_type = {};

--- vili.exceptions.invalid_node_type constructor
---
---@param node_type string #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.invalid_node_type
function vili.exceptions.invalid_node_type(node_type, info) end



---@class vili.exceptions.number_dump_error : vili.exceptions.exception[vili.exceptions.number_dump_error]
vili.exceptions._number_dump_error = {};

--- vili.exceptions.number_dump_error constructor
---
---@param value vili.number #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.number_dump_error
function vili.exceptions.number_dump_error(value, info) end



---@class vili.exceptions.parsing_error : vili.exceptions.exception[vili.exceptions.parsing_error]
vili.exceptions._parsing_error = {};

--- vili.exceptions.parsing_error constructor
---
---@param source string #
---@param line number #
---@param column number #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.parsing_error
function vili.exceptions.parsing_error(source, line, column, info) end



---@class vili.exceptions.too_much_indentation : vili.exceptions.exception[vili.exceptions.too_much_indentation]
vili.exceptions._too_much_indentation = {};

--- vili.exceptions.too_much_indentation constructor
---
---@param indent_level number #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.too_much_indentation
function vili.exceptions.too_much_indentation(indent_level, info) end



---@class vili.exceptions.unknown_child_node : vili.exceptions.exception[vili.exceptions.unknown_child_node]
---@field key string #
vili.exceptions._unknown_child_node = {};

--- vili.exceptions.unknown_child_node constructor
---
---@param key string #
---@param info vili.exceptions.debug_info #
---@return vili.exceptions.unknown_child_node
function vili.exceptions.unknown_child_node(key, info) end



return vili.exceptions;