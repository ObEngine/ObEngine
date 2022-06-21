---@meta

obe.engine = {};
---@class obe.engine.Engine
---@field Audio obe.audio.AudioManager #
---@field Configuration obe.config.ConfigurationManager #
---@field Resources obe.engine.ResourceManager #
---@field Input obe.input.InputManager #
---@field Framerate obe.time.FramerateManager #
---@field Events obe.event.EventManager #
---@field Scene obe.scene.Scene #
---@field Cursor obe.system.Cursor #
---@field Window obe.system.Window #
obe.engine._Engine = {};

--- obe.engine.Engine constructor
---
---@return obe.engine.Engine
function obe.engine.Engine() end


function obe.engine._Engine:init() end

function obe.engine._Engine:run() end


---@class obe.engine.ResourceManagedObject
obe.engine._ResourceManagedObject = {};


function obe.engine._ResourceManagedObject:remove_resource_manager() end

---@param resources obe.engine.ResourceManager #
function obe.engine._ResourceManagedObject:attach_resource_manager(resources) end


---@class obe.engine.ResourceManager
---@field default_anti_aliasing boolean #
obe.engine._ResourceManager = {};

--- obe.engine.ResourceManager constructor
---
---@return obe.engine.ResourceManager
function obe.engine.ResourceManager() end


---@param path string #
---@return obe.graphics.Font
function obe.engine._ResourceManager:get_font(path) end

function obe.engine._ResourceManager:clean() end



---@alias obe.engine.ResourceStore table<string, T>

---@alias obe.engine.TexturePair table<number, obe.graphics.Texture>
return obe.engine;