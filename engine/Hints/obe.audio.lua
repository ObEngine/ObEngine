---@meta

obe.audio = {};
---@class obe.audio.AudioManager
obe.audio._AudioManager = {};

--- Initializes the underlying audio engine.
---
---@return obe.audio.AudioManager
function obe.audio.AudioManager() end


--- Loads a sound file at a given path.
---
---@param path obe.system.Path #Path to the sound file
---@param load_policy? obe.audio.LoadPolicy #The way you want to load the sound file
---@return obe.audio.Sound
function obe.audio._AudioManager:load(path, load_policy) end


---@class obe.audio.Sound
obe.audio._Sound = {};

--- obe.audio.Sound constructor
---
---@param manager SoLoud.Soloud #
---@param source SoLoud.AudioSource #
---@return obe.audio.Sound
function obe.audio.Sound(manager, source) end


---@return number
function obe.audio._Sound:get_duration() end

function obe.audio._Sound:play() end

function obe.audio._Sound:pause() end

function obe.audio._Sound:stop() end

---@param pitch number #
function obe.audio._Sound:set_pitch(pitch) end

---@return number
function obe.audio._Sound:get_pitch() end

---@param speed number #
function obe.audio._Sound:set_speed(speed) end

---@return number
function obe.audio._Sound:get_speed() end

---@return obe.audio.SoundStatus
function obe.audio._Sound:get_status() end

---@return number
function obe.audio._Sound:get_offset() end

---@param offset number #
function obe.audio._Sound:set_offset(offset) end

---@return number
function obe.audio._Sound:get_volume() end

---@param volume number #
function obe.audio._Sound:set_volume(volume) end

---@param looping boolean #
function obe.audio._Sound:set_looping(looping) end

---@return boolean
function obe.audio._Sound:is_looping() end



--- Defines how a sound should be loaded.
---
---@class obe.audio.LoadPolicy
obe.audio.LoadPolicy = {
    Normal = 0,
    Cache = 1,
    Stream = 2,
};

--- Enum that defines the current status of a sound.
---
---@class obe.audio.SoundStatus
obe.audio.SoundStatus = {
    Playing = 0,
    Paused = 1,
    Stopped = 2,
};
return obe.audio;