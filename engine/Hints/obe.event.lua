---@meta

obe.event = {};
---@class obe.event.CallbackScheduler
obe.event._CallbackScheduler = {};

--- obe.event.CallbackScheduler constructor
---
---@return obe.event.CallbackScheduler
function obe.event.CallbackScheduler() end


---@param amount number #
---@return obe.event.CallbackScheduler
function obe.event._CallbackScheduler:after(amount) end

---@param amount number #
---@return obe.event.CallbackScheduler
function obe.event._CallbackScheduler:every(amount) end

--- calls the callback amount times at the rate configured in the every(x) call
---
---@param amount number #
---@return obe.event.CallbackScheduler
function obe.event._CallbackScheduler:replay(amount) end

---@param callback obe.event.Callback #
function obe.event._CallbackScheduler:run(callback) end

function obe.event._CallbackScheduler:stop() end


---@class obe.event.EventBase
obe.event._EventBase = {};

--- Creates a new Event.
---
---@param parent_name string #Identifier of the parent EventGroup
---@param name string #Name of the Event
---@param initial_state? boolean #State of the Event when created (enabled / disabled)
---@return obe.event.EventBase
function obe.event.EventBase(parent_name, name, initial_state) end


--- Get the State of the Event (enabled / disabled)
---
---@return boolean
function obe.event._EventBase:get_state() end

--- Get the name of the Event.
---
---@return string
function obe.event._EventBase:get_name() end

--- Get the identifier of the Event.
---
---@return string
function obe.event._EventBase:get_identifier() end

--- Registers a listener that will be called when the Event is triggered.
---
---@param id string #of the listener being added
---@param listener obe.event.ExternalEventListener #Listener to register
function obe.event._EventBase:add_external_listener(id, listener) end

--- Removes a Listener from the Event.
---
---@param id string #id of the Listener to unregister
function obe.event._EventBase:remove_external_listener(id) end


---@class obe.event.EventGroup
obe.event._EventGroup = {};

--- Creates a new EventGroup.
---
---@param event_namespace string #Name of the Namespace the EventGroup is in
---@param name string #Name of the EventGroup
---@return obe.event.EventGroup
function obe.event.EventGroup(event_namespace, name) end


---@return obe.event.EventGroupView
function obe.event._EventGroup:get_view() end

--- Sets if the EventGroup is joinable or not.
---
---@param joinable boolean #true if the EventGroup should be joinable, false otherwise
function obe.event._EventGroup:set_joinable(joinable) end

--- Get if the EventGroup is joinable or not.
---
---@return boolean
function obe.event._EventGroup:is_joinable() end

---@param event_name string #
---@return obe.event.EventBase
function obe.event._EventGroup:get(event_name) end

--- Get a Event contained in the EventGroup.
---
---@param event_name string #Name of the Event to get
---@return obe.event.Event[EventType]
function obe.event._EventGroup:get(event_name) end

--- Checks whether the EventGroup contains an Event with a given name or not.
---
---@param event_name string #Name of the Event to check the existence of
---@return boolean
function obe.event._EventGroup:contains(event_name) end

--- Creates a new Event in the EventGroup.
---
---@return std.enable_if_t[HasId[EventType >.value]]
function obe.event._EventGroup:add() end

---@param event_name string #
function obe.event._EventGroup:add(event_name) end

--- Removes a Event from the EventGroup.
---
---@param event_name string #Name of the Event to remove
function obe.event._EventGroup:remove(event_name) end

--- Triggers a Event.
---
---@param event EventType #event
---@return std.enable_if_t[HasId[EventType >.value]]
function obe.event._EventGroup:trigger(event) end

--- Triggers a Event.
---
---@param event_name string #name of the Event to trigger
---@param event EventType #event
function obe.event._EventGroup:trigger(event_name, event) end

--- Get the name of all Events contained in the EventGroup.
---
---@return string[]
function obe.event._EventGroup:get_events_names() end

--- Get all the Events contained in the EventGroup.
---
---@return obe.event.EventBase[]
function obe.event._EventGroup:get_events() end

--- Get the full name of the EventGroup (namespace + name)
---
---@return string
function obe.event._EventGroup:get_identifier() end

--- Get the name of the EventGroup.
---
---@return string
function obe.event._EventGroup:get_name() end

--- Register a callback for when Event::add_listener is called.
---
---@param event_name string #
---@param callback obe.event.OnListenerChange #
function obe.event._EventGroup:on_add_listener(event_name, callback) end

--- Register a callback for when Event::remote_listener is called.
---
---@param event_name string #
---@param callback obe.event.OnListenerChange #
function obe.event._EventGroup:on_remove_listener(event_name, callback) end


---@class obe.event.EventGroupView
obe.event._EventGroupView = {};

--- obe.event.EventGroupView constructor
---
---@param event_group obe.event.EventGroup #
---@return obe.event.EventGroupView
function obe.event.EventGroupView(event_group) end


--- Get the name of all Events contained in the EventGroup.
---
---@return string[]
function obe.event._EventGroupView:get_events_names() end

--- Get all the Events contained in the EventGroup.
---
---@return obe.event.EventBase[]
function obe.event._EventGroupView:get_events() end

--- Get the full name of the EventGroup (namespace + name)
---
---@return string
function obe.event._EventGroupView:get_identifier() end

--- Get the name of the EventGroup.
---
---@return string
function obe.event._EventGroupView:get_name() end

--- Get if the EventGroup is joinable or not.
---
---@return boolean
function obe.event._EventGroupView:is_joinable() end

---@param event_name string #
---@return obe.event.EventBase
function obe.event._EventGroupView:get(event_name) end

--- Get a Event contained in the EventGroup.
---
---@return obe.event.Event[EventType]
function obe.event._EventGroupView:get() end

--- Checks whether the EventGroup contains an Event with a given name or not.
---
---@param event_name string #Name of the Event to check the existence of
---@return boolean
function obe.event._EventGroupView:contains(event_name) end


---@class obe.event.EventManager
obe.event._EventManager = {};

--- obe.event.EventManager constructor
---
---@return obe.event.EventManager
function obe.event.EventManager() end


--- Updates the EventManager.
---
function obe.event._EventManager:update() end

--- Clears the EventManager.
---
function obe.event._EventManager:clear() end

---@param event_namespace string #
---@return obe.event.EventNamespace
function obe.event._EventManager:create_namespace(event_namespace) end

---@param event_namespace string #
---@return obe.event.EventNamespace
function obe.event._EventManager:join_namespace(event_namespace) end

---@param event_namespace string #
---@return obe.event.EventNamespaceView
function obe.event._EventManager:get_namespace(event_namespace) end

---@return string[]
function obe.event._EventManager:get_all_namespaces_names() end

---@return obe.event.CallbackScheduler
function obe.event._EventManager:schedule() end


---@class obe.event.EventNamespace
obe.event._EventNamespace = {};

--- obe.event.EventNamespace constructor
---
---@param name string #
---@return obe.event.EventNamespace
function obe.event.EventNamespace(name) end


--- Creates a new EventGroup (Throws an error if the EventGroup already exists)
---
---@param group string #Name of the new EventGroup
---@return obe.event.EventGroupPtr
function obe.event._EventNamespace:create_group(group) end

--- Join an existing EventGroup (Throws an error if the EventGroup does not exists or isn't joinable)
---
---@param group string #Name of the EventGroup to join
---@return obe.event.EventGroupPtr
function obe.event._EventNamespace:join_group(group) end

---@param group string #
---@return obe.event.EventGroupView
function obe.event._EventNamespace:get_group(group) end

--- Get all the names of the EventGroup in the given Namespace.
---
---@return string[]
function obe.event._EventNamespace:get_all_groups_names() end

--- Removes an existing EventGroup.
---
---@param group obe.event.EventGroup #Pointer to the EventGroup to delete
function obe.event._EventNamespace:remove_group(group) end

--- Check if an EventGroup exists in the EventNamespace.
---
---@param group string #Name of the EventGroup to search
---@return boolean
function obe.event._EventNamespace:does_group_exists(group) end

---@return obe.event.EventNamespaceView
function obe.event._EventNamespace:get_view() end

--- Sets if the EventNamespace is joinable or not.
---
---@param joinable boolean #true if the EventNamespace should be joinable, false otherwise
function obe.event._EventNamespace:set_joinable(joinable) end

--- Get if the EventNamespace is joinable or not.
---
---@return boolean
function obe.event._EventNamespace:is_joinable() end

---@return string
function obe.event._EventNamespace:get_name() end


---@class obe.event.EventNamespaceView
obe.event._EventNamespaceView = {};

--- obe.event.EventNamespaceView constructor
---
---@param event_namespace obe.event.EventNamespace #
---@return obe.event.EventNamespaceView
function obe.event.EventNamespaceView(event_namespace) end


---@param group string #
---@return obe.event.EventGroupPtr
function obe.event._EventNamespaceView:join_group(group) end

---@param group string #
---@return obe.event.EventGroupView
function obe.event._EventNamespaceView:get_group(group) end

--- Get all the names of the EventGroup in the given Namespace.
---
---@return string[]
function obe.event._EventNamespaceView:get_all_groups_names() end

--- Check if an EventGroup exists in the EventNamespace.
---
---@param group string #Name of the EventGroup to search
---@return boolean
function obe.event._EventNamespaceView:does_group_exists(group) end

---@return string
function obe.event._EventNamespaceView:get_name() end


---@class obe.event.LuaEventListener
obe.event._LuaEventListener = {};

--- obe.event.LuaEventListener constructor
---
---@param callback function #
---@return obe.event.LuaEventListener
function obe.event.LuaEventListener(callback) end




---@alias obe.event.Callback fun()

---@alias obe.event.EventGroupPtr obe.event.EventGroup

---@alias obe.event.ExternalEventListener obe.event.LuaEventListener

---@alias obe.event.OnListenerChange fun(p0:obe.event.ListenerChangeState, p1:string)
---@param self obe.event.EventGroup #
---@param name string #
function obe.event.add(self, name) end

---@param self obe.event.EventGroup #
---@param name string #
---@param data? table #
function obe.event.trigger(self, name, data) end


--- 
---
---@class obe.event.CallbackSchedulerState
obe.event.CallbackSchedulerState = {
    ---@type obe.event.CallbackSchedulerState
    Standby = 0,
    ---@type obe.event.CallbackSchedulerState
    Ready = 1,
    ---@type obe.event.CallbackSchedulerState
    Done = 2,
};

--- 
---
---@class obe.event.ListenerChangeState
obe.event.ListenerChangeState = {
    ---@type obe.event.ListenerChangeState
    Added = 0,
    ---@type obe.event.ListenerChangeState
    Removed = 1,
};
return obe.event;