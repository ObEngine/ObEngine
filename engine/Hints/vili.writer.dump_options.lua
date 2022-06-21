---@meta

vili.writer.dump_options = {};
---@class vili.writer.dump_options._array
---@field items_per_line number #
---@field max_line_length number #
---@field starts_with_newline vili.writer.delimiter_newline_policy #
---@field ends_with_newline vili.writer.delimiter_newline_policy #
---@field left_bracket_spacing number #
---@field right_bracket_spacing number #
---@field inline_spacing number #
---@field comma_spacing vili.writer.comma_spacing_policy #
vili.writer.dump_options.__array = {};



---@class vili.writer.dump_options._object
---@field items_per_line number #
---@field max_line_length number #
---@field starts_with_newline vili.writer.delimiter_newline_policy #
---@field ends_with_newline vili.writer.delimiter_newline_policy #
---@field left_brace_spacing number #
---@field right_brace_spacing number #
---@field affectation_left_spaces number #
---@field affectation_right_spaces number #
---@field inline_spacing number #
---@field comma_spacing vili.writer.comma_spacing_policy #
---@field style vili.writer.object_style #
vili.writer.dump_options.__object = {};



return vili.writer.dump_options;