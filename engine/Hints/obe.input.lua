---@meta

obe.input = {};
---@class obe.input.InputAction : obe.types.Identifiable
obe.input._InputAction = {};

--- Creates a new InputAction.
---
---@param actions_events obe.event.EventGroup #Pointer to the Actions EventGroup
---@param id string #Id of the InputAction
---@return obe.input.InputAction
function obe.input.InputAction(actions_events, id) end


--- Adds an InputCondition to the InputAction.
---
---@param condition obe.input.InputCondition #An InputCondition to add to the InputAction
function obe.input._InputAction:add_condition(condition) end

--- Adds a context to the InputAction.
---
---@param context string #New context for the InputAction
function obe.input._InputAction:add_context(context) end

--- Check if the InputAction is enabled.
---
---@return boolean
function obe.input._InputAction:check() end

--- Clears all the InputCondition of the InputAction.
---
function obe.input._InputAction:clear_conditions() end

--- Get all the contexts the InputAction is in.
---
---@return string[]
function obe.input._InputAction:get_contexts() end

--- Gets the delay required between two InputAction triggerings.
---
---@return obe.time.TimeUnit
function obe.input._InputAction:get_interval() end

--- Gets the delay between two 'Hold' callbacks activations.
---
---@return obe.time.TimeUnit
function obe.input._InputAction:get_repeat() end

--- Sets the delay required between two InputAction triggerings.
---
---@param delay obe.time.TimeUnit #Delay required between two InputAction triggerings (in ms)
function obe.input._InputAction:set_interval(delay) end

--- Sets the delay between two 'Hold' callbacks activations.
---
---@param delay obe.time.TimeUnit #Delay required between two 'Hold' callbacks activations
function obe.input._InputAction:set_repeat(delay) end

--- Updates the InputAction.
---
function obe.input._InputAction:update() end

---@return obe.input.InputSource[]
function obe.input._InputAction:get_involved_input_sources() end

---@param monitors obe.input.InputButtonMonitorPtr[] #
function obe.input._InputAction:enable(monitors) end

function obe.input._InputAction:disable() end

---@return boolean
function obe.input._InputAction:is_enabled() end


---@class obe.input.InputButtonMonitor
obe.input._InputButtonMonitor = {};

--- Constructor of InputButtonMonition.
---
---@param button obe.input.InputSource #Pointer to the InputButton to monitor
---@return obe.input.InputButtonMonitor
function obe.input.InputButtonMonitor(button) end


--- Gets a pointer to the monitored InputButton.
---
---@return obe.input.InputSource
function obe.input._InputButtonMonitor:get_input_source() end

--- Gets the state of the InputButton (InputButtonState)
---
---@return obe.input.InputSourceState
function obe.input._InputButtonMonitor:get_state() end

--- Updates the InputButtonMonitor (needed to modify the linked InputButtonState)
---
---@param events obe.event.EventGroupPtr #
function obe.input._InputButtonMonitor:update(events) end

---@return boolean
function obe.input._InputButtonMonitor:check_for_refresh() end


---@class obe.input.InputCondition
obe.input._InputCondition = {};

--- obe.input.InputCondition constructor
---
---@return obe.input.InputCondition
function obe.input.InputCondition() end


--- Adds a new InputCombinationElement to the InputCondition.
---
---@param combination_element obe.input.InputCombinationElement #The InputCombinationElement to add to the InputCondition
function obe.input._InputCondition:add_combination_element(combination_element) end

--- Checks if the condition is fulfilled.
---
---@return boolean
function obe.input._InputCondition:check() end

--- Clears the InputCondition.
---
function obe.input._InputCondition:clear() end

---@param monitors obe.input.InputButtonMonitorPtr[] #
function obe.input._InputCondition:enable(monitors) end

function obe.input._InputCondition:disable() end

---@return boolean
function obe.input._InputCondition:is_enabled() end


---@class obe.input.InputManager : obe.types.Togglable
obe.input._InputManager = {};

--- Creates a new KeyboardManager.
---
---@param event_namespace obe.event.EventNamespace #
---@return obe.input.InputManager
function obe.input.InputManager(event_namespace) end


--- Get if a KeyboardAction exists.
---
---@param action_id string #Id of the KeyboardAction to check the existence
---@return boolean
function obe.input._InputManager:action_exists(action_id) end

--- Adds a new context the KeyboardManager will use.
---
---@param context string #Name of the context to add
---@return obe.input.InputManager
function obe.input._InputManager:add_context(context) end

--- Get the KeyboardAction identified by action_id if it exists.
---
---@param action_id string #Id of the KeyboardAction to retrieve
---@return obe.input.InputAction
function obe.input._InputManager:get_action(action_id) end

--- Gets all the contexts currently used by the InputManager.
---
---@return string[]
function obe.input._InputManager:get_contexts() end

--- Clears all Actions.
---
function obe.input._InputManager:clear() end

--- Clear all contexts the KeyboardManager is using.
---
function obe.input._InputManager:clear_contexts() end

--- Configure KeyboardAction from a vili configuration file.
---
---@param config vili.node #Reference to the vili ComplexAttribute used to configure the KeyboardManager
function obe.input._InputManager:configure(config) end

--- Removes a context in use.
---
---@param context string #Name of the context to remove
---@return obe.input.InputManager
function obe.input._InputManager:remove_context(context) end

--- Cleans all the contexts and adds a new one.
---
---@param context string #Name of the only context to use
function obe.input._InputManager:set_context(context) end

--- Updates the KeyboardManager.
---
function obe.input._InputManager:update() end

--- Get an InputButton from the given key.
---
---@param key string #Name of the InputButton you want to get
---@return obe.input.InputSource
function obe.input._InputManager:get_input_source(key) end

--- Get a list of all InputButtons.
---
---@return obe.input.InputSource[]
function obe.input._InputManager:get_all_input_sources() end

--- Get a list of all InputButtons with a given type.
---
---@param input_type string #
---@return obe.input.InputSource[]
function obe.input._InputManager:get_all_input_sources(input_type) end

--- Get a list of all InputButtons which are pressed.
---
---@return obe.input.InputSource[]
function obe.input._InputManager:get_pressed_input_sources() end

---@param name string #
---@return obe.input.InputButtonMonitorPtr
function obe.input._InputManager:monitor(name) end

---@param input obe.input.InputSource #
---@return obe.input.InputButtonMonitorPtr
function obe.input._InputManager:monitor(input) end

function obe.input._InputManager:require_refresh() end

function obe.input._InputManager:initialize_gamepads() end

---@param gamepad_index number #
function obe.input._InputManager:initialize_gamepad(gamepad_index) end


---@class obe.input.InputSource
obe.input._InputSource = {};

--- obe.input.InputSource constructor
---
---@param input_type string #
---@param name string #
---@param printable_char string #
---@return obe.input.InputSource
function obe.input.InputSource(input_type, name, printable_char) end

--- obe.input.InputSource constructor
---
---@param other obe.input.InputSource #
---@return obe.input.InputSource
function obe.input.InputSource(other) end


--- Get the name of the Input source.
---
---@return string
function obe.input._InputSource:get_name() end

--- Get the type of the Input source.
---
---@return string
function obe.input._InputSource:get_input_type() end

---@return string
function obe.input._InputSource:get_printable_char() end

--- Get if the key is pressed.
---
---@return boolean
function obe.input._InputSource:is_pressed() end

--- Get if the key prints a writable character.
---
---@return boolean
function obe.input._InputSource:is_printable() end


---@class obe.input.InputSourceGamepadAxis : obe.input.InputSource
obe.input._InputSourceGamepadAxis = {};

--- Creates a new InputSource representing a gamepad Axis.
---
---@param gamepad_index number #Index of the gamepad
---@param gamepad_axis sf.Joystick.Axis #Enum value of the Gamepad Axis
---@param axis_threshold Tuple_ObeInputAxisThresholdDirection_Number #
---@param name string #Name of the gamepad Axis
---@return obe.input.InputSourceGamepadAxis
function obe.input.InputSourceGamepadAxis(gamepad_index, gamepad_axis, axis_threshold, name) end


---@return number
function obe.input._InputSourceGamepadAxis:get_gamepad_index() end

--- Get Axis Position value.
---
---@return number
function obe.input._InputSourceGamepadAxis:get_axis_position() end

--- Get if the key is pressed.
---
---@return boolean
function obe.input._InputSourceGamepadAxis:is_pressed() end


---@class obe.input.InputSourceGamepadButton : obe.input.InputSource
obe.input._InputSourceGamepadButton = {};

--- Creates a new InputSource representing a Gamepad Button.
---
---@param gamepad_index number #Index of the gamepad
---@param button_index number #Index of the button of the gamepad
---@param name string #Name of the gamepad Button
---@return obe.input.InputSourceGamepadButton
function obe.input.InputSourceGamepadButton(gamepad_index, button_index, name) end


---@return number
function obe.input._InputSourceGamepadButton:get_gamepad_index() end

---@return number
function obe.input._InputSourceGamepadButton:get_button_index() end

--- Get if the key is pressed.
---
---@return boolean
function obe.input._InputSourceGamepadButton:is_pressed() end


---@class obe.input.InputSourceKeyboardKey : obe.input.InputSource
obe.input._InputSourceKeyboardKey = {};

--- Creates a new InputSource representing a Keyboard key.
---
---@param key sf.Keyboard.Key #SFML Keyboard Key
---@param printable_char string #The character printed when the key is pressed
---@return obe.input.InputSourceKeyboardKey
function obe.input.InputSourceKeyboardKey(key, printable_char) end

--- Creates a new InputSource representing a Keyboard key.
---
---@param key sf.Keyboard.Key #SFML Keyboard Key
---@param name string #Name of the Key
---@param printable_char string #The character printed when the key is pressed
---@return obe.input.InputSourceKeyboardKey
function obe.input.InputSourceKeyboardKey(key, name, printable_char) end


--- Get the SFML Keyboard Key.
---
---@return sf.Keyboard.Key
function obe.input._InputSourceKeyboardKey:get_key() end

--- Get if the key is pressed.
---
---@return boolean
function obe.input._InputSourceKeyboardKey:is_pressed() end


---@class obe.input.InputSourceMouseButton : obe.input.InputSource
obe.input._InputSourceMouseButton = {};

--- Creates a new InputSource representing a Mouse Button.
---
---@param button sf.Mouse.Button #SFML Mouse Button
---@return obe.input.InputSourceMouseButton
function obe.input.InputSourceMouseButton(button) end


--- Get the SFML Mouse Button.
---
---@return sf.Mouse.Button
function obe.input._InputSourceMouseButton:get_mouse_button() end

--- Get if the key is pressed.
---
---@return boolean
function obe.input._InputSourceMouseButton:is_pressed() end


---@class obe.input.InputSourceMouseWheelScroll : obe.input.InputSource
obe.input._InputSourceMouseWheelScroll = {};

--- Creates a new InputSource representing a Mouse Wheel Scroll.
---
---@param direction obe.input.MouseWheelScrollDirection #MouseWheel scroll direction
---@param threshold? number #scroll detection threshold
---@return obe.input.InputSourceMouseWheelScroll
function obe.input.InputSourceMouseWheelScroll(direction, threshold) end


--- Get the MouseWheel scroll direction.
---
---@return obe.input.MouseWheelScrollDirection
function obe.input._InputSourceMouseWheelScroll:get_scroll_wheel_direction() end

--- Get if the key is pressed.
---
---@return boolean
function obe.input._InputSourceMouseWheelScroll:is_pressed() end



---@alias obe.input.InputButtonMonitorPtr obe.input.InputButtonMonitor

---@alias obe.input.InputCombinationElement Tuple_ObeInputInputSource_ObeTypesFlagSetObeInputInputSourceState

---@alias obe.input.InputCombination obe.input.InputCombinationElement[]

---@alias obe.input.AxisThresholdDirectionMeta obe.types.SmartEnum[obe.input.AxisThresholdDirection]

---@alias obe.input.InputButtonStateMeta obe.types.SmartEnum[obe.input.InputSourceState]

---@alias obe.input.InputTypeMeta obe.types.SmartEnum[obe.input.InputType]

--- Trigger condition on an AxisButton input.
---
---@class obe.input.AxisThresholdDirection
obe.input.AxisThresholdDirection = {
    ---@type obe.input.AxisThresholdDirection
    Less = 0,
    ---@type obe.input.AxisThresholdDirection
    More = 1,
};

--- 
---
---@class obe.input.MouseWheelScrollDirection
obe.input.MouseWheelScrollDirection = {
    ---@type obe.input.MouseWheelScrollDirection
    Up = 0,
    ---@type obe.input.MouseWheelScrollDirection
    Down = 1,
    ---@type obe.input.MouseWheelScrollDirection
    Left = 2,
    ---@type obe.input.MouseWheelScrollDirection
    Right = 3,
};

--- Possible states of InputSource.
---
---@class obe.input.InputSourceState
obe.input.InputSourceState = {
    ---@type obe.input.InputSourceState
    Idle = 0,
    ---@type obe.input.InputSourceState
    Hold = 1,
    ---@type obe.input.InputSourceState
    Pressed = 2,
    ---@type obe.input.InputSourceState
    Released = 3,
};

--- The type of Input.
---
---@class obe.input.InputType
obe.input.InputType = {
    ---@type obe.input.InputType
    Alpha = 0,
    ---@type obe.input.InputType
    Numeric = 1,
    ---@type obe.input.InputType
    NumericNP = 2,
    ---@type obe.input.InputType
    Arrows = 3,
    ---@type obe.input.InputType
    Functions = 4,
    ---@type obe.input.InputType
    Mouse = 5,
    ---@type obe.input.InputType
    Others = 6,
    ---@type obe.input.InputType
    GamepadButton = 7,
    ---@type obe.input.InputType
    GamepadAxis = 8,
    ---@type obe.input.InputType
    ScrollWheel = 9,
};
return obe.input;