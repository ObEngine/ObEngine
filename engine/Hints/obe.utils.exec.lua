---@meta

obe.utils.exec = {};
---@class obe.utils.exec.RunArgsParser
obe.utils.exec._RunArgsParser = {};

--- Constructor of RunArgsParser takes argc and argv in parameters.
---
---@param size number #This is argc
---@param start string #This is argv
---@return obe.utils.exec.RunArgsParser
function obe.utils.exec.RunArgsParser(size, start) end


--- Check if a argument has been entered.
---
---@param arg string #Name of the argument you want to check existence
---@return boolean
function obe.utils.exec._RunArgsParser:argument_exists(arg) end

--- Get the given argument's value.
---
---@param arg string #Name of the argument you want to retrieve the value
---@return string
function obe.utils.exec._RunArgsParser:get_argument_value(arg) end


return obe.utils.exec;