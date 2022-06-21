---@meta

obe.scene.Exceptions = {};
---@class obe.scene.Exceptions.ChildNotInSceneNode : obe.Exception[obe.scene.Exceptions.ChildNotInSceneNode]
obe.scene.Exceptions._ChildNotInSceneNode = {};

--- obe.scene.Exceptions.ChildNotInSceneNode constructor
---
---@param scene_node nil #
---@param child nil #
---@param info obe.DebugInfo #
---@return obe.scene.Exceptions.ChildNotInSceneNode
function obe.scene.Exceptions.ChildNotInSceneNode(scene_node, child, info) end



---@class obe.scene.Exceptions.GameObjectAlreadyExists : obe.Exception[obe.scene.Exceptions.GameObjectAlreadyExists]
obe.scene.Exceptions._GameObjectAlreadyExists = {};

--- obe.scene.Exceptions.GameObjectAlreadyExists constructor
---
---@param scene_file string #
---@param object_type string #
---@param object_id string #
---@param info obe.DebugInfo #
---@return obe.scene.Exceptions.GameObjectAlreadyExists
function obe.scene.Exceptions.GameObjectAlreadyExists(scene_file, object_type, object_id, info) end



---@class obe.scene.Exceptions.InvalidSceneFile : obe.Exception[obe.scene.Exceptions.InvalidSceneFile]
obe.scene.Exceptions._InvalidSceneFile = {};

--- obe.scene.Exceptions.InvalidSceneFile constructor
---
---@param scene_file string #
---@param info obe.DebugInfo #
---@return obe.scene.Exceptions.InvalidSceneFile
function obe.scene.Exceptions.InvalidSceneFile(scene_file, info) end



---@class obe.scene.Exceptions.MissingSceneFileBlock : obe.Exception[obe.scene.Exceptions.MissingSceneFileBlock]
obe.scene.Exceptions._MissingSceneFileBlock = {};

--- obe.scene.Exceptions.MissingSceneFileBlock constructor
---
---@param scene_file string #
---@param block_name string #
---@param info obe.DebugInfo #
---@return obe.scene.Exceptions.MissingSceneFileBlock
function obe.scene.Exceptions.MissingSceneFileBlock(scene_file, block_name, info) end



---@class obe.scene.Exceptions.SceneOnLoadCallbackError : obe.Exception[obe.scene.Exceptions.SceneOnLoadCallbackError]
obe.scene.Exceptions._SceneOnLoadCallbackError = {};

--- obe.scene.Exceptions.SceneOnLoadCallbackError constructor
---
---@param scene_file string #
---@param next_scene_file string #
---@param error_message string #
---@param info obe.DebugInfo #
---@return obe.scene.Exceptions.SceneOnLoadCallbackError
function obe.scene.Exceptions.SceneOnLoadCallbackError(scene_file, next_scene_file, error_message, info) end



---@class obe.scene.Exceptions.SceneScriptLoadingError : obe.Exception[obe.scene.Exceptions.SceneScriptLoadingError]
obe.scene.Exceptions._SceneScriptLoadingError = {};

--- obe.scene.Exceptions.SceneScriptLoadingError constructor
---
---@param scene_file string #
---@param script_path string #
---@param error_message string #
---@param info obe.DebugInfo #
---@return obe.scene.Exceptions.SceneScriptLoadingError
function obe.scene.Exceptions.SceneScriptLoadingError(scene_file, script_path, error_message, info) end



---@class obe.scene.Exceptions.UnknownCollider : obe.Exception[obe.scene.Exceptions.UnknownCollider]
obe.scene.Exceptions._UnknownCollider = {};

--- obe.scene.Exceptions.UnknownCollider constructor
---
---@param scene_file string #
---@param collider_id string #
---@param all_colliders_ids string[] #
---@param info obe.DebugInfo #
---@return obe.scene.Exceptions.UnknownCollider
function obe.scene.Exceptions.UnknownCollider(scene_file, collider_id, all_colliders_ids, info) end



---@class obe.scene.Exceptions.UnknownGameObject : obe.Exception[obe.scene.Exceptions.UnknownGameObject]
obe.scene.Exceptions._UnknownGameObject = {};

--- obe.scene.Exceptions.UnknownGameObject constructor
---
---@param scene_file string #
---@param object_id string #
---@param all_object_ids string[] #
---@param info obe.DebugInfo #
---@return obe.scene.Exceptions.UnknownGameObject
function obe.scene.Exceptions.UnknownGameObject(scene_file, object_id, all_object_ids, info) end



---@class obe.scene.Exceptions.UnknownSprite : obe.Exception[obe.scene.Exceptions.UnknownSprite]
obe.scene.Exceptions._UnknownSprite = {};

--- obe.scene.Exceptions.UnknownSprite constructor
---
---@param scene_file string #
---@param sprite_id string #
---@param all_sprites_ids string[] #
---@param info obe.DebugInfo #
---@return obe.scene.Exceptions.UnknownSprite
function obe.scene.Exceptions.UnknownSprite(scene_file, sprite_id, all_sprites_ids, info) end



return obe.scene.Exceptions;