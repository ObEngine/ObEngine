---Casts a pointer to its virtual child
---@generic TypeHint
---@param value userdata
---@param typehint? TypeHint# Optional type hint for casting
---@return TypeHint
function cast(value, typehint)
    return obe.script.cast(value);
end