---@meta

obe.animation = {};
---@class obe.animation.Animation : obe.types.Serializable
obe.animation._Animation = {};

--- obe.animation.Animation constructor
---
---@return obe.animation.Animation
function obe.animation.Animation() end

--- obe.animation.Animation constructor
---
---@param p0 obe.animation.Animation #
---@return obe.animation.Animation
function obe.animation.Animation(p0) end


--- Apply global Animation parameters (Sprite offset and priority)
---
---@param parameters vili.node #A vili::node that contains the following optional parameters : spriteOffsetX : x Coordinate of the Sprite Offset in the Animation in pixels. spriteOffsetY : y Coordinate of the Sprite Offset in the Animation in pixels. priority : Priority of the Animation (A higher Animation priority can't be interrupted by an Animation with a lower one).
function obe.animation._Animation:apply_parameters(parameters) end

--- Get the name of all contained AnimationGroup of the Animation.
---
---@return string[]
function obe.animation._Animation:get_all_animation_groups_names() end

--- Get the default delay of the Animation. The delay will be transferred to AnimationGroup children if not specified. The delay represents the amount of seconds between each frame of the Animation.
---
---@return obe.time.TimeUnit
function obe.animation._Animation:get_delay() end

--- Get AnimationGroup pointer by group_name. It will throws a ObEngine.Animation.Animation.AnimationGroupNotFound if the AnimationGroup is not found.
---
---@param group_name string #The name of the AnimationGroup to return
---@return obe.animation.AnimationGroup
function obe.animation._Animation:get_animation_group(group_name) end

--- Get the Animation name.
---
---@return string
function obe.animation._Animation:get_name() end

--- Get the Animation Play Mode.
---
---@return obe.animation.AnimationPlayMode
function obe.animation._Animation:get_play_mode() end

--- Get the Animation Status.
---
---@return obe.animation.AnimationStatus
function obe.animation._Animation:get_status() end

--- Get the name of the Animation to call when the AnimationStatus of the Animation is equal to AnimationStatus::Call.
---
---@return string
function obe.animation._Animation:get_next_animation() end

--- Get the name of the current AnimationGroup.
---
---@return string
function obe.animation._Animation:get_current_animation_group() end

--- Return the Animation priority.
---
---@return number
function obe.animation._Animation:get_priority() end

--- Get the current Texture displayed by the Animation.
---
---@return obe.graphics.Texture
function obe.animation._Animation:get_current_texture() end

--- Get the texture used in the Animation at the specified index.
---
---@param index number #Index of the texture to return.
---@return obe.graphics.Texture
function obe.animation._Animation:get_texture_at_index(index) end

--- Return whether the Animation is over or not.
---
---@return boolean
function obe.animation._Animation:is_over() end

--- Configure an Animation using the Animation configuration file (Vili file)
---
---@param path obe.system.Path #System::Path to the Animation config file (.ani.vili file extension)
---@param resources? obe.engine.ResourceManager #pointer to the ResourceManager that will load the textures for the Animation
function obe.animation._Animation:load_animation(path, resources) end

--- Reset the Animation (Unselect current AnimationGroup and restart AnimationCode)
---
function obe.animation._Animation:reset() end

--- Update the Animation (Updates the current AnimationGroup, executes the AnimationCode)
---
function obe.animation._Animation:update() end

--- Enables or disables anti-aliasing for textures of this animation.
---
---@param anti_aliasing boolean #should be true to enable anti_aliasing, false otherwise
function obe.animation._Animation:set_anti_aliasing(anti_aliasing) end

--- Gets the anti-aliasing status for the Animation.
---
---@return boolean
function obe.animation._Animation:is_anti_aliased() end

---@return obe.animation.AnimationState
function obe.animation._Animation:make_state() end

--- Gets the validation schema of the Serializable object as a vili node.
---
---@return vili.node
function obe.animation._Animation:schema() end

--- Dumps the content of the Serializable object to a vili node.
---
---@return vili.node
function obe.animation._Animation:dump() end

--- Loads an object from a vili node.
---
---@param data vili.node #vili node containing the data of the object
function obe.animation._Animation:load(data) end


---@class obe.animation.AnimationGroup
obe.animation._AnimationGroup = {};

--- AnimationGroup constructor.
---
---@param name string #Name of the AnimationGroup
---@return obe.animation.AnimationGroup
function obe.animation.AnimationGroup(name) end

--- obe.animation.AnimationGroup constructor
---
---@param group obe.animation.AnimationGroup #
---@return obe.animation.AnimationGroup
function obe.animation.AnimationGroup(group) end


--- Get the delay between each frame of the AnimationGroup.
---
---@return obe.time.TimeUnit
function obe.animation._AnimationGroup:get_delay() end

--- Get the current index of AnimationGroup.
---
---@return number
function obe.animation._AnimationGroup:get_current_index() end

--- Get the name of the AnimationGroup.
---
---@return string
function obe.animation._AnimationGroup:get_name() end

--- Get the AnimationGroup size.
---
---@return number
function obe.animation._AnimationGroup:get_textures_amount() end

--- Get the current Sprite of the AnimationGroup.
---
---@return obe.graphics.Texture
function obe.animation._AnimationGroup:get_current_texture() end

--- Get if the AnimationGroup is done playing.
---
---@return boolean
function obe.animation._AnimationGroup:is_over() end

--- Increment index of the current texture to be displayed.
---
---@param force? boolean #
function obe.animation._AnimationGroup:next(force) end

--- Decrement index of the current texture to be displayed.
---
---@param force? boolean #
function obe.animation._AnimationGroup:previous(force) end

--- Add a new texture to the AnimationGroup.
---
---@param texture obe.graphics.Texture #A pointer of a Texture to add to the AnimationGroup
function obe.animation._AnimationGroup:push_texture(texture) end

--- Remove the texture at the given index in the AnimationGroup.
---
---@param index number #Removes the texture at index
function obe.animation._AnimationGroup:remove_texture_by_index(index) end

--- Reset the AnimationGroup (Index to 0, Loops to 0, Delay to 0)
---
function obe.animation._AnimationGroup:reset() end

--- Set the delay between each frame of the AnimationGroup.
---
---@param delay obe.time.TimeUnit #Delay in milliseconds
function obe.animation._AnimationGroup:set_delay(delay) end

--- Set how many times the AnimationGroup should be replayed before end.
---
---@param loops number #Amount of loops to do
function obe.animation._AnimationGroup:set_loops(loops) end


---@class obe.animation.AnimationState
obe.animation._AnimationState = {};

--- obe.animation.AnimationState constructor
---
---@param parent obe.animation.Animation #
---@return obe.animation.AnimationState
function obe.animation.AnimationState(parent) end


function obe.animation._AnimationState:load() end

--- Get the Animation Status.
---
---@return obe.animation.AnimationStatus
function obe.animation._AnimationState:get_status() end

--- Get the name of the Animation to call when the AnimationStatus of the Animation is equal to AnimationStatus::Call.
---
---@return string
function obe.animation._AnimationState:get_next_animation() end

--- Get AnimationGroup pointer by group_name. It will throw a ObEngine.Animation.Animation.AnimationGroupNotFound if the AnimationGroup is not found.
---
---@param group_name string #The name of the AnimationGroup to return
---@return obe.animation.AnimationGroup
function obe.animation._AnimationState:get_animation_group(group_name) end

--- Get the name of the current AnimationGroup.
---
---@return string
function obe.animation._AnimationState:get_current_animation_group() end

--- Get the current Texture displayed by the Animation.
---
---@return obe.graphics.Texture
function obe.animation._AnimationState:get_texture() end

--- Return whether the Animation is over or not.
---
---@return boolean
function obe.animation._AnimationState:is_over() end

--- Reset the Animation (Unselect current AnimationGroup and restart AnimationCode)
---
function obe.animation._AnimationState:reset() end

--- Update the Animation (Updates the current AnimationGroup, executes the AnimationCode)
---
function obe.animation._AnimationState:update() end

---@return obe.animation.Animation
function obe.animation._AnimationState:get_animation() end


---@class obe.animation.Animator
obe.animation._Animator = {};

--- obe.animation.Animator constructor
---
---@return obe.animation.Animator
function obe.animation.Animator() end

--- obe.animation.Animator constructor
---
---@param p0 obe.animation.Animator #
---@return obe.animation.Animator
function obe.animation.Animator(p0) end


--- Clear the Animator of all Animation.
---
function obe.animation._Animator:clear() end

--- Get the name of all contained Animation.
---
---@return string[]
function obe.animation._Animator:get_all_animations_names() end

--- Get the contained Animation pointer by Animation name.
---
---@param animation_name string #Name of the Animation to get
---@return obe.animation.Animation
function obe.animation._Animator:get_animation(animation_name) end

--- Get the name of the currently played Animation.
---
---@return string
function obe.animation._Animator:get_current_animation_name() end

--- Get the current texture of the current Animation.
---
---@return obe.graphics.Texture
function obe.animation._Animator:get_current_texture() end

--- Loads the Animator It will also load all the Animation contained in the Animator. If an Animator configuration file is found it will load it.
---
---@param path obe.system.Path #
---@param resources? obe.engine.ResourceManager #
function obe.animation._Animator:load(path, resources) end

--- Set the Animation to play by name.
---
---@param key string #A std::string containing the name of the Animation to play.
function obe.animation._Animator:set_animation(key) end

--- Start or Pause the Animator (won't do anything even if updated)
---
---@param pause boolean #true if the Animator should pause, false otherwise
function obe.animation._Animator:set_paused(pause) end

--- Update the Animator and the currently played Animation.
---
function obe.animation._Animator:update() end

---@param sprite obe.graphics.Sprite #
---@param target_scale_mode? obe.animation.AnimatorTargetScaleMode #
function obe.animation._Animator:set_target(sprite, target_scale_mode) end

---@return obe.system.Path
function obe.animation._Animator:get_filesystem_path() end

---@return obe.animation.AnimatorState
function obe.animation._Animator:make_state() end


---@class obe.animation.AnimatorState
obe.animation._AnimatorState = {};

--- obe.animation.AnimatorState constructor
---
---@param parent obe.animation.Animator #
---@return obe.animation.AnimatorState
function obe.animation.AnimatorState(parent) end


--- Get the name of the currently played Animation.
---
function obe.animation._AnimatorState:load() end

---@return string
function obe.animation._AnimatorState:get_current_animation_name() end

--- Set the Animation to play by name.
---
---@param key string #A std::string containing the name of the Animation to play.
function obe.animation._AnimatorState:set_animation(key) end

--- Start or Pause the Animator (won't do anything even if updated)
---
---@param pause boolean #true if the Animator should pause, false otherwise
function obe.animation._AnimatorState:set_paused(pause) end

--- Update the Animator and the currently played Animation.
---
function obe.animation._AnimatorState:update() end

---@param sprite obe.graphics.Sprite #
---@param target_scale_mode? obe.animation.AnimatorTargetScaleMode #
function obe.animation._AnimatorState:set_target(sprite, target_scale_mode) end

function obe.animation._AnimatorState:reset() end

---@return obe.graphics.Sprite
function obe.animation._AnimatorState:get_target() end

---@return obe.animation.AnimationState
function obe.animation._AnimatorState:get_current_animation() end

---@return obe.graphics.Texture
function obe.animation._AnimatorState:get_current_texture() end

---@return obe.animation.Animator
function obe.animation._AnimatorState:get_animator() end


---@class obe.animation.ValueTweening
obe.animation._ValueTweening = {};

--- obe.animation.ValueTweening constructor
---
---@param duration obe.time.TimeUnit #
---@param easing? obe.animation.easing.EasingFunction #
---@return obe.animation.ValueTweening
function obe.animation.ValueTweening(duration, easing) end

--- obe.animation.ValueTweening constructor
---
---@param from TweenableClass #
---@param to TweenableClass #
---@param duration obe.time.TimeUnit #
---@param easing? obe.animation.easing.EasingFunction #
---@return obe.animation.ValueTweening
function obe.animation.ValueTweening(from, to, duration, easing) end


---@param from TweenableClass #
---@return obe.animation.ValueTweening
function obe.animation._ValueTweening:from(from) end

---@param to TweenableClass #
---@return obe.animation.ValueTweening
function obe.animation._ValueTweening:to(to) end

---@param easing obe.animation.easing.EasingFunction #
---@return obe.animation.ValueTweening
function obe.animation._ValueTweening:ease(easing) end

function obe.animation._ValueTweening:start() end

function obe.animation._ValueTweening:stop() end

---@param progression number #
function obe.animation._ValueTweening:seek(progression) end

function obe.animation._ValueTweening:reset() end

function obe.animation._ValueTweening:resume() end

---@return boolean
function obe.animation._ValueTweening:done() end

---@param dt number #
---@return TweenableClass
function obe.animation._ValueTweening:step(dt) end



---@alias obe.animation.AnimationPlayModeMeta obe.types.SmartEnum[obe.animation.AnimationPlayMode]

---@alias obe.animation.AnimationCommandMeta obe.types.SmartEnum[obe.animation.AnimationCommand]

---@alias obe.animation.AnimatorTargetScaleModeMeta obe.types.SmartEnum[obe.animation.AnimatorTargetScaleMode]
---@param p0 T #
---@return std.true_type
function obe.animation.template_specialization_exists_impl(p0) end


--- The Play Mode of an Animation. It indicates whether an Animation can be interrupted or not and what to do when the Animation is over TODO: /bind{AnimationPlayMode}.
---
---@class obe.animation.AnimationPlayMode
obe.animation.AnimationPlayMode = {
    OneTime = 0,
    Loop = 1,
    Force = 2,
};

--- 
---
---@class obe.animation.AnimationCommand
obe.animation.AnimationCommand = {
    Wait = 0,
    PlayGroup = 1,
    SetAnimation = 2,
};

--- The AnimationStatus indicates whether the current Animation should continue to play or call another one.
---
---@class obe.animation.AnimationStatus
obe.animation.AnimationStatus = {
    Play = 0,
    Call = 1,
};

--- Sets the scaling behaviour the Animator will apply on target.
---
---@class obe.animation.AnimatorTargetScaleMode
obe.animation.AnimatorTargetScaleMode = {
    Fit = 0,
    KeepRatio = 1,
    FixedWidth = 2,
    FixedHeight = 3,
    TextureSize = 4,
};
return obe.animation;