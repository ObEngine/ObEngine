---@meta

obe.types = {};
---@class obe.types.Identifiable
obe.types._Identifiable = {};

--- Creates a new Identifiable.
---
---@param id string #A std::string containing the id of the Identifiable
---@return obe.types.Identifiable
function obe.types.Identifiable(id) end


--- Set a new id for the Identifiable.
---
---@param id string #Sets the id of the Identifiable
function obe.types._Identifiable:set_id(id) end

--- Get the id of the Identifiable.
---
---@return string
function obe.types._Identifiable:get_id() end


---@class obe.types.ProtectedIdentifiable : obe.types.Identifiable
obe.types._ProtectedIdentifiable = {};



---@class obe.types.Selectable
obe.types._Selectable = {};

--- Constructor of Selectable Class.
---
---@param selected? boolean #Default state of m_selected
---@return obe.types.Selectable
function obe.types.Selectable(selected) end


--- Set the state of the Selectable.
---
---@param selected boolean #A boolean to set the state of the Selectable (true / false)
function obe.types._Selectable:set_selected(selected) end

--- Selectable becomes unselected if it was selected and selected if it was not.
---
function obe.types._Selectable:toggle_selected() end

--- Selects the Selectable.
---
function obe.types._Selectable:select() end

--- Unselect the Selectable.
---
function obe.types._Selectable:unselect() end

--- Get if the Selectable is selected or not.
---
---@return boolean
function obe.types._Selectable:is_selected() end


---@class obe.types.Serializable
obe.types._Serializable = {};


--- Dumps the content of the Serializable object to a vili node.
---
---@return vili.node
function obe.types._Serializable:dump() end

--- Loads an object from a vili node.
---
---@param data vili.node #vili node containing the data of the object
function obe.types._Serializable:load(data) end

---@param path string #
function obe.types._Serializable:load_from_file(path) end

---@param data vili.node #
function obe.types._Serializable:validate_and_load(data) end


---@class obe.types.Togglable
obe.types._Togglable = {};

--- Constructor of Togglable Class.
---
---@param enabled boolean #Default state of m_enabled
---@return obe.types.Togglable
function obe.types.Togglable(enabled) end


--- Set the state of the Togglable.
---
---@param state boolean #A boolean to set the state of the Togglable (true / false)
function obe.types._Togglable:set_enabled(state) end

--- Togglable disables if it was enabled and enables if it wasn't.
---
function obe.types._Togglable:toggle() end

--- Enable the Togglable.
---
function obe.types._Togglable:enable() end

--- Disable the Togglable.
---
function obe.types._Togglable:disable() end

--- Get if the Togglable is enabled or not.
---
---@return boolean
function obe.types._Togglable:is_enabled() end


---@class obe.types.UniqueIdentifiable
obe.types._UniqueIdentifiable = {};

--- Creates a new UniqueIdentifiable.
---
---@return obe.types.UniqueIdentifiable
function obe.types.UniqueIdentifiable() end

--- obe.types.UniqueIdentifiable constructor
---
---@param p0 obe.types.UniqueIdentifiable #
---@return obe.types.UniqueIdentifiable
function obe.types.UniqueIdentifiable(p0) end

--- obe.types.UniqueIdentifiable constructor
---
---@param other obe.types.UniqueIdentifiable #
---@return obe.types.UniqueIdentifiable
function obe.types.UniqueIdentifiable(other) end


--- Get the unique id of the UniqueIdentifiable.
---
---@return string
function obe.types._UniqueIdentifiable:get_unique_id() end


---@class obe.types.UnknownEnumEntry : obe.Exception[obe.types.UnknownEnumEntry]
obe.types._UnknownEnumEntry = {};

--- obe.types.UnknownEnumEntry constructor
---
---@param enum_name string #
---@param entry_name string #
---@param all_entries string[] #
---@param info obe.DebugInfo #
---@return obe.types.UnknownEnumEntry
function obe.types.UnknownEnumEntry(enum_name, entry_name, all_entries, info) end




---@alias obe.types.is_scoped_enum std.integral_constant[boolean,std.is_enum[E >.value &&!std.is_convertible[E>,int >.value]]]
return obe.types;