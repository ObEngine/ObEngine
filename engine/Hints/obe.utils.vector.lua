---@meta

obe.utils.vector = {};
--- Check if a given item is in the given std::vector.
---
---@param item V #Item you want to search in the std::vector
---@param vec V[] #Reference of the std::vector you want to search the item in
---@return boolean
function obe.utils.vector.contains(item, vec) end

--- Join all elements of a std::string into a std::string using a separator.
---
---@param vector string[] #array containing the strings to join
---@param sep? string #string separator used to join the string values from the array
---@param start? number #start position from where to start joining values
---@param stop? number #from which index (starting at the end) of the array to stop joining values
---@return string
function obe.utils.vector.join(vector, sep, start, stop) end

return obe.utils.vector;