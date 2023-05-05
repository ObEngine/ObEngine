---@meta

vili = {};
---@class vili.const_node_iterator
vili._const_node_iterator = {};

--- vili.const_node_iterator constructor
---
---@param value array.const_iterator #
---@return vili.const_node_iterator
function vili.const_node_iterator(value) end

--- vili.const_node_iterator constructor
---
---@param value object.const_iterator #
---@return vili.const_node_iterator
function vili.const_node_iterator(value) end

--- vili.const_node_iterator constructor
---
---@param other_it vili.const_node_iterator #
---@return vili.const_node_iterator
function vili.const_node_iterator(other_it) end



---@class vili.node
vili._node = {};

--- Default constructor, node will have null type.
---
---@return vili.node
function vili.node() end

--- Same than vili::integer constructor.
---
---@param value number #
---@return vili.node
function vili.node(value) end

--- Creates a node that contains an integer.
---
---@param value vili.integer #
---@return vili.node
function vili.node(value) end

--- Creates a node that contains a number.
---
---@param value vili.number #
---@return vili.node
function vili.node(value) end

--- Creates a node that contains a string.
---
---@param value vili.string #
---@return vili.node
function vili.node(value) end

--- Creates a node that contains a string.
---
---@param value string #
---@return vili.node
function vili.node(value) end

--- Creates a node that contains a boolean.
---
---@param value vili.boolean #
---@return vili.node
function vili.node(value) end

--- Same than vili::string constructor.
---
---@param value string #
---@return vili.node
function vili.node(value) end

--- Creates a node that contains an array (vector-like container)
---
---@param value vili.array #
---@return vili.node
function vili.node(value) end

--- Creates a node that contains a object (map-like container)
---
---@param value vili.object #
---@return vili.node
function vili.node(value) end

--- node copy constructor
---
---@param copy vili.node #
---@return vili.node
function vili.node(copy) end

--- node move constructor
---
---@param move vili.node #
---@return vili.node
function vili.node(move) end


--- Retrieves the type of the underlying value of the node.
---
---@return vili.node_type
function vili._node:type() end

--- Dumps the node content as a string.
---
---@param root? boolean #
---@return string
function vili._node:dump(root) end

--- Checks if the node contains a given type.
---
---@return boolean
function vili._node:is() end

--- Checks if the node contains a given type.
---
---@return boolean
function vili._node:is() end

--- Checks whether the underlying value is a primitive (boolean, integer, number, string) or not.
---
---@return boolean
function vili._node:is_primitive() end

--- Checks whether the underlying value is a container (array, object) or not.
---
---@return boolean
function vili._node:is_container() end

--- Checks whether the node contains a value or node.
---
---@return boolean
function vili._node:is_null() end

--- Checks whether the underlying value is an integer.
---
---@return boolean
function vili._node:is_integer() end

--- Checks whether the underlying value is a number.
---
---@return boolean
function vili._node:is_number() end

--- Checks whether the underlying value is an integer or a number.
---
---@return boolean
function vili._node:is_numeric() end

--- Checks whether the underlying value is a boolean.
---
---@return boolean
function vili._node:is_boolean() end

--- Checks whether the underlying value is a string.
---
---@return boolean
function vili._node:is_string() end

--- Checks whether the underlying value is an array.
---
---@return boolean
function vili._node:is_array() end

--- Checks whether the underlying value is an object.
---
---@return boolean
function vili._node:is_object() end

--- Returns the node as the underlying type.
---
---@return T
function vili._node:as() end

--- Returns the node as the underlying type.
---
---@return std.enable_if_t[!std.is_floating_point_v[T >||! vili.PERMISSIVE_CAST,T]]
function vili._node:as() end

--- Returns the node as the underlying type This overload is only used when vili has to convert an integer to a floating point number and therefore can't return a const reference from the internal variant.
---
---@return std.enable_if_t[std.is_floating_point_v[T > && vili.PERMISSIVE_CAST,T]]
function vili._node:as() end

---@return std.enable_if_t[!std.is_floating_point_v[T >||! vili.PERMISSIVE_CAST,T]]
function vili._node:as() end

--- Returns the node as a boolean.
---
---@return vili.boolean
function vili._node:as_boolean() end

--- Returns the node as an integer.
---
---@return vili.integer
function vili._node:as_integer() end

--- Returns the node as a number.
---
---@return vili.number
function vili._node:as_number() end

--- Returns the node as a string.
---
---@return vili.string
function vili._node:as_string() end

--- Returns the node as an array.
---
---@return vili.array
function vili._node:as_array() end

--- Returns the node as an object.
---
---@return vili.object
function vili._node:as_object() end

---@param value vili.node #
function vili._node:push(value) end

--- Emplace a child node at given index.
---
---@param index number #Index of the node to emplace
---@param value value_type #Value of the node to emplace
function vili._node:emplace(index, value) end

--- Emplace a child node at given key.
---
---@param key string #Key of the node to emplace
---@param value value_type #Value of the node to emplace
function vili._node:emplace(key, value) end

---@param index number #
---@param value vili.node #
function vili._node:insert(index, value) end

---@param key string #
---@param value vili.node #
function vili._node:insert(key, value) end

---@param value vili.node #
function vili._node:merge(value) end

---@param key string #
---@return boolean
function vili._node:contains(key) end

---@param index number #
function vili._node:erase(index) end

---@param begin number #
---@param end number #
function vili._node:erase(begin, _end) end

---@param key string #
function vili._node:erase(key) end

---@return vili.node
function vili._node:front() end

---@return vili.node
function vili._node:back() end

---@return vili.node_iterator
function vili._node:begin() end

---@return vili.const_node_iterator
function vili._node:begin() end

---@return vili.node_iterator
function vili._node:_end() end

---@return vili.const_node_iterator
function vili._node:_end() end

---@return vili.object
function vili._node:items() end

---@return vili.object
function vili._node:items() end

---@param key string #
---@return vili.node
function vili._node:at(key) end

---@param index number #
---@return vili.node
function vili._node:at(index) end

---@param key string #
---@return vili.node
function vili._node:at(key) end

---@param index number #
---@return vili.node
function vili._node:at(index) end

--- Directly access underlying variant.
---
---@return vili.node_data
function vili._node:data() end

---@return number
function vili._node:size() end

---@return boolean
function vili._node:empty() end

function vili._node:clear() end

---@param type vili.node_type #
---@return vili.node
function vili._node:from_type(type) end


---@class vili.node_iterator
vili._node_iterator = {};

--- vili.node_iterator constructor
---
---@param value array.iterator #
---@return vili.node_iterator
function vili.node_iterator(value) end

--- vili.node_iterator constructor
---
---@param value object.iterator #
---@return vili.node_iterator
function vili.node_iterator(value) end

--- vili.node_iterator constructor
---
---@param other_it vili.node_iterator #
---@return vili.node_iterator
function vili.node_iterator(other_it) end




---@alias vili.node_data nil|vili.object|vili.array|vili.integer|vili.number|vili.boolean|vili.string

---@alias vili.null nil

---@alias vili.object nlohmann.fifo_map[string,vili.node]

---@alias vili.array vili.node[]

---@alias vili.integer number

---@alias vili.number number

---@alias vili.boolean boolean

---@alias vili.string string
---@param type string #
---@return vili.node_type
function vili.from_string(type) end

---@param type vili.node_type #
---@return string
function vili.to_string(type) end


---@type boolean
vili.PERMISSIVE_CAST = {};

---@type boolean
vili.VERBOSE_EXCEPTIONS = {};

---@type string
vili.true_value = {};

---@type string
vili.false_value = {};

---@type string
vili.null_typename = {};

---@type string
vili.boolean_typename = {};

---@type string
vili.integer_typename = {};

---@type string
vili.number_typename = {};

---@type string
vili.string_typename = {};

---@type string
vili.object_typename = {};

---@type string
vili.array_typename = {};

---@type string
vili.unknown_typename = {};

---@type string
vili.container_typename = {};

--- An enum representing Types of existing Nodes.
---
---@class vili.node_type
vili.node_type = {
    ---@type vili.node_type
    null = 0,
    ---@type vili.node_type
    string = 1,
    ---@type vili.node_type
    integer = 2,
    ---@type vili.node_type
    number = 3,
    ---@type vili.node_type
    boolean = 4,
    ---@type vili.node_type
    array = 5,
    ---@type vili.node_type
    object = 6,
};
return vili;