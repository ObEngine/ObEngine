---@meta

obe.graphics.canvas = {};
---@class obe.graphics.canvas.Bezier : obe.graphics.canvas.CanvasElement
---@field points obe.transform.UnitVector[] #
---@field colors obe.graphics.Color[] #
---@field precision number #
---@field Type obe.graphics.canvas.CanvasElementType #
obe.graphics.canvas._Bezier = {};

--- obe.graphics.canvas.Bezier constructor
---
---@param parent obe.graphics.canvas.Canvas #
---@param id string #
---@return obe.graphics.canvas.Bezier
function obe.graphics.canvas.Bezier(parent, id) end


--- Draw the Bezier Curve.
---
---@param target obe.graphics.RenderTarget #Target where to draw the Sprite to
function obe.graphics.canvas._Bezier:draw(target) end


---@class obe.graphics.canvas.Canvas
obe.graphics.canvas._Canvas = {};

--- Create a new Canvas.
---
---@param width number #Width of the Canvas (in pixels)
---@param height number #Height of the Canvas (in pixels)
---@return obe.graphics.canvas.Canvas
function obe.graphics.canvas.Canvas(width, height) end


--- Adds a new CanvasElement of type T to the Canvas.
---
---@param id string #Id of the new element to add to the canvas
---@return T
function obe.graphics.canvas._Canvas:add(id) end

--- Get a CanvasElement with the given id.
---
---@param id string #Id of the CanvasElement you want to retrieve
---@return obe.graphics.canvas.CanvasElement
function obe.graphics.canvas._Canvas:get(id) end

--- Render all the Canvas content to the Sprite target.
---
---@param target obe.graphics.Sprite #
function obe.graphics.canvas._Canvas:render(target) end

--- Clear all CanvasElement from the Canvas.
---
function obe.graphics.canvas._Canvas:clear() end

--- Remove a CanvasElement from the Canvas.
---
---@param id string #Id of the CanvasElement to remove
function obe.graphics.canvas._Canvas:remove(id) end

--- Get the current Texture of the Canvas.
---
---@return obe.graphics.Texture
function obe.graphics.canvas._Canvas:get_texture() end

--- Ask the Canvas to sort elements for the next rendering.
---
function obe.graphics.canvas._Canvas:requires_sort() end


---@class obe.graphics.canvas.CanvasElement : obe.types.ProtectedIdentifiable
---@field parent obe.graphics.canvas.Canvas #
---@field layer number #
---@field visible boolean #
---@field type obe.graphics.canvas.CanvasElementType #
---@field Type obe.graphics.canvas.CanvasElementType #
obe.graphics.canvas._CanvasElement = {};

--- Create a new CanvasElement.
---
---@param parent obe.graphics.canvas.Canvas #Reference to the Canvas
---@param id string #Id of the new CanvasElement
---@return obe.graphics.canvas.CanvasElement
function obe.graphics.canvas.CanvasElement(parent, id) end


--- Abstract draw method.
---
---@param target obe.graphics.RenderTarget #Target where to render the result
function obe.graphics.canvas._CanvasElement:draw(target) end

--- Change layer or object and will ask the Canvas to reorder elements automatically.
---
---@param layer number #
function obe.graphics.canvas._CanvasElement:set_layer(layer) end


---@class obe.graphics.canvas.CanvasPositionable : obe.graphics.canvas.CanvasElement
---@field position obe.transform.UnitVector #
obe.graphics.canvas._CanvasPositionable = {};

--- obe.graphics.canvas.CanvasPositionable constructor
---
---@param parent obe.graphics.canvas.Canvas #
---@param id string #
---@return obe.graphics.canvas.CanvasPositionable
function obe.graphics.canvas.CanvasPositionable(parent, id) end



---@class obe.graphics.canvas.Circle : obe.graphics.canvas.CanvasPositionable
---@field shape obe.graphics.shapes.Circle #
---@field Type obe.graphics.canvas.CanvasElementType #
obe.graphics.canvas._Circle = {};

--- Create a new Circle.
---
---@param parent obe.graphics.canvas.Canvas #Reference to the Canvas
---@param id string #Id of the new Circle
---@return obe.graphics.canvas.Circle
function obe.graphics.canvas.Circle(parent, id) end


--- Draw the Circle.
---
---@param target obe.graphics.RenderTarget #Target where to draw the Circle to
function obe.graphics.canvas._Circle:draw(target) end


---@class obe.graphics.canvas.Line : obe.graphics.canvas.CanvasElement
---@field p1 obe.transform.UnitVector #
---@field p2 obe.transform.UnitVector #
---@field thickness number #
---@field p1_color obe.graphics.Color #
---@field p2_color obe.graphics.Color #
---@field Type obe.graphics.canvas.CanvasElementType #
obe.graphics.canvas._Line = {};

--- Create a new Line.
---
---@param parent obe.graphics.canvas.Canvas #Reference to the Canvas
---@param id string #Id of the new Line
---@return obe.graphics.canvas.Line
function obe.graphics.canvas.Line(parent, id) end


--- Draw the Line.
---
---@param target obe.graphics.RenderTarget #Target where to draw the Line to
function obe.graphics.canvas._Line:draw(target) end


---@class obe.graphics.canvas.Polygon : obe.graphics.canvas.CanvasPositionable
---@field shape obe.graphics.shapes.Polygon #
---@field Type obe.graphics.canvas.CanvasElementType #
obe.graphics.canvas._Polygon = {};

--- obe.graphics.canvas.Polygon constructor
---
---@param parent obe.graphics.canvas.Canvas #
---@param id string #
---@return obe.graphics.canvas.Polygon
function obe.graphics.canvas.Polygon(parent, id) end


--- Abstract draw method.
---
---@param target obe.graphics.RenderTarget #Target where to render the result
function obe.graphics.canvas._Polygon:draw(target) end


---@class obe.graphics.canvas.Rectangle : obe.graphics.canvas.CanvasPositionable
---@field shape obe.graphics.shapes.Rectangle #
---@field size obe.transform.UnitVector #
---@field Type obe.graphics.canvas.CanvasElementType #
obe.graphics.canvas._Rectangle = {};

--- Create a new Rectangle.
---
---@param parent obe.graphics.canvas.Canvas #Reference to the Canvas
---@param id string #Id of the new Rectangle
---@return obe.graphics.canvas.Rectangle
function obe.graphics.canvas.Rectangle(parent, id) end


--- Draw the Rectangle.
---
---@param target obe.graphics.RenderTarget #Target where to draw the Rectangle to
function obe.graphics.canvas._Rectangle:draw(target) end


---@class obe.graphics.canvas.Text : obe.graphics.canvas.CanvasPositionable
---@field font_path string #
---@field shape obe.graphics.shapes.Text #
---@field h_align obe.graphics.canvas.TextHorizontalAlign #
---@field v_align obe.graphics.canvas.TextVerticalAlign #
---@field texts obe.graphics.Text[] #
---@field Type obe.graphics.canvas.CanvasElementType #
---@field text obe.graphics.Text #Returns the current Text part.
obe.graphics.canvas._Text = {};

--- Create a new Text.
---
---@param parent obe.graphics.canvas.Canvas #Reference to the Canvas
---@param id string #Id of the new Text
---@return obe.graphics.canvas.Text
function obe.graphics.canvas.Text(parent, id) end


--- Draw the Text.
---
---@param target obe.graphics.RenderTarget #Target where to draw the Text to
function obe.graphics.canvas._Text:draw(target) end

function obe.graphics.canvas._Text:refresh() end



---@alias obe.graphics.canvas.CanvasElementTypeMeta obe.types.SmartEnum[obe.graphics.canvas.CanvasElementType]

--- Type of the CanvasElement, used for identification \lua_bind{Canvas.Type}.
---
---@class obe.graphics.canvas.CanvasElementType
obe.graphics.canvas.CanvasElementType = {
    CanvasElement = 0,
    Line = 1,
    Rectangle = 2,
    Text = 3,
    Circle = 4,
    Polygon = 5,
    Bezier = 6,
};

--- Horizontal alignment state of Text \lua_bind{Canvas.TextAlignment.Horizontal}.
---
---@class obe.graphics.canvas.TextHorizontalAlign
obe.graphics.canvas.TextHorizontalAlign = {
    Left = 0,
    Center = 1,
    Right = 2,
};

--- Vertical alignment of Text \lua_bind{Canvas.TextAlignment.Vertical}.
---
---@class obe.graphics.canvas.TextVerticalAlign
obe.graphics.canvas.TextVerticalAlign = {
    Top = 0,
    Center = 1,
    Bottom = 2,
};
return obe.graphics.canvas;