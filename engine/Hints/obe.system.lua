---@meta

obe.system = {};
---@class obe.system.ContextualPathFactory
obe.system._ContextualPathFactory = {};

--- obe.system.ContextualPathFactory constructor
---
---@param base string #
---@return obe.system.ContextualPathFactory
function obe.system.ContextualPathFactory(base) end

--- obe.system.ContextualPathFactory constructor
---
---@param base string #
---@param custom_mounts obe.system.MountList #
---@return obe.system.ContextualPathFactory
function obe.system.ContextualPathFactory(base, custom_mounts) end



---@class obe.system.Cursor
obe.system._Cursor = {};

--- Creates a Cursor.
---
---@param window obe.system.Window #
---@param event_namespace obe.event.EventNamespace #
---@return obe.system.Cursor
function obe.system.Cursor(window, event_namespace) end


--- Gets the x Coordinate of the Cursor Position (Constrained)
---
---@return number
function obe.system._Cursor:get_constrained_x() end

--- Gets the y Coordinate of the Cursor Position (Constrained)
---
---@return number
function obe.system._Cursor:get_constrained_y() end

--- Gets the x Coordinate of the raw (System) position of the Cursor (Unconstrained)
---
---@return number
function obe.system._Cursor:get_x() end

--- Gets the y Coordinate of the raw (System) position of the Cursor (Unconstrained)
---
---@return number
function obe.system._Cursor:get_y() end

--- Sets the x Coordinate of the Cursor Position.
---
---@param x number #An int containing the x Coordinate of the new Cursor Position
function obe.system._Cursor:set_x(x) end

--- Sets the y Coordinate of the Cursor Position.
---
---@param y number #An int containing the y Coordinate of the new Cursor Position
function obe.system._Cursor:set_y(y) end

--- Sets the Position of the Cursor.
---
---@param x number #An int containing the x Coordinate of the new Cursor Position
---@param y number #An int containing the y Coordinate of the new Cursor Position
function obe.system._Cursor:set_position(x, y) end

function obe.system._Cursor:show() end

function obe.system._Cursor:hide() end

---@param visible boolean #
function obe.system._Cursor:set_visible(visible) end

---@return boolean
function obe.system._Cursor:is_visible() end

---@return obe.transform.UnitVector
function obe.system._Cursor:get_position() end

---@return obe.transform.UnitVector
function obe.system._Cursor:get_scene_position() end

--- Updates the Cursor.
---
function obe.system._Cursor:update() end

--- Sets the Cursor's constraint.
---
---@param constraint obe.system.Cursor.PositionConstraint #A function returning the constrained Position of the Cursor (x, y coordinates) and taking the Cursor pointer in parameter
---@param condition? obe.system.Cursor.ConstraintCondition #condition for the constraint to apply
function obe.system._Cursor:set_constraint(constraint, condition) end

---@param button sf.Mouse.Button #
---@return boolean
function obe.system._Cursor:is_pressed(button) end

--- Change the cursor.
---
---@param new_cursor obe.system.CursorModel #CursorModel defining the cursor to display
function obe.system._Cursor:set_cursor(new_cursor) end


---@class obe.system.CursorModel
obe.system._CursorModel = {};


--- Set cursor appearance and hotspot from an image file.
---
---@param filename string #Image file to use for the cursor
---@param hotspot_x number #X coordinate on image (in pixels) of the cursor hotspot
---@param hotspot_y number #Y coordinate on image (in pixels) of the cursor hotspot
---@return boolean
function obe.system._CursorModel:load_from_file(filename, hotspot_x, hotspot_y) end

--- Loads a native system cursor.
---
---@param type obe.system.CursorType #Native system cursor type
---@return boolean
function obe.system._CursorModel:load_from_system(type) end


---@class obe.system.FindResult
obe.system._FindResult = {};

--- obe.system.FindResult constructor
---
---@param path_type obe.system.PathType #
---@param path_not_found string #
---@param query string #
---@param mounts obe.system.MountList #
---@return obe.system.FindResult
function obe.system.FindResult(path_type, path_not_found, query, mounts) end

--- obe.system.FindResult constructor
---
---@param path_type obe.system.PathType #
---@param mount obe.system.MountablePath #
---@param path string #
---@param query string #
---@param element? string #
---@return obe.system.FindResult
function obe.system.FindResult(path_type, mount, path, query, element) end


---@return string
function obe.system._FindResult:hypothetical_path() end

---@return string
function obe.system._FindResult:path() end

---@return obe.system.MountablePath
function obe.system._FindResult:mount() end

---@return string
function obe.system._FindResult:query() end

---@return string
function obe.system._FindResult:element() end

---@return boolean
function obe.system._FindResult:success() end


---@class obe.system.MountablePath
---@field path_type obe.system.MountablePathType #Type of the mounted path.
---@field base_path string #Path of the mounted path.
---@field prefix string #Prefix of the mounted path.
---@field priority number #Priority of the mounted path (Higher priority means overriding lower priority Paths)
---@field implicit boolean #Allows the path to be used implicitly (without prefix)
---@field deferred_resolution boolean #Allows to defer base_path resolution to a later time.
obe.system._MountablePath = {};

--- Constructor of MountablePath.
---
---@param path_type obe.system.MountablePathType #Type of the mounted path
---@param base_path string #Path to the mounted path
---@param prefix string #
---@param priority? number #Priority of the mounted path
---@param implicit? boolean #is taken into account when no prefix is provided
---@param defer_resolution? boolean #whether or not to resolve base_path on construction
---@return obe.system.MountablePath
function obe.system.MountablePath(path_type, base_path, prefix, priority, implicit, defer_resolution) end


function obe.system._MountablePath:resolve_base_path() end

--- Function called to Mount all Paths using 'mount.vili' file.
---
---@param from_cwd? boolean #
---@param from_exe? boolean #
function obe.system._MountablePath:load_mount_file(from_cwd, from_exe) end

--- Add a Path to Mounted Paths.
---
---@param path obe.system.MountablePath #Path to mount
---@param same_prefix_policy? obe.system.SamePrefixPolicy #action to take whenever two or more MountablePath with the same prefix are found
function obe.system._MountablePath:mount(path, same_prefix_policy) end

--- Remove a Path from Mounted Paths.
---
---@param path obe.system.MountablePath #Path to unmount
function obe.system._MountablePath:unmount(path) end

--- Remove all Paths from Mounted Paths.
---
function obe.system._MountablePath:unmount_all() end

--- All the Mounted Paths.
---
---@return obe.system.MountList
function obe.system._MountablePath:paths() end

--- All the Mounted Paths as strings.
---
---@return string[]
function obe.system._MountablePath:string_paths() end

--- Sort the mounted paths based on their priorities.
---
function obe.system._MountablePath:sort() end

--- Retrieve a MountablePath based on the prefix.
---
---@param prefix string #
---@return obe.system.MountablePath
function obe.system._MountablePath:from_prefix(prefix) end

---@return string[]
function obe.system._MountablePath:get_all_prefixes() end


---@class obe.system.Path
obe.system._Path = {};

--- Default constructor of Path.
---
---@return obe.system.Path
function obe.system.Path() end

--- Build a path with a custom registry of MountablePath that it will be able to search from.
---
---@param mount obe.system.MountList #A reference containing the mount points the Path should be using
---@return obe.system.Path
function obe.system.Path(mount) end

--- Build a path from an other path (Copy constructor)
---
---@param path obe.system.Path #The Path to build the new Path from
---@return obe.system.Path
function obe.system.Path(path) end

--- Build a path from a std::string_view.
---
---@param path string #Path in std::string_view form
---@return obe.system.Path
function obe.system.Path(path) end

--- Build a path with explicit prefix.
---
---@param prefix string #Prefix in std::string_view form
---@param path string #Path in std::string_view form
---@return obe.system.Path
function obe.system.Path(prefix, path) end


--- Replaces Path's value with a new one.
---
---@param path string #New value for Path
---@return obe.system.Path
function obe.system._Path:set(path) end

--- Returns a new Path which is the current one concatenated with the given string.
---
---@param path string #String containing the path part to add
---@return obe.system.Path
function obe.system._Path:add(path) end

--- Get the last part of a Path.
---
---@return string
function obe.system._Path:last() end

--- Build a path using the current path and the BasePath at given index.
---
---@param index number #Index of the BasePath to use
---@return obe.system.Path
function obe.system._Path:get_path(index) end

--- Finds the most prioritized file corresponding to the Path.
---
---@param path_type? obe.system.PathType #
---@return obe.system.FindResult[]
function obe.system._Path:list(path_type) end

---@param path_type? obe.system.PathType #
---@return obe.system.FindResult
function obe.system._Path:find(path_type) end

---@param path_type? obe.system.PathType #
---@return obe.system.FindResult[]
function obe.system._Path:find_all(path_type) end

--- Get the current path in string form.
---
---@return string
function obe.system._Path:to_string() end


---@class obe.system.Plugin : obe.types.Identifiable
obe.system._Plugin = {};

--- obe.system.Plugin constructor
---
---@param id string #
---@param path string #
---@return obe.system.Plugin
function obe.system.Plugin(id, path) end


---@param engine obe.engine.Engine #
function obe.system._Plugin:on_init(engine) end

---@param engine obe.engine.Engine #
function obe.system._Plugin:on_exit(engine) end

---@return boolean
function obe.system._Plugin:has_on_init() end

---@return boolean
function obe.system._Plugin:has_on_exit() end

---@return boolean
function obe.system._Plugin:is_valid() end


---@class obe.system.Window
obe.system._Window = {};

--- obe.system.Window constructor
---
---@param configuration vili.node #
---@return obe.system.Window
function obe.system.Window(configuration) end


function obe.system._Window:create() end

function obe.system._Window:clear() end

function obe.system._Window:close() end

function obe.system._Window:display() end

---@return obe.transform.UnitVector
function obe.system._Window:get_render_size() end

---@return obe.transform.UnitVector
function obe.system._Window:get_window_size() end

---@return obe.transform.UnitVector
function obe.system._Window:get_size() end

---@return boolean
function obe.system._Window:is_open() end

---@param event sf.Event #
---@return boolean
function obe.system._Window:poll_event(event) end

---@param width number #
---@param height number #
function obe.system._Window:set_size(width, height) end

---@param width number #
---@param height number #
function obe.system._Window:set_window_size(width, height) end

---@param width number #
---@param height number #
function obe.system._Window:set_render_size(width, height) end

---@param title string #
function obe.system._Window:set_title(title) end

---@param enabled boolean #
function obe.system._Window:set_vertical_sync_enabled(enabled) end

---@param view sf.View #
function obe.system._Window:set_view(view) end

---@param path string #
function obe.system._Window:set_icon(path) end

---@return obe.graphics.RenderTarget
function obe.system._Window:get_target() end

---@return sf.RenderWindow
function obe.system._Window:get_window() end

---@return obe.graphics.Color
function obe.system._Window:get_clear_color() end

---@param color obe.graphics.Color #
function obe.system._Window:set_clear_color(color) end

---@param visible boolean #
function obe.system._Window:set_mouse_cursor_visible(visible) end

---@return obe.transform.UnitVector
function obe.system._Window:get_screen_size() end



---@alias obe.system.MountList obe.system.MountablePath[]

---@alias obe.system.PathTypeMeta obe.types.SmartEnum[obe.system.PathType]

---@alias obe.system.PluginFunction dynamicLinker.dynamicLinker.dlSymbol[T]?

---@alias obe.system.StretchModeMeta obe.types.SmartEnum[obe.system.StretchMode]

---@alias obe.system.WindowSizeMeta obe.types.SmartEnum[obe.system.WindowSize]

---@alias obe.system.RenderSizeMeta obe.types.SmartEnum[obe.system.RenderSize]
---@param path string #
---@param warn_on_missing_prefix? boolean #
---@return table<number, string>
function obe.system.split_path_and_prefix(path, warn_on_missing_prefix) end


--- 
---
---@class obe.system.CursorType
obe.system.CursorType = {
    Arrow = 0,
    ArrowWait = 1,
    Wait = 2,
    Text = 3,
    Hand = 4,
    SizeHorizontal = 5,
    SizeVertical = 6,
    SizeTopLeftBottomRight = 7,
    SizeBottomLeftTopRight = 8,
    SizeAll = 9,
    Cross = 10,
    Help = 11,
    NotAllowed = 12,
};

--- Defines the source of a mounted path.
---
---@class obe.system.MountablePathType
obe.system.MountablePathType = {
    Path = 0,
    Package = 1,
    Project = 2,
};

--- action to take whenever two MountablePath with the same prefix are mounted
---
---@class obe.system.SamePrefixPolicy
obe.system.SamePrefixPolicy = {
    KeepBoth = 0,
    Skip = 1,
    Replace = 2,
};

--- 
---
---@class obe.system.PathType
obe.system.PathType = {
    All = 0,
    Directory = 1,
    File = 2,
};

--- 
---
---@class obe.system.WindowContext
obe.system.WindowContext = {
    GameWindow = 0,
    EditorWindow = 1,
};

--- 
---
---@class obe.system.StretchMode
obe.system.StretchMode = {
    None = 0,
    Center = 1,
    Stretch = 2,
    Fit = 3,
};

--- 
---
---@class obe.system.WindowSize
obe.system.WindowSize = {
    Screen = 0,
};

--- 
---
---@class obe.system.RenderSize
obe.system.RenderSize = {
    Window = 0,
    Screen = 1,
};
return obe.system;