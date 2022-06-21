---@meta

obe.transform = {};
---@class obe.transform.Matrix2D
obe.transform._Matrix2D = {};

--- obe.transform.Matrix2D constructor
---
---@param elements number[] #
---@return obe.transform.Matrix2D
function obe.transform.Matrix2D(elements) end


---@param vector obe.transform.UnitVector #
---@return obe.transform.UnitVector
function obe.transform._Matrix2D:product(vector) end


---@class obe.transform.Movable
obe.transform._Movable = {};


--- Set the position of the Movable using an UnitVector.
---
---@param position obe.transform.UnitVector #Position to affect to the Movable
function obe.transform._Movable:set_position(position) end

--- Moves the Movable (Adds the given position to the current one)
---
---@param position obe.transform.UnitVector #Position to add to the current Position
function obe.transform._Movable:move(position) end

--- Get the Position of the Movable.
---
---@return obe.transform.UnitVector
function obe.transform._Movable:get_position() end


---@class obe.transform.Polygon : obe.transform.UnitBasedObject, obe.transform.Movable
---@field DefaultTolerance number #
obe.transform._Polygon = {};

--- obe.transform.Polygon constructor
---
---@return obe.transform.Polygon
function obe.transform.Polygon() end

--- obe.transform.Polygon constructor
---
---@param polygon obe.transform.Polygon #
---@return obe.transform.Polygon
function obe.transform.Polygon(polygon) end


--- Adds a new Point to the Polygon at Position (x, y)
---
---@param position obe.transform.UnitVector #Coordinate of the Position where to add the new Point
---@param point_index? number #Index where to insert the new Point, Use point_index = -1 <DefaultArg> to insert at the end (between last and first Point)
function obe.transform._Polygon:add_point(position, point_index) end

--- Finds the closest Line from the given Position.
---
---@param position obe.transform.UnitVector #Position used to get the closest Line
---@return obe.transform.PolygonSegment
function obe.transform._Polygon:find_closest_segment(position) end

--- Find the closest Point from the given Position(x, y)
---
---@param position obe.transform.UnitVector #Coordinate of the Position used to get the closest Point
---@param neighbor? boolean #Get the closest neighbor of the closest Point instead of the Point
---@param excluded_points? obe.transform.point_index_t[] #A std::vector containing points you want to exclude from the calculus (Not used in neighbor check step)
---@return obe.transform.PolygonPoint
function obe.transform._Polygon:find_closest_point(position, neighbor, excluded_points) end

--- Get all the Points of the Polygon.
---
---@return obe.transform.PolygonPath
function obe.transform._Polygon:get_all_points() end

--- Get the position of the Master Point (centroid) of the Polygon.
---
---@return obe.transform.UnitVector
function obe.transform._Polygon:get_centroid() end

--- Get the number of points in the Polygon.
---
---@return number
function obe.transform._Polygon:get_points_amount() end

--- Get the Position of the first point (index 0) of the Polygon.
---
---@return obe.transform.UnitVector
function obe.transform._Polygon:get_position() end

--- Gets the current angle of the PolygonalCollider.
---
---@return number
function obe.transform._Polygon:get_rotation() end

--- Gets the segment of the Polygon at index segment.
---
---@param segment obe.transform.point_index_t #Index of the Segment to get
---@return obe.transform.PolygonSegment
function obe.transform._Polygon:get_segment(segment) end

--- Get if the Position (x, y) is on one of the side of the Polygon.
---
---@param position obe.transform.UnitVector #Coordinate of the Position to test
---@param tolerance? number #Amount of SceneUnits allowed around the position
---@return obe.transform.PolygonSegment?
function obe.transform._Polygon:get_segment_containing_point(position, tolerance) end

--- Check if the MasterPoint of the Polygon is on Position (x - tolerance <= x <= x + tolerance, y - tolerance <= tolerance <= y + tolerance)
---
---@param position obe.transform.UnitVector #Coordinate of the Position to test
---@param tolerance obe.transform.UnitVector #Position tolerance, bigger number means less precise
---@return boolean
function obe.transform._Polygon:is_centroid_near_position(position, tolerance) end

--- Check if a point of the Polygon is on Position (x - tolerance <= x <= x + tolerance, y - tolerance <= tolerance <= y + tolerance)
---
---@param position obe.transform.UnitVector #Coordinate of the Position to test
---@param tolerance obe.transform.UnitVector #Position tolerance, bigger number means less precise
---@return obe.transform.PolygonPoint?
function obe.transform._Polygon:get_point_near_position(position, tolerance) end

--- Moves the Polygon (relative to the current position)
---
---@param position obe.transform.UnitVector #UnitVector containing the offset to move the Polygon
function obe.transform._Polygon:move(position) end

--- Adds an angle to the current angle of the PolygonalCollider (will rotate all points around the given origin)
---
---@param angle number #Angle to add to the PolygonalCollider
---@param origin obe.transform.UnitVector #Origin to rotate all the points around
function obe.transform._Polygon:rotate(angle, origin) end

--- Sets the new position of the Polygon (using the point at index 0)
---
---@param position obe.transform.UnitVector #UnitVector containing the new Position of the Polygon
function obe.transform._Polygon:set_position(position) end

--- Sets the angle of the PolygonalCollider (will rotate all points around the given origin)
---
---@param angle number #Angle to set to the PolygonalCollider
---@param origin obe.transform.UnitVector #Origin to rotate all the points around
function obe.transform._Polygon:set_rotation(angle, origin) end

---@param position obe.transform.UnitVector #
function obe.transform._Polygon:set_position_from_centroid(position) end

---@return obe.transform.Rect
function obe.transform._Polygon:get_bounding_box() end


---@class obe.transform.PolygonPoint : obe.transform.UnitVector
---@field index obe.transform.point_index_t #
obe.transform._PolygonPoint = {};

--- obe.transform.PolygonPoint constructor
---
---@param parent obe.transform.Polygon #
---@param index obe.transform.point_index_t #
---@return obe.transform.PolygonPoint
function obe.transform.PolygonPoint(parent, index) end

--- obe.transform.PolygonPoint constructor
---
---@param parent obe.transform.Polygon #
---@param index obe.transform.point_index_t #
---@param position obe.transform.UnitVector #
---@return obe.transform.PolygonPoint
function obe.transform.PolygonPoint(parent, index, position) end


function obe.transform._PolygonPoint:remove() end

---@param position obe.transform.UnitVector #
---@return number
function obe.transform._PolygonPoint:distance(position) end

---@param from obe.transform.PolygonPoint.RelativePositionFrom #
---@return obe.transform.UnitVector
function obe.transform._PolygonPoint:get_relative_position(from) end

---@param from obe.transform.PolygonPoint.RelativePositionFrom #
---@param position obe.transform.UnitVector #
function obe.transform._PolygonPoint:set_relative_position(from, position) end

---@param position obe.transform.UnitVector #
function obe.transform._PolygonPoint:move(position) end


---@class obe.transform.PolygonSegment
---@field first obe.transform.PolygonPoint #
---@field second obe.transform.PolygonPoint #
obe.transform._PolygonSegment = {};

--- obe.transform.PolygonSegment constructor
---
---@param first obe.transform.PolygonPoint #
---@param second obe.transform.PolygonPoint #
---@return obe.transform.PolygonSegment
function obe.transform.PolygonSegment(first, second) end


---@return number
function obe.transform._PolygonSegment:get_angle() end

---@return number
function obe.transform._PolygonSegment:get_length() end


---@class obe.transform.Rect : obe.transform.Movable
---@field x number #
---@field y number #
---@field width number #
---@field height number #
obe.transform._Rect = {};

--- obe.transform.Rect constructor
---
---@return obe.transform.Rect
function obe.transform.Rect() end

--- obe.transform.Rect constructor
---
---@param position obe.transform.UnitVector #
---@param size obe.transform.UnitVector #
---@return obe.transform.Rect
function obe.transform.Rect(position, size) end


--- Transform the UnitVector passed by reference using the given Referential.
---
---@param vec obe.transform.UnitVector #The UnitVector you want to transform
---@param ref obe.transform.Referential #The chosen Rect::Referential
---@param type obe.transform.ReferentialConversionType #The way you want to transform your UnitVector From : Referential::TopLeft to ref To : ref to Referential::TopLeft
function obe.transform._Rect:transform_referential(vec, ref, type) end

--- Moves the Rectangle (Adds the given position to the current one)
---
---@param position obe.transform.UnitVector #Position to add to the current Position
function obe.transform._Rect:move(position) end

--- Set the Position of a specific Referential of the Rect (The opposite Point won't move)
---
---@param position obe.transform.UnitVector #Position to affect to the specific Referential
---@param ref? obe.transform.Referential #Referential you want to move
function obe.transform._Rect:set_point_position(position, ref) end

--- Move a specific Referential of the Rect (The opposite Point won't move)
---
---@param position obe.transform.UnitVector #Position to add to the specific Referential
---@param ref? obe.transform.Referential #Referential you want to move
function obe.transform._Rect:move_point(position, ref) end

--- Set the size of the Rect.
---
---@param size obe.transform.UnitVector #New size of the Rect
---@param ref? obe.transform.Referential #Referential used to resize the Rect (Referential that won't move)
function obe.transform._Rect:set_size(size, ref) end

--- Scales the Rect (Relative to the current size)
---
---@param size obe.transform.UnitVector #Size to multiply to the current size
---@param ref? obe.transform.Referential #Referential used to scale the Rect (Referential that won't move)
function obe.transform._Rect:scale(size, ref) end

--- Get the Size of the Rect.
---
---@return obe.transform.UnitVector
function obe.transform._Rect:get_size() end

--- Get the Scale Factor of the Rect.
---
---@return obe.transform.UnitVector
function obe.transform._Rect:get_scale_factor() end

---@return number
function obe.transform._Rect:get_rotation() end

---@param angle number #
---@param origin obe.transform.UnitVector #
function obe.transform._Rect:set_rotation(angle, origin) end

---@param angle number #
---@param origin obe.transform.UnitVector #
function obe.transform._Rect:rotate(angle, origin) end

--- Draws the Rect for debug purposes <REMOVE>
---
---@param surface obe.graphics.RenderTarget #
---@param x number #
---@param y number #
function obe.transform._Rect:draw(surface, x, y) end

--- Checks if the Rect intersects a specified Rect.
---
---@param rect obe.transform.Rect #The other Rect to check
---@return boolean
function obe.transform._Rect:intersects(rect) end

---@param rect obe.transform.Rect #
---@return obe.transform.Rect?
function obe.transform._Rect:intersection(rect) end


---@class obe.transform.Referential
---@field TopLeft obe.transform.Referential #Referential TopLeft.
---@field Top obe.transform.Referential #Referential Top.
---@field TopRight obe.transform.Referential #Referential TopRight.
---@field Left obe.transform.Referential #Referential Left.
---@field Center obe.transform.Referential #Referential Center.
---@field Right obe.transform.Referential #Referential Right.
---@field BottomLeft obe.transform.Referential #Referential BottomLeft.
---@field Bottom obe.transform.Referential #Referential Bottom.
---@field BottomRight obe.transform.Referential #Referential BottomRight.
---@field Referentials obe.transform.Referential[] #
obe.transform._Referential = {};

--- obe.transform.Referential constructor
---
---@return obe.transform.Referential
function obe.transform.Referential() end

--- obe.transform.Referential constructor
---
---@param x number #
---@param y number #
---@return obe.transform.Referential
function obe.transform.Referential(x, y) end


--- Get the opposite Referential in a Rect.
---
---@param axis? obe.transform.FlipAxis #
---@return obe.transform.Referential
function obe.transform._Referential:flip(axis) end

--- Get if the Referential is on the left side of a normalized Rect.
---
---@return boolean
function obe.transform._Referential:is_on_left_side() end

--- Get if the Referential is on the right side of a normalized Rect.
---
---@return boolean
function obe.transform._Referential:is_on_right_side() end

--- Get if the Referential is on the top side of a normalized Rect.
---
---@return boolean
function obe.transform._Referential:is_on_top_side() end

--- Get if the Referential is on the bottom side of a normalized Rect.
---
---@return boolean
function obe.transform._Referential:is_on_bottom_side() end

--- Get if the Referential is on a corner of a normalized Rect.
---
---@return boolean
function obe.transform._Referential:is_on_corner() end

--- Get if the Referential is on a side of a normalized Rect.
---
---@return boolean
function obe.transform._Referential:is_on_side() end

--- Get if the Referential is one of the 9 known referentials (TopLeft, Top, TopRight, Left, Center, Right, BottomLeft, Bottom, BottomRight)
---
---@return boolean
function obe.transform._Referential:is_known() end

--- Get the normalized position of a Referential in a Rect (-1 : Left / Top, 0 = Center, 1 = Right / Bottom)
---
---@return obe.transform.UnitVector
function obe.transform._Referential:get_offset() end

--- Get the name of a Referential in std::string form.
---
---@param format? string #Format (fmt) of the string returned
---@return string
function obe.transform._Referential:to_string(format) end

--- Gets a Referential based on its name.
---
---@param ref string #Name of the Referential
---@return obe.transform.Referential
function obe.transform._Referential:from_string(ref) end


---@class obe.transform.UnitBasedObject
obe.transform._UnitBasedObject = {};


--- Set the unit the Object should work with.
---
---@param unit obe.transform.Units #Unit you want the Object to work with
function obe.transform._UnitBasedObject:set_working_unit(unit) end

--- Get the unit the Object works with.
---
---@return obe.transform.Units
function obe.transform._UnitBasedObject:get_working_unit() end


---@class obe.transform.UnitVector
---@field x number #x Coordinate of the UnitVector (related to Unit)
---@field y number #y Coordinate of the UnitVector (related to Unit)
---@field unit obe.transform.Units #Unit of the UnitVector.
---@field View obe.transform.ViewStruct #Struct used for UnitVector conversions, do not modify !
---@field Screen obe.transform.ScreenStruct #Struct used for UnitVector conversions, do not modify !
obe.transform._UnitVector = {};

--- Constructor of UnitVector.
---
---@param unit? obe.transform.Units #Unit of the UnitVector
---@return obe.transform.UnitVector
function obe.transform.UnitVector(unit) end

--- Constructor (with x, y) of UnitVector.
---
---@param x number #x Coordinate of the UnitVector
---@param y number #y Coordinate of the UnitVector
---@param unit? obe.transform.Units #Unit of the UnitVector
---@return obe.transform.UnitVector
function obe.transform.UnitVector(x, y, unit) end


--- Return an UnitVector with the converted values (x, y) to the Unit you want.
---
---@param p_unit obe.transform.Units #An enum value from Transform::Units
---@return obe.transform.UnitVector
function obe.transform._UnitVector:to(p_unit) end

--- Unpacks the UnitVector to a tuple (can be used with structured bindings)
---
---@return table<number, number>
function obe.transform._UnitVector:unpack() end

---@param angle number #
---@param zero? obe.transform.UnitVector #
---@return obe.transform.UnitVector
function obe.transform._UnitVector:rotate(angle, zero) end

---@param vec obe.transform.UnitVector #
---@return number
function obe.transform._UnitVector:distance(vec) end

--- Return the length of the UnitVector.
---
---@return number
function obe.transform._UnitVector:magnitude() end


---@class obe.transform.ScreenStruct
---@field w number #
---@field h number #
obe.transform._ScreenStruct = {};



---@class obe.transform.ViewStruct
---@field w number #
---@field h number #
---@field x number #
---@field y number #
obe.transform._ViewStruct = {};




---@alias obe.transform.point_index_t number

---@alias obe.transform.PolygonPath obe.transform.PolygonPoint[]

---@alias obe.transform.UnitsMeta obe.Types.SmartEnum[obe.transform.Units]

--- Conversion Type for Referential Usage.
---
---@class obe.transform.ReferentialConversionType
obe.transform.ReferentialConversionType = {
    From = 0,
    To = 1,
};

--- Enum which contains value to indicate which kind of flip you want to perform on a Referential.
---
---@class obe.transform.FlipAxis
obe.transform.FlipAxis = {
    Horizontal = 0,
    Vertical = 1,
    Both = 2,
};

--- Different Units used to work with elements position / size in the Scene.
---
---@class obe.transform.Units
obe.transform.Units = {
    ViewPercentage = 0,
    ViewPixels = 1,
    ViewUnits = 2,
    ScenePixels = 3,
    SceneUnits = 4,
};
return obe.transform;