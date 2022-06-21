---@meta

obe.script.Helpers = {};
---@param lua sol.state_view #
---@return table<string, function>
function obe.script.Helpers.make_all_helpers(lua) end

---@param lua sol.state_view #
---@return function
function obe.script.Helpers.fetch_from_one_of(lua) end

---@param lua sol.state_view #
---@return function
function obe.script.Helpers.rawget_from(lua) end

---@param lua sol.state_view #
---@return function
function obe.script.Helpers.len_from(lua) end

---@param lua sol.state_view #
---@return function
function obe.script.Helpers.pairs_from(lua) end

return obe.script.Helpers;