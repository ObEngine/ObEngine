---@meta

obe.time = {};
---@class obe.time.Chronometer
obe.time._Chronometer = {};


--- Starts the Chronometer.
---
function obe.time._Chronometer:start() end

--- Stops the Chronometer.
---
function obe.time._Chronometer:stop() end

--- Resets the Chronometer.
---
function obe.time._Chronometer:reset() end

--- Get Time elapsed since the Chronometer started.
---
---@return obe.time.TimeUnit
function obe.time._Chronometer:get_elapsed_time() end

--- Defines a limit to the Chronometer.
---
---@param limit obe.time.TimeUnit #The amount of milliseconds before the limit is exceeded
function obe.time._Chronometer:set_limit(limit) end

---@return obe.time.TimeUnit
function obe.time._Chronometer:get_limit() end

--- Check if the defined limit has been exceeded.
---
---@return boolean
function obe.time._Chronometer:is_over() end


---@class obe.time.FramerateCounter
obe.time._FramerateCounter = {};


--- Called when screen is refreshed.
---
function obe.time._FramerateCounter:render_tick() end

--- Called when game is updated.
---
function obe.time._FramerateCounter:update_tick() end

--- Load a new font to use when drawing the stats.
---
---@param font obe.graphics.Font #Font to use to draw the amount of fps / ups
function obe.time._FramerateCounter:load_font(font) end

--- Draws the calculated stats on the screen.
---
function obe.time._FramerateCounter:draw() end


---@class obe.time.FramerateManager
obe.time._FramerateManager = {};

--- Creates a new FramerateManager.
---
---@param window obe.system.Window #
---@return obe.time.FramerateManager
function obe.time.FramerateManager(window) end


--- Configures the FramerateManager.
---
---@param config vili.node #Configuration of the FramerateManager
function obe.time._FramerateManager:configure(config) end

--- Updates the FramerateManager (done every time in the main loop)
---
function obe.time._FramerateManager:update() end

--- Get if the engine should render everything.
---
---@return boolean
function obe.time._FramerateManager:should_render() end

---@return boolean
function obe.time._FramerateManager:should_update() end

function obe.time._FramerateManager:start() end

function obe.time._FramerateManager:reset() end

--- Get the DeltaTime.
---
---@return obe.time.TimeUnit
function obe.time._FramerateManager:get_raw_delta_time() end

--- Get the GameSpeed (DeltaTime * SpeedCoefficient)
---
---@return number
function obe.time._FramerateManager:get_delta_time() end

--- Get the SpeedCoefficient.
---
---@return number
function obe.time._FramerateManager:get_speed_coefficient() end

--- Check if Framerate is limited or not.
---
---@return boolean
function obe.time._FramerateManager:is_framerate_limited() end

--- Get the frame per second cap.
---
---@return number
function obe.time._FramerateManager:get_framerate_target() end

--- Check if vsync is enabled or not.
---
---@return boolean
function obe.time._FramerateManager:is_vsync_enabled() end

--- Set the SpeedCoefficient.
---
---@param speed number #The new SpeedCoefficient
function obe.time._FramerateManager:set_speed_coefficient(speed) end

--- Set the max framerate.
---
---@param limit number #An unsigned int containing the max framerate, 0 for no limit
function obe.time._FramerateManager:set_framerate_target(limit) end

--- Set if VerticalSync should be enabled or not.
---
---@param vsync boolean #A boolean containing if the v-sync should be enabled (true = enabled)
function obe.time._FramerateManager:set_vsync_enabled(vsync) end

---@param max_delta_time number #
function obe.time._FramerateManager:set_max_delta_time(max_delta_time) end



---@alias obe.time.TimeUnit number
--- Get the amount of seconds elapsed since epoch.
---
---@return obe.time.TimeUnit
function obe.time.epoch() end


---@type obe.time.TimeUnit
obe.time.seconds = {};

---@type obe.time.TimeUnit
obe.time.milliseconds = {};

---@type obe.time.TimeUnit
obe.time.microseconds = {};

---@type obe.time.TimeUnit
obe.time.minutes = {};

---@type obe.time.TimeUnit
obe.time.hours = {};

---@type obe.time.TimeUnit
obe.time.days = {};

---@type obe.time.TimeUnit
obe.time.weeks = {};
return obe.time;