---@meta

--- Builds vili array from Lua table
---
---@param t table #Lua table to convert to vili array
---@return vili.node
function vili.array(t)
end

--- Builds vili object from Lua table
---
---@param t table #Lua table to convert to vili object
---@return vili.node
function vili.object(t)
end

--- Builds vili node from Lua value
---
---@param t any #Lua value to convert to vili node
---@return vili.node
function vili.from_lua(t)
end

--- Builds Lua value from vili node
---
---@param t vili.node #Vili node to convert to Lua value
---@return any
function vili.to_lua(t)
end

--- Loads vili document from path and converts it to Lua table
---
---@param path string #Path to the vili document
---@param state? vili.parser.state #Optional state with preloaded elements used to parse the document
---@return table
function vili.from_file(path, state)
end

--- Loads vili document from string and converts it to Lua table
---
---@param data string #Vili document in string form
---@param parser_state? vili.parser.state #Optional state with preloaded elements used to parse the document
---@return table
function vili.from_string(data, parser_state)
end

--- Dumps Lua table to a vili document in string form
---
---@param tbl table #Lua table to dump
---@param dump_options? vili.writer.dump_options #Dump options
---@return string
function vili.dump(tbl, dump_options)
end

--- Dumps Lua table to a vili file
---
---@param path #Path where to write the Vili document
---@param tbl table #Lua table to dump
---@param dump_options? vili.writer.dump_options #Dump options
function vili.to_file(path, tbl, dump_options)
end

return vili;