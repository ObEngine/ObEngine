---@meta

vili.utils.string = {};
---@param subject string #
---@param search string #
---@param replace string #
---@return string
function vili.utils.string.replace(subject, search, replace) end

---@param str string #
---@return boolean
function vili.utils.string.is_int(str) end

---@param str string #
---@return boolean
function vili.utils.string.is_float(str) end

---@param str string #
---@return string
function vili.utils.string.truncate_float(str) end

---@param str string #
---@return string
function vili.utils.string.quote(str) end

---@param input string #
---@return number
function vili.utils.string.to_double(input) end

---@param input string #
---@return number
function vili.utils.string.to_long(input) end

---@param input string #
---@param indent_level? number #
---@param pad_left? boolean #
---@return string
function vili.utils.string.indent(input, indent_level, pad_left) end

---@param source string #
---@param target string #
---@return number
function vili.utils.string.distance(source, target) end

---@param source string #
---@param words string[] #
---@param limit number #
---@return string[]
function vili.utils.string.sort_by_distance(source, words, limit) end

return vili.utils.string;