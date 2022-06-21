---@meta

obe.graphics.shapes = {};
---@class obe.graphics.shapes.Circle : obe.graphics.shapes.Shape[obe.graphics.shapes.Circle]
---@field shape sf.CircleShape #
obe.graphics.shapes._Circle = {};

--- obe.graphics.shapes.Circle constructor
---
---@return obe.graphics.shapes.Circle
function obe.graphics.shapes.Circle() end

--- obe.graphics.shapes.Circle constructor
---
---@param shape sf.CircleShape #
---@return obe.graphics.shapes.Circle
function obe.graphics.shapes.Circle(shape) end

--- obe.graphics.shapes.Circle constructor
---
---@param circle obe.graphics.shapes.Circle #
---@return obe.graphics.shapes.Circle
function obe.graphics.shapes.Circle(circle) end


---@param radius number #
function obe.graphics.shapes._Circle:set_radius(radius) end

---@return number
function obe.graphics.shapes._Circle:get_radius() end

---@param target sf.RenderTarget #
---@param states sf.RenderStates #
function obe.graphics.shapes._Circle:draw(target, states) end


---@class obe.graphics.shapes.Polygon : obe.graphics.shapes.Shape[obe.graphics.shapes.Polygon]
---@field shape sf.ConvexShape #
obe.graphics.shapes._Polygon = {};

--- obe.graphics.shapes.Polygon constructor
---
---@return obe.graphics.shapes.Polygon
function obe.graphics.shapes.Polygon() end

--- obe.graphics.shapes.Polygon constructor
---
---@param shape sf.ConvexShape #
---@return obe.graphics.shapes.Polygon
function obe.graphics.shapes.Polygon(shape) end

--- obe.graphics.shapes.Polygon constructor
---
---@param polygon obe.graphics.shapes.Polygon #
---@return obe.graphics.shapes.Polygon
function obe.graphics.shapes.Polygon(polygon) end


---@param index number #
---@param position obe.transform.UnitVector #
function obe.graphics.shapes._Polygon:set_point_position(index, position) end

---@param index number #
---@return obe.transform.UnitVector
function obe.graphics.shapes._Polygon:get_point_position(index) end

---@param target sf.RenderTarget #
---@param states sf.RenderStates #
function obe.graphics.shapes._Polygon:draw(target, states) end


---@class obe.graphics.shapes.Rectangle : obe.graphics.shapes.Shape[obe.graphics.shapes.Rectangle]
---@field shape sf.RectangleShape #
obe.graphics.shapes._Rectangle = {};

--- obe.graphics.shapes.Rectangle constructor
---
---@return obe.graphics.shapes.Rectangle
function obe.graphics.shapes.Rectangle() end

--- obe.graphics.shapes.Rectangle constructor
---
---@param shape sf.RectangleShape #
---@return obe.graphics.shapes.Rectangle
function obe.graphics.shapes.Rectangle(shape) end

--- obe.graphics.shapes.Rectangle constructor
---
---@param rectangle obe.graphics.shapes.Rectangle #
---@return obe.graphics.shapes.Rectangle
function obe.graphics.shapes.Rectangle(rectangle) end


---@return obe.transform.UnitVector
function obe.graphics.shapes._Rectangle:get_size() end

---@param size obe.transform.UnitVector #
function obe.graphics.shapes._Rectangle:set_size(size) end

---@param target sf.RenderTarget #
---@param states sf.RenderStates #
function obe.graphics.shapes._Rectangle:draw(target, states) end


---@class obe.graphics.shapes.Text : obe.graphics.shapes.BaseShape[obe.graphics.shapes.Text]
---@field shape obe.graphics.RichText #
obe.graphics.shapes._Text = {};

--- obe.graphics.shapes.Text constructor
---
---@return obe.graphics.shapes.Text
function obe.graphics.shapes.Text() end

--- obe.graphics.shapes.Text constructor
---
---@param shape obe.graphics.RichText #
---@return obe.graphics.shapes.Text
function obe.graphics.shapes.Text(shape) end

--- obe.graphics.shapes.Text constructor
---
---@param text obe.graphics.shapes.Text #
---@return obe.graphics.shapes.Text
function obe.graphics.shapes.Text(text) end


function obe.graphics.shapes._Text:clear() end

---@param text obe.graphics.Text #
function obe.graphics.shapes._Text:append(text) end

---@return obe.graphics.Font
function obe.graphics.shapes._Text:get_font() end

---@param font obe.graphics.Font #
function obe.graphics.shapes._Text:set_font(font) end

---@return number
function obe.graphics.shapes._Text:get_character_size() end

---@param size number #
function obe.graphics.shapes._Text:set_character_size(size) end

---@param target sf.RenderTarget #
---@param states sf.RenderStates #
function obe.graphics.shapes._Text:draw(target, states) end


return obe.graphics.shapes;