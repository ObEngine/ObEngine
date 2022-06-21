---@meta

obe.graphics.utils = {};
---@class obe.graphics.utils.DrawPolygonOptions
---@field lines boolean #
---@field points boolean #
---@field radius number #
---@field line_color obe.graphics.Color #
---@field point_color obe.graphics.Color #
---@field specific_line_color table<number, obe.graphics.Color> #
---@field specific_point_color table<number, obe.graphics.Color> #
obe.graphics.utils._DrawPolygonOptions = {};



--- Draws a Point.
---
---@param surface obe.graphics.RenderTarget #RenderSurface where to render the point
---@param x number #x Coordinate of the position of the Point
---@param y number #y Coordinate of the position of the Point
---@param radius number #Radius of the Point to draw
---@param color obe.graphics.Color #Color of the new Point
function obe.graphics.utils.draw_point(surface, x, y, radius, color) end

--- Draws a Line.
---
---@param surface obe.graphics.RenderTarget #RenderSurface where to render the line
---@param x1 number #x Coordinate of the first point of the line
---@param y1 number #y Coordinate of the first point of the line
---@param x2 number #x Coordinate of the second point of the line
---@param y2 number #y Coordinate of the second point of the line
---@param thickness number #Thickness of the line you want to draw (2 = Minimal visible size)
---@param color obe.graphics.Color #Color of the line you want to draw
function obe.graphics.utils.draw_line(surface, x1, y1, x2, y2, thickness, color) end

--- Draws a Polygon.
---
---@param surface obe.graphics.RenderTarget #RenderSurface where to render the polygon
---@param points obe.transform.UnitVector[] #List of all the Polygon points positions
---@param options obe.graphics.utils.DrawPolygonOptions #Drawing options : <lines> bool : Are the lines of the Polygon visible ? (true = visible, false = not visible) <points> bool : Are the points of the Polygon visible ? (true = visible, false = not visible) <radius> unsigned int : The radius of the points of the Polygon. <line_color> Color : Default color of the lines of the Polygon. <line_color_x> Color : Color of a specific line of the Polygon where x is the index of the line <point_color> Color : Default color of the points of the Polygon <point_color_x> Color : Color of a specific point of the Polygon where x is the index of the point
function obe.graphics.utils.draw_polygon(surface, points, options) end

return obe.graphics.utils;