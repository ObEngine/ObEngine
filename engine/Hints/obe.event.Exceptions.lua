---@meta

obe.event.Exceptions = {};
---@class obe.event.Exceptions.CallbackCreationError : obe.Exception[obe.event.Exceptions.CallbackCreationError]
obe.event.Exceptions._CallbackCreationError = {};

--- obe.event.Exceptions.CallbackCreationError constructor
---
---@param event_name string #
---@param environment_id string #
---@param callback string #
---@param error string #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.CallbackCreationError
function obe.event.Exceptions.CallbackCreationError(event_name, environment_id, callback, error, info) end



---@class obe.event.Exceptions.EventAlreadyExists : obe.Exception[obe.event.Exceptions.EventAlreadyExists]
obe.event.Exceptions._EventAlreadyExists = {};

--- obe.event.Exceptions.EventAlreadyExists constructor
---
---@param event_group_identifier string #
---@param event_name string #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.EventAlreadyExists
function obe.event.Exceptions.EventAlreadyExists(event_group_identifier, event_name, info) end



---@class obe.event.Exceptions.EventExecutionError : obe.Exception[obe.event.Exceptions.EventExecutionError]
obe.event.Exceptions._EventExecutionError = {};

--- obe.event.Exceptions.EventExecutionError constructor
---
---@param event_name string #
---@param listener_id string #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.EventExecutionError
function obe.event.Exceptions.EventExecutionError(event_name, listener_id, info) end



---@class obe.event.Exceptions.EventGroupAlreadyExists : obe.Exception[obe.event.Exceptions.EventGroupAlreadyExists]
obe.event.Exceptions._EventGroupAlreadyExists = {};

--- obe.event.Exceptions.EventGroupAlreadyExists constructor
---
---@param event_namespace string #
---@param event_group string #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.EventGroupAlreadyExists
function obe.event.Exceptions.EventGroupAlreadyExists(event_namespace, event_group, info) end



---@class obe.event.Exceptions.EventGroupNotJoinable : obe.Exception[obe.event.Exceptions.EventGroupNotJoinable]
obe.event.Exceptions._EventGroupNotJoinable = {};

--- obe.event.Exceptions.EventGroupNotJoinable constructor
---
---@param event_namespace string #
---@param event_group string #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.EventGroupNotJoinable
function obe.event.Exceptions.EventGroupNotJoinable(event_namespace, event_group, info) end



---@class obe.event.Exceptions.EventNamespaceAlreadyExists : obe.Exception[obe.event.Exceptions.EventNamespaceAlreadyExists]
obe.event.Exceptions._EventNamespaceAlreadyExists = {};

--- obe.event.Exceptions.EventNamespaceAlreadyExists constructor
---
---@param event_namespace string #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.EventNamespaceAlreadyExists
function obe.event.Exceptions.EventNamespaceAlreadyExists(event_namespace, info) end



---@class obe.event.Exceptions.EventNamespaceNotJoinable : obe.Exception[obe.event.Exceptions.EventNamespaceNotJoinable]
obe.event.Exceptions._EventNamespaceNotJoinable = {};

--- obe.event.Exceptions.EventNamespaceNotJoinable constructor
---
---@param event_namespace string #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.EventNamespaceNotJoinable
function obe.event.Exceptions.EventNamespaceNotJoinable(event_namespace, info) end



---@class obe.event.Exceptions.UnknownEvent : obe.Exception[obe.event.Exceptions.UnknownEvent]
obe.event.Exceptions._UnknownEvent = {};

--- obe.event.Exceptions.UnknownEvent constructor
---
---@param event_group string #
---@param event_name string #
---@param existing_events string[] #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.UnknownEvent
function obe.event.Exceptions.UnknownEvent(event_group, event_name, existing_events, info) end



---@class obe.event.Exceptions.UnknownEventGroup : obe.Exception[obe.event.Exceptions.UnknownEventGroup]
obe.event.Exceptions._UnknownEventGroup = {};

--- obe.event.Exceptions.UnknownEventGroup constructor
---
---@param event_namespace string #
---@param event_group string #
---@param existing_groups string[] #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.UnknownEventGroup
function obe.event.Exceptions.UnknownEventGroup(event_namespace, event_group, existing_groups, info) end



---@class obe.event.Exceptions.UnknownEventNamespace : obe.Exception[obe.event.Exceptions.UnknownEventNamespace]
obe.event.Exceptions._UnknownEventNamespace = {};

--- obe.event.Exceptions.UnknownEventNamespace constructor
---
---@param event_namespace string #
---@param existing_namespaces string[] #
---@param info obe.DebugInfo #
---@return obe.event.Exceptions.UnknownEventNamespace
function obe.event.Exceptions.UnknownEventNamespace(event_namespace, existing_namespaces, info) end



return obe.event.Exceptions;