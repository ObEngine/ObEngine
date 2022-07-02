---@meta

obe.collision = {};
---@class obe.collision.CollisionData
---@field colliders obe.collision.PolygonalCollider[] #Colliders the collider touched during the collision (empty if no collision occurs)
---@field offset obe.transform.UnitVector #Maximum distance that can be traveled before collision.
obe.collision._CollisionData = {};



---@class obe.collision.PolygonalCollider : obe.transform.Polygon, obe.types.Selectable, obe.component.Component[obe.collision.PolygonalCollider]
---@field ComponentType string #
obe.collision._PolygonalCollider = {};

--- Constructs a PolygonalCollider.
---
---@param id string #Id of the PolygonalCollider (Used to retrieve it for example)
---@return obe.collision.PolygonalCollider
function obe.collision.PolygonalCollider(id) end

--- obe.collision.PolygonalCollider constructor
---
---@param collider obe.collision.PolygonalCollider #
---@return obe.collision.PolygonalCollider
function obe.collision.PolygonalCollider(collider) end


--- Adds a Tag to the Collider.
---
---@param tag_type obe.collision.ColliderTagType #List where you want to add the Tag (Tag / Accepted / Rejected)
---@param tag string #Name of the Tag you want to add
function obe.collision._PolygonalCollider:add_tag(tag_type, tag) end

--- Clears Tags of the Collider.
---
---@param tag_type obe.collision.ColliderTagType #List you want to clear (Tag / Accepted /Rejected)
function obe.collision._PolygonalCollider:clear_tags(tag_type) end

--- Check if the Collider contains one of the Tag in parameter.
---
---@param tag_type obe.collision.ColliderTagType #List from where you want to check the Tags existence (Tag / Accepted / Rejected)
---@param tags string[] #List of Tags you want to check the existence
---@return boolean
function obe.collision._PolygonalCollider:matches_any_tag(tag_type, tags) end

--- Checks if the Collider contains a Tag.
---
---@param tag_type obe.collision.ColliderTagType #List from where you want to check the Tag existence (Tag / Accepted / Rejected)
---@param tag string #Name of the Tag you want to check the existence
---@return boolean
function obe.collision._PolygonalCollider:contains_tag(tag_type, tag) end

--- Gets all the Tags from one of the Lists.
---
---@param tag_type obe.collision.ColliderTagType #List where you want to get all the Tags from (Tag / Accepted / Rejected)
---@return string[]
function obe.collision._PolygonalCollider:get_all_tags(tag_type) end

--- Get the Id of the parent of the Collider (When used in a GameObject)
---
---@return string
function obe.collision._PolygonalCollider:get_parent_id() end

--- Gets the validation schema of the Serializable object as a vili node.
---
---@return vili.node
function obe.collision._PolygonalCollider:schema() end

--- Dumps the content of the PolygonalCollider.
---
---@return vili.node
function obe.collision._PolygonalCollider:dump() end

--- Loads the PolygonalCollider from a ComplexNode.
---
---@param data vili.node #ComplexNode containing the data of the PolygonalCollider
function obe.collision._PolygonalCollider:load(data) end

--- Removes a Tag of the Collider.
---
---@param tag_type obe.collision.ColliderTagType #List you want to remove a Collider from (Tag / Accepted / Rejected)
---@param tag string #Name of the Tag you want to remove
function obe.collision._PolygonalCollider:remove_tag(tag_type, tag) end

--- Set the Id of the parent of the Collider (When used in a GameObject)
---
---@param parent string #A std::string containing the Id of the parent of the Collider
function obe.collision._PolygonalCollider:set_parent_id(parent) end

---@return string
function obe.collision._PolygonalCollider:type() end

---@return obe.transform.Rect
function obe.collision._PolygonalCollider:get_bounding_box() end

--- Adds a new Point to the Polygon at Position (x, y)
---
---@param position obe.transform.UnitVector #Coordinate of the Position where to add the new Point
---@param point_index? number #Index where to insert the new Point, Use point_index = -1 <DefaultArg> to insert at the end (between last and first Point)
function obe.collision._PolygonalCollider:add_point(position, point_index) end

--- Moves the Movable (Adds the given position to the current one)
---
---@param position obe.transform.UnitVector #Position to add to the current Position
function obe.collision._PolygonalCollider:move(position) end

--- Adds an angle to the current angle of the PolygonalCollider (will rotate all points around the given origin)
---
---@param angle number #Angle to add to the PolygonalCollider
---@param origin obe.transform.UnitVector #Origin to rotate all the points around
function obe.collision._PolygonalCollider:rotate(angle, origin) end

--- Set the position of the Movable using an UnitVector.
---
---@param position obe.transform.UnitVector #Position to affect to the Movable
function obe.collision._PolygonalCollider:set_position(position) end

--- Sets the angle of the PolygonalCollider (will rotate all points around the given origin)
---
---@param angle number #Angle to set to the PolygonalCollider
---@param origin obe.transform.UnitVector #Origin to rotate all the points around
function obe.collision._PolygonalCollider:set_rotation(angle, origin) end

---@param position obe.transform.UnitVector #
function obe.collision._PolygonalCollider:set_position_from_centroid(position) end


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

---@param probe obe.collision.PolygonalCollider #
function obe.collision._TrajectoryNode:set_probe(probe) end

---@param dt number #
function obe.collision._TrajectoryNode:update(dt) end



---@alias obe.collision.ColliderTagTypeMeta obe.types.SmartEnum[obe.collision.ColliderTagType]

---@alias obe.collision.OnCollideCallback fun(p0:obe.collision.Trajectory, p1:obe.transform.UnitVector, p2:obe.collision.CollisionData)

---@alias obe.collision.TrajectoryCheckFunction fun(p0:obe.collision.Trajectory, p1:obe.transform.UnitVector, p2:obe.collision.PolygonalCollider)

--- Enum used when manipulating tags in the Collider.
---
---@class obe.collision.ColliderTagType
obe.collision.ColliderTagType = {
    Tag = 0,
    Accepted = 1,
    Rejected = 2,
};
return obe.collision;