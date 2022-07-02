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

---@return obe.input.InputButton[]
function obe.input._InputAction:get_involved_buttons() end

---@param monitors obe.input.InputButtonMonitorPtr[] #
function obe.input._InputAction:enable(monitors) end

function obe.input._InputAction:disable() end

---@return boolean
function obe.input._InputAction:is_enabled() end


---@class obe.input.InputButton
obe.input._InputButton = {};

--- Creates a new InputButton representing a Keyboard key.
---
---@param key sf.Keyboard.Key #SFML Keyboard Key
---@param name string #Name of the Key
---@param return_char string #The character printed when the key is pressed
---@param type obe.input.InputType #Type of the Key (Arrows, Alpha, Numeric, NumericNP, Functions, Others)
---@return obe.input.InputButton
function obe.input.InputButton(key, name, return_char, type) end

--- Creates a new InputButton representing a Mouse Button.
---
---@param key sf.Mouse.Button #SFML Mouse Button
---@param name string #Name of the Mouse Button
---@return obe.input.InputButton
function obe.input.InputButton(key, name) end

--- Creates a new InputButton representing a Gamepad Button.
---
---@param gamepad_index number #Index of the gamepad
---@param button_index number #Index of the button of the gamepad
---@param name string #Name of the gamepad Button
---@return obe.input.InputButton
function obe.input.InputButton(gamepad_index, button_index, name) end

--- Creates a new InputButton representing a gamepad Axis.
---
---@param gamepad_index number #Index of the gamepad
---@param gamepad_axis sf.Joystick.Axis #Enum value of the Gamepad Axis
---@param detect Tuple_ObeInputAxisThresholdDirection_Number #Pair containing the check type (More / Less) and the threshold before axis activation detection
---@param name string #Name of the gamepad Axis
---@return obe.input.InputButton
function obe.input.InputButton(gamepad_index, gamepad_axis, detect, name) end

--- obe.input.InputButton constructor
---
---@param direction obe.input.MouseWheelScrollDirection #
---@param name string #
---@return obe.input.InputButton
function obe.input.InputButton(direction, name) end

--- obe.input.InputButton constructor
---
---@param other obe.input.InputButton #
---@return obe.input.InputButton
function obe.input.InputButton(other) end


---@param other obe.input.InputButton #
function obe.input._InputButton:reload(other) end

--- Get Axis Position value if InputButton is an axis (throws error otherwise)
---
---@return number
function obe.input._InputButton:get_axis_position() end

---@return number
function obe.input._InputButton:get_wheel_delta() end

--- Get the SFML Keyboard Key.
---
---@return sf.Keyboard.Key
function obe.input._InputButton:get_key() end

--- Get the name of the Key.
---
---@return string
function obe.input._InputButton:get_name() end

--- Get the type of the Key (Arrows, Alpha, Numeric, NumericNP, Functions, Others)
---
---@return obe.input.InputType
function obe.input._InputButton:get_type() end

--- Equivalent to InputButton::get_type() == input_type.
---
---@param input_type obe.input.InputType #Type to test the equivalence
---@return boolean
function obe.input._InputButton:is(input_type) end

--- Get if the key is pressed.
---
---@return boolean
function obe.input._InputButton:is_pressed() end

--- Get if the key prints a writable character.
---
---@return boolean
function obe.input._InputButton:is_writable() end


---@class obe.input.InputButtonMonitor
obe.input._InputButtonMonitor = {};

--- Constructor of InputButtonMonition.
---
---@param button obe.input.InputButton #Pointer to the InputButton to monitor
---@return obe.input.InputButtonMonitor
function obe.input.InputButtonMonitor(button) end


--- Gets a pointer to the monitored InputButton.
---
---@return obe.input.InputButton
function obe.input._InputButtonMonitor:get_button() end

--- Gets the state of the InputButton (InputButtonState)
---
---@return obe.input.InputButtonState
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
---@return obe.input.InputButton
function obe.input._InputManager:get_input(key) end

--- Get a list of all InputButtons which are pressed.
---
---@return obe.input.InputButton[]
function obe.input._InputManager:get_pressed_inputs() end

function obe.input._InputManager:require_refresh() end

function obe.input._InputManager:initialize_gamepads() end

---@param gamepad_index number #
function obe.input._InputManager:initialize_gamepad(gamepad_index) end



---@alias obe.input.AxisThresholdDirectionMeta obe.types.SmartEnum[obe.input.AxisThresholdDirection]

---@alias obe.input.InputButtonMonitorPtr obe.input.InputButtonMonitor

---@alias obe.input.InputButtonStateMeta obe.types.SmartEnum[obe.input.InputButtonState]

---@alias obe.input.InputCombinationElement Tuple_ObeInputInputButton_ObeTypesFlagSetObeInputInputButtonState

---@alias obe.input.InputCombination obe.input.InputCombinationElement[]

---@alias obe.input.InputTypeMeta obe.types.SmartEnum[obe.input.InputType]

--- 
---
---@class obe.input.MouseWheelScrollDirection
obe.input.MouseWheelScrollDirection = {
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3,
};

--- Trigger condition on an AxisButton input.
---
---@class obe.input.AxisThresholdDirection
obe.input.AxisThresholdDirection = {
    Less = 0,
    More = 1,
};

--- Possible states of InputButton.
---
---@class obe.input.InputButtonState
obe.input.InputButtonState = {
    Idle = 0,
    Hold = 1,
    Pressed = 2,
    Released = 3,
    LAST__ = 4,
};

--- The type of Input.
---
---@class obe.input.InputType
obe.input.InputType = {
    Alpha = 0,
    Numeric = 1,
    NumericNP = 2,
    Arrows = 3,
    Functions = 4,
    Mouse = 5,
    Others = 6,
    GamepadButton = 7,
    GamepadAxis = 8,
    ScrollWheel = 9,
};
return obe.input;