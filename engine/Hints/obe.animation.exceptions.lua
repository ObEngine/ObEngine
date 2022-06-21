---@meta

obe.animation.exceptions = {};
---@class obe.animation.exceptions.AnimationGroupTextureIndexOverflow : obe.Exception[obe.animation.exceptions.AnimationGroupTextureIndexOverflow]
obe.animation.exceptions._AnimationGroupTextureIndexOverflow = {};

--- obe.animation.exceptions.AnimationGroupTextureIndexOverflow constructor
---
---@param group_name string #
---@param index number #
---@param maximum number #
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.AnimationGroupTextureIndexOverflow
function obe.animation.exceptions.AnimationGroupTextureIndexOverflow(group_name, index, maximum, info) end



---@class obe.animation.exceptions.AnimationTextureIndexOverflow : obe.Exception[obe.animation.exceptions.AnimationTextureIndexOverflow]
obe.animation.exceptions._AnimationTextureIndexOverflow = {};

--- obe.animation.exceptions.AnimationTextureIndexOverflow constructor
---
---@param animation string #
---@param index number #
---@param maximum number #
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.AnimationTextureIndexOverflow
function obe.animation.exceptions.AnimationTextureIndexOverflow(animation, index, maximum, info) end



---@class obe.animation.exceptions.InvalidAnimationFile : obe.Exception[obe.animation.exceptions.InvalidAnimationFile]
obe.animation.exceptions._InvalidAnimationFile = {};

--- obe.animation.exceptions.InvalidAnimationFile constructor
---
---@param path string #
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.InvalidAnimationFile
function obe.animation.exceptions.InvalidAnimationFile(path, info) end



---@class obe.animation.exceptions.InvalidEasingFunction : obe.Exception[obe.animation.exceptions.InvalidEasingFunction]
obe.animation.exceptions._InvalidEasingFunction = {};

--- obe.animation.exceptions.InvalidEasingFunction constructor
---
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.InvalidEasingFunction
function obe.animation.exceptions.InvalidEasingFunction(info) end



---@class obe.animation.exceptions.NoSelectedAnimation : obe.Exception[obe.animation.exceptions.NoSelectedAnimation]
obe.animation.exceptions._NoSelectedAnimation = {};

--- obe.animation.exceptions.NoSelectedAnimation constructor
---
---@param animator string #
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.NoSelectedAnimation
function obe.animation.exceptions.NoSelectedAnimation(animator, info) end



---@class obe.animation.exceptions.NoSelectedAnimationGroup : obe.Exception[obe.animation.exceptions.NoSelectedAnimationGroup]
obe.animation.exceptions._NoSelectedAnimationGroup = {};

--- obe.animation.exceptions.NoSelectedAnimationGroup constructor
---
---@param animation string #
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.NoSelectedAnimationGroup
function obe.animation.exceptions.NoSelectedAnimationGroup(animation, info) end



---@class obe.animation.exceptions.UnknownAnimation : obe.Exception[obe.animation.exceptions.UnknownAnimation]
obe.animation.exceptions._UnknownAnimation = {};

--- obe.animation.exceptions.UnknownAnimation constructor
---
---@param animator_path string #
---@param animation string #
---@param animations string[] #
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.UnknownAnimation
function obe.animation.exceptions.UnknownAnimation(animator_path, animation, animations, info) end



---@class obe.animation.exceptions.UnknownAnimationGroup : obe.Exception[obe.animation.exceptions.UnknownAnimationGroup]
obe.animation.exceptions._UnknownAnimationGroup = {};

--- obe.animation.exceptions.UnknownAnimationGroup constructor
---
---@param animation string #
---@param group_name string #
---@param groups string[] #
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.UnknownAnimationGroup
function obe.animation.exceptions.UnknownAnimationGroup(animation, group_name, groups, info) end



---@class obe.animation.exceptions.UnknownEasingFromEnum : obe.Exception[obe.animation.exceptions.UnknownEasingFromEnum]
obe.animation.exceptions._UnknownEasingFromEnum = {};

--- obe.animation.exceptions.UnknownEasingFromEnum constructor
---
---@param enum_value number #
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.UnknownEasingFromEnum
function obe.animation.exceptions.UnknownEasingFromEnum(enum_value, info) end



---@class obe.animation.exceptions.UnknownEasingFromString : obe.Exception[obe.animation.exceptions.UnknownEasingFromString]
obe.animation.exceptions._UnknownEasingFromString = {};

--- obe.animation.exceptions.UnknownEasingFromString constructor
---
---@param easing_name string #
---@param all_easings string[] #
---@param info obe.DebugInfo #
---@return obe.animation.exceptions.UnknownEasingFromString
function obe.animation.exceptions.UnknownEasingFromString(easing_name, all_easings, info) end



return obe.animation.exceptions;