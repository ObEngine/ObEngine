---@meta

obe.collision = {};
---@class obe.collision.CapsuleCollider : obe.collision.Collider
---@field Type obe.collision.ColliderType #
obe.collision._CapsuleCollider = {};

--- obe.collision.CapsuleCollider constructor
---
---@return obe.collision.CapsuleCollider
function obe.collision.CapsuleCollider() end


---@return obe.collision.ColliderType
function obe.collision._CapsuleCollider:get_collider_type() end

---@return obe.transform.Rect
function obe.collision._CapsuleCollider:get_bounding_box() end

--- Get the Position of the Movable.
---
---@return obe.transform.UnitVector
function obe.collision._CapsuleCollider:get_position() end

--- Set the position of the Movable using an UnitVector.
---
---@param position obe.transform.UnitVector #Position to affect to the Movable
function obe.collision._CapsuleCollider:set_position(position) end

--- Moves the Movable (Adds the given position to the current one)
---
---@param position obe.transform.UnitVector #Position to add to the current Position
function obe.collision._CapsuleCollider:move(position) end

---@return number
function obe.collision._CapsuleCollider:get_radius() end

---@param radius number #
function obe.collision._CapsuleCollider:set_radius(radius) end


---@class obe.collision.CircleCollider : obe.collision.Collider
---@field Type obe.collision.ColliderType #
obe.collision._CircleCollider = {};

--- obe.collision.CircleCollider constructor
---
---@return obe.collision.CircleCollider
function obe.collision.CircleCollider() end


---@return obe.collision.ColliderType
function obe.collision._CircleCollider:get_collider_type() end

---@return obe.transform.Rect
function obe.collision._CircleCollider:get_bounding_box() end

--- Get the Position of the Movable.
---
---@return obe.transform.UnitVector
function obe.collision._CircleCollider:get_position() end

--- Set the position of the Movable using an UnitVector.
---
---@param position obe.transform.UnitVector #Position to affect to the Movable
function obe.collision._CircleCollider:set_position(position) end

--- Moves the Movable (Adds the given position to the current one)
---
---@param position obe.transform.UnitVector #Position to add to the current Position
function obe.collision._CircleCollider:move(position) end

---@return number
function obe.collision._CircleCollider:get_radius() end

---@param radius number #
function obe.collision._CircleCollider:set_radius(radius) end


---@class obe.collision.Collider : obe.transform.Movable
---@field Type obe.collision.ColliderType #
obe.collision._Collider = {};

--- obe.collision.Collider constructor
---
---@return obe.collision.Collider
function obe.collision.Collider() end

--- obe.collision.Collider constructor
---
---@param position obe.transform.UnitVector #
---@return obe.collision.Collider
function obe.collision.Collider(position) end


---@return obe.collision.ColliderType
function obe.collision._Collider:get_collider_type() end

--- Sets a Tag to the Collider.
---
---@param tag string #Name of the Tag you want to set to the collider
function obe.collision._Collider:set_tag(tag) end

--- Gets all the Tags from one of the Lists)
---
---@return string
function obe.collision._Collider:get_tag() end

--- Checks if two polygons are intersecting.
---
---@param collider obe.collision.Collider #The other collider to test
---@return boolean
function obe.collision._Collider:collides(collider) end

--- Gets the Maximum distance before Collision with a specific Collider.
---
---@param collider obe.collision.Collider #Collider to check the Collision with
---@param self_offset? obe.transform.UnitVector #
---@param other_offset? obe.transform.UnitVector #
---@return obe.transform.UnitVector
function obe.collision._Collider:get_offset_before_collision(collider, self_offset, other_offset) end

---@return obe.transform.Rect
function obe.collision._Collider:get_bounding_box() end


---@class obe.collision.ColliderComponent : obe.component.Component[obe.collision.ColliderComponent]
---@field ComponentType string #
obe.collision._ColliderComponent = {};

--- obe.collision.ColliderComponent constructor
---
---@param id string #
---@return obe.collision.ColliderComponent
function obe.collision.ColliderComponent(id) end

--- obe.collision.ColliderComponent constructor
---
---@param other obe.collision.ColliderComponent #
---@return obe.collision.ColliderComponent
function obe.collision.ColliderComponent(other) end


--- Dumps the content of the Serializable object to a vili node.
---
---@return vili.node
function obe.collision._ColliderComponent:dump() end

--- Loads an object from a vili node.
---
---@param data vili.node #vili node containing the data of the object
function obe.collision._ColliderComponent:load(data) end

---@return obe.collision.ColliderType
function obe.collision._ColliderComponent:get_collider_type() end

---@return string
function obe.collision._ColliderComponent:type() end

---@return obe.collision.Collider
function obe.collision._ColliderComponent:get_inner_collider() end

--- Retrieves casted collider \thints.
---
---@return ColliderClass
function obe.collision._ColliderComponent:get_inner_collider() end


---@class obe.collision.CollisionData
---@field colliders obe.collision.Collider[] #Colliders the collider touched during the collision (empty if no collision occurs)
---@field offset obe.transform.UnitVector #Maximum distance that can be traveled before collision.
obe.collision._CollisionData = {};



---@class obe.collision.CollisionSpace
obe.collision._CollisionSpace = {};

--- obe.collision.CollisionSpace constructor
---
---@return obe.collision.CollisionSpace
function obe.collision.CollisionSpace() end


--- Adds a Collider in the CollisionSpace.
---
---@param collider obe.collision.Collider #Pointer to the collider to add to the CollisionSpace
function obe.collision._CollisionSpace:add_collider(collider) end

--- Get how many Colliders are present in the Scene.
---
---@return number
function obe.collision._CollisionSpace:get_collider_amount() end

--- Get all the pointers of the Colliders in the Scene.
---
---@return std.unordered_set[obe.collision.Collider]
function obe.collision._CollisionSpace:get_all_colliders() end

--- Removes the Collider with the given Id from the Scene.
---
---@param collider obe.collision.Collider #Pointer to the collider to remove from the CollisionSpace
function obe.collision._CollisionSpace:remove_collider(collider) end

---@param collider obe.collision.Collider #
---@return boolean
function obe.collision._CollisionSpace:collides(collider) end

---@param collider obe.collision.Collider #
---@param offset? obe.transform.UnitVector #
---@return obe.transform.UnitVector
function obe.collision._CollisionSpace:get_offset_before_collision(collider, offset) end

---@param source_tag string #
---@param rejected_tag string #
function obe.collision._CollisionSpace:add_tag_to_blacklist(source_tag, rejected_tag) end

---@param source_tag string #
---@param rejected_tag string #
function obe.collision._CollisionSpace:remove_tag_to_blacklist(source_tag, rejected_tag) end

---@param source_tag string #
function obe.collision._CollisionSpace:clear_blacklist(source_tag) end

---@param source_tag string #
---@return std.unordered_set[string]
function obe.collision._CollisionSpace:get_blacklist(source_tag) end


---@class obe.collision.PolygonCollider : obe.collision.Collider
---@field Type obe.collision.ColliderType #
obe.collision._PolygonCollider = {};

--- obe.collision.PolygonCollider constructor
---
---@return obe.collision.PolygonCollider
function obe.collision.PolygonCollider() end

--- obe.collision.PolygonCollider constructor
---
---@param position obe.transform.UnitVector #
---@return obe.collision.PolygonCollider
function obe.collision.PolygonCollider(position) end


---@return obe.collision.ColliderType
function obe.collision._PolygonCollider:get_collider_type() end

---@return obe.transform.Rect
function obe.collision._PolygonCollider:get_bounding_box() end

--- Get the Position of the Movable.
---
---@return obe.transform.UnitVector
function obe.collision._PolygonCollider:get_position() end

--- Set the position of the Movable using an UnitVector.
---
---@param position obe.transform.UnitVector #Position to affect to the Movable
function obe.collision._PolygonCollider:set_position(position) end

--- Moves the Movable (Adds the given position to the current one)
---
---@param position obe.transform.UnitVector #Position to add to the current Position
function obe.collision._PolygonCollider:move(position) end

--- Adds a new Point to the Polygon at Position (x, y)
---
---@param position obe.transform.UnitVector #Coordinate of the Position where to add the new Point
---@param point_index? number #Index where to insert the new Point, Use point_index = -1 <DefaultArg> to insert at the end (between last and first Point)
function obe.collision._PolygonCollider:add_point(position, point_index) end

--- Get the number of points in the Polygon.
---
---@return number
function obe.collision._PolygonCollider:get_points_amount() end

---@return obe.transform.Polygon
function obe.collision._PolygonCollider:get_polygon() end

--- Sets the angle of the PolygonalCollider (will rotate all points around the given origin)
---
---@param angle number #Angle to set to the PolygonalCollider
function obe.collision._PolygonCollider:set_rotation(angle) end

--- Adds an angle to the current angle of the PolygonalCollider (will rotate all points around the given origin)
---
---@param angle number #Angle to add to the PolygonalCollider
function obe.collision._PolygonCollider:rotate(angle) end

--- Gets the current angle of the PolygonalCollider.
---
---@return number
function obe.collision._PolygonCollider:get_rotation() end


---@class obe.collision.RectangleCollider : obe.collision.Collider
---@field Type obe.collision.ColliderType #
obe.collision._RectangleCollider = {};

--- obe.collision.RectangleCollider constructor
---
---@return obe.collision.RectangleCollider
function obe.collision.RectangleCollider() end

--- obe.collision.RectangleCollider constructor
---
---@param size obe.transform.UnitVector #
---@return obe.collision.RectangleCollider
function obe.collision.RectangleCollider(size) end

--- obe.collision.RectangleCollider constructor
---
---@param position obe.transform.UnitVector #
---@param size obe.transform.UnitVector #
---@return obe.collision.RectangleCollider
function obe.collision.RectangleCollider(position, size) end


---@return obe.collision.ColliderType
function obe.collision._RectangleCollider:get_collider_type() end

---@return obe.transform.Rect
function obe.collision._RectangleCollider:get_bounding_box() end

--- Get the Position of the Movable.
---
---@return obe.transform.UnitVector
function obe.collision._RectangleCollider:get_position() end

--- Set the position of the Movable using an UnitVector.
---
---@param position obe.transform.UnitVector #Position to affect to the Movable
function obe.collision._RectangleCollider:set_position(position) end

--- Moves the Movable (Adds the given position to the current one)
---
---@param position obe.transform.UnitVector #Position to add to the current Position
function obe.collision._RectangleCollider:move(position) end

---@return obe.transform.UnitVector
function obe.collision._RectangleCollider:get_size() end

---@param size obe.transform.UnitVector #
function obe.collision._RectangleCollider:set_size(size) end


---@class obe.collision.Trajectory : obe.types.Togglable
obe.collision._Trajectory = {};

--- obe.collision.Trajectory constructor
---
---@param unit? obe.transform.Units #
---@return obe.collision.Trajectory
function obe.collision.Trajectory(unit) end


---@param acceleration number #
---@return obe.collision.Trajectory
function obe.collision._Trajectory:add_acceleration(acceleration) end

---@param angle number #
---@return obe.collision.Trajectory
function obe.collision._Trajectory:add_angle(angle) end

---@param check obe.collision.TrajectoryCheckFunction #
function obe.collision._Trajectory:add_check(check) end

---@param speed number #
---@return obe.collision.Trajectory
function obe.collision._Trajectory:add_speed(speed) end

---@return number
function obe.collision._Trajectory:get_acceleration() end

---@return number
function obe.collision._Trajectory:get_angle() end

---@return obe.collision.TrajectoryCheckFunction[]
function obe.collision._Trajectory:get_checks() end

---@return obe.collision.OnCollideCallback
function obe.collision._Trajectory:get_on_collide_callback() end

---@return number
function obe.collision._Trajectory:get_speed() end

---@return boolean
function obe.collision._Trajectory:is_static() end

---@return obe.transform.Units
function obe.collision._Trajectory:get_unit() end

---@param callback obe.collision.OnCollideCallback #
function obe.collision._Trajectory:on_collide(callback) end

---@param acceleration number #
---@return obe.collision.Trajectory
function obe.collision._Trajectory:set_acceleration(acceleration) end

---@param angle number #
---@return obe.collision.Trajectory
function obe.collision._Trajectory:set_angle(angle) end

---@param speed number #
---@return obe.collision.Trajectory
function obe.collision._Trajectory:set_speed(speed) end

---@param static_ boolean #
---@return obe.collision.Trajectory
function obe.collision._Trajectory:set_static(static_) end


---@class obe.collision.TrajectoryNode
obe.collision._TrajectoryNode = {};

--- obe.collision.TrajectoryNode constructor
---
---@param scene_node obe.scene.SceneNode #
---@return obe.collision.TrajectoryNode
function obe.collision.TrajectoryNode(scene_node) end


---@param id string #
---@param unit? obe.transform.Units #
---@return obe.collision.Trajectory
function obe.collision._TrajectoryNode:add_trajectory(id, unit) end

---@return obe.scene.SceneNode
function obe.collision._TrajectoryNode:get_scene_node() end

---@param id string #
---@return obe.collision.Trajectory
function obe.collision._TrajectoryNode:get_trajectory(id) end

---@param id string #
function obe.collision._TrajectoryNode:remove_trajectory(id) end

---@param collision_space obe.collision.CollisionSpace const #
---@param probe obe.collision.Collider #
function obe.collision._TrajectoryNode:set_probe(collision_space, probe) end

---@param dt number #
function obe.collision._TrajectoryNode:update(dt) end


---@class obe.collision.CollisionRejectionPair
---@field collider1 obe.collision.Collider #
---@field collider2 obe.collision.Collider #
obe.collision._CollisionRejectionPair = {};




---@alias obe.collision.ColliderTypeMeta obe.types.SmartEnum[obe.collision.ColliderType]

---@alias obe.collision.ColliderTypes obe.collision.CapsuleCollider|obe.collision.CircleCollider|obe.collision.PolygonCollider|obe.collision.RectangleCollider

---@alias obe.collision.OnCollideCallback fun(p0:obe.collision.Trajectory, p1:obe.transform.UnitVector, p2:obe.collision.Collider)

---@alias obe.collision.TrajectoryCheckFunction fun(p0:obe.collision.Trajectory, p1:obe.transform.UnitVector, p2:obe.collision.Collider)
---@param collider_type obe.collision.ColliderType #
---@return C2_TYPE
function obe.collision.collider_type_to_c2type(collider_type) end


--- 
---
---@class obe.collision.ColliderType
obe.collision.ColliderType = {
    ---@type obe.collision.ColliderType
    Collider = 0,
    ---@type obe.collision.ColliderType
    Circle = 1,
    ---@type obe.collision.ColliderType
    Rectangle = 2,
    ---@type obe.collision.ColliderType
    Capsule = 3,
    ---@type obe.collision.ColliderType
    Polygon = 4,
};
return obe.collision;