---@meta

obe.debug.render = {};
---@class obe.debug.render.ColliderRenderOptions
---@field color obe.graphics.Color #
obe.debug.render._ColliderRenderOptions = {};



---@param target obe.graphics.RenderTarget #
---@param polygon obe.transform.Polygon #
---@param draw_lines boolean #
---@param draw_points boolean #
---@param draw_centroid boolean #
---@param draw_skeleton boolean #
---@param offset obe.transform.UnitVector #
function obe.debug.render.draw_polygon(target, polygon, draw_lines, draw_points, draw_centroid, draw_skeleton, offset) end

---@param target obe.graphics.RenderTarget #
---@param collider obe.collision.ColliderComponent #
---@param render_options obe.debug.render.ColliderRenderOptions #
function obe.debug.render.draw_collider(target, collider, render_options) end

return obe.debug.render;