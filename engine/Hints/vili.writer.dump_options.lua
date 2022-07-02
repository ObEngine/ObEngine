---@meta

vili.writer.dump_options = {};
---@class vili.writer.dump_options._array
---@field items_per_line vili.writer.dump_options._items_per_line #
---@field max_line_length number #
---@field starts_with_newline vili.writer.delimiter_newline_policy #
---@field ends_with_newline vili.writer.delimiter_newline_policy #
---@field inline_spacing number #
vili.writer.dump_options.__array = {};



---@class vili.writer.dump_options._items_per_line
---@field any number #
---@field primitives number #
---@field arrays number #
---@field objects number #
vili.writer.dump_options.__items_per_line = {};



---@class vili.writer.dump_options._object
---@field items_per_line vili.writer.dump_options._items_per_line #
---@field max_line_length number #
---@field starts_with_newline vili.writer.delimiter_newline_policy #
---@field ends_with_newline vili.writer.delimiter_newline_policy #
---@field inline_spacing number #
---@field arrays_vertical_spacing number #
---@field objects_vertical_spacing number #
---@field style vili.writer.object_style #
vili.writer.dump_options.__object = {};



return vili.writer.dump_options;