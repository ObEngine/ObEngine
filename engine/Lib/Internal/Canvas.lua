local class = require("extlibs://pl.class"); -- NOTE: we are not using the global class() since it is not loaded yet
local make_reactive = require("obe://Lib/Internal/Reactive").make_reactive;

obe.canvas = {};

obe.canvas.Canvas = class();
function obe.canvas.Canvas:_init(width, height)
    self.internal = obe.graphics.canvas.Canvas(math.floor(width), math.floor(height));
    self.elements = {};
end

local function normalize_color(color, base)
    if type(color) == "table" then
        local ncolor = obe.graphics.Color();
        base = base or {r = 0, g = 0, b = 0, a = 255};
        ncolor.r = math.floor(color.r or base.r);
        ncolor.g = math.floor(color.g or base.g);
        ncolor.b = math.floor(color.b or base.b);
        ncolor.a = math.floor(color.a or base.a);
        return ncolor;
    elseif type(color) == "number" then
        local dalpha = base.a;
        color = math.floor(color);
        return obe.graphics.Color(color, color, color, dalpha);
    elseif type(color) == "string" then
        local new_color = obe.graphics.Color();
        new_color:from_string(color);
        return new_color;
    elseif type(color) == "userdata" then
        return color;
    end
end

local function convert_horizontal_align(align)
    if type(align) == "string" then
        if align == "Left" then
            return obe.graphics.canvas.TextHorizontalAlign.Left;
        elseif align == "Center" then
            return obe.graphics.canvas.TextHorizontalAlign.Center;
        elseif align == "Right" then
            return obe.graphics.canvas.TextHorizontalAlign.Right;
        else
            error(("Horizontal Alignment '%s' does not exists, use one of those [Left, Center, Right]"):format(align));
        end
    else
        if align == obe.graphics.canvas.TextHorizontalAlign.Left then
            return "Left";
        elseif align == obe.graphics.canvas.TextHorizontalAlign.Center then
            return "Center";
        elseif align == obe.graphics.canvas.TextHorizontalAlign.Right then
            return "Right";
        end
    end
end

local function convert_vertical_align(align)
    if type(align) == "string" then
        if align == "Top" then
            return obe.graphics.canvas.TextVerticalAlign.Top;
        elseif align == "Center" then
            return obe.graphics.canvas.TextVerticalAlign.Center;
        elseif align == "Bottom" then
            return obe.graphics.canvas.TextVerticalAlign.Bottom;
        else
            error(("Vertical Alignment '%s' does not exists, use one of those [Top, Center, Bottom]"):format(align));
        end
    else
        if align == obe.graphics.canvas.TextVerticalAlign.Top then
            return "Top";
        elseif align == obe.graphics.canvas.TextVerticalAlign.Center then
            return "Center";
        elseif align == obe.graphics.canvas.TextVerticalAlign.Bottom then
            return "Bottom";
        end
    end
end

local SHAPE_SCHEMAS = {};

SHAPE_SCHEMAS.Drawable = make_reactive {
    type = "Drawable",
    getters = {
        layer = function(self)
            return self.layer;
        end,
        visible = function(self)
            return self.visible;
        end,
        id = function(self)
            return self:get_id();
        end
    },
    setters = {
        layer = function(self, layer)
            self:set_layer(layer or 1);
        end,
        visible = function(self, visible)
            self.visible = visible;
        end
    }
}

SHAPE_SCHEMAS.Line = make_reactive {
    type = "Line",
    bases = {SHAPE_SCHEMAS.Drawable},
    getters = {
        p1 = {
            priority = {"unit"},
            getters = {
                x = function(self)
                    return self.p1.x;
                end,
                y = function(self)
                    return self.p1.y;
                end,
                unit = function(self)
                    return self.p1.unit;
                end,
                color = {
                    getters = {
                        r = function(self)
                            return self.p1_color.r;
                        end,
                        g = function(self)
                            return self.p1_color.g;
                        end,
                        b = function(self)
                            return self.p1_color.b;
                        end,
                        a = function(self)
                            return self.p1_color.a;
                        end
                    },
                    setters = {
                        r = function(self, r)
                            self.p1_color.r = r or 0;
                        end,
                        g = function(self, g)
                            self.p1_color.g = g or 0;
                        end,
                        b = function(self, b)
                            self.p1_color.b = b or 0;
                        end,
                        a = function(self, a)
                            self.p1_color.a = a or 255;
                        end
                    }
                }
            },
            setters = {
                x = function(self, x)
                    self.p1.x = x or 0;
                end,
                y = function(self, y)
                    self.p1.y = y or 0;
                end,
                unit = function(self, unit)
                    self.p1.unit = unit or obe.transform.Units.ScenePixels;
                end,
                color = function(self, color)
                    self.p1_color = normalize_color(color, self.p1_color);
                end
            }
        },
        p2 = {
            priority = {"unit"},
            getters = {
                x = function(self)
                    return self.p2.x;
                end,
                y = function(self)
                    return self.p2.y;
                end,
                unit = function(self)
                    return self.p2.unit;
                end,
                color = {
                    getters = {
                        r = function(self)
                            return self.p2_color.r;
                        end,
                        g = function(self)
                            return self.p2_color.g;
                        end,
                        b = function(self)
                            return self.p2_color.b;
                        end,
                        a = function(self)
                            return self.p2_color.a;
                        end
                    },
                    setters = {
                        r = function(self, r)
                            self.p2_color.r = r or 0;
                        end,
                        g = function(self, g)
                            self.p2_color.g = g or 0;
                        end,
                        b = function(self, b)
                            self.p2_color.b = b or 0;
                        end,
                        a = function(self, a)
                            self.p2_color.a = a or 255;
                        end
                    }
                }
            },
            setters = {
                x = function(self, x)
                    self.p2.x = x or 0;
                end,
                y = function(self, y)
                    self.p2.y = y or 0;
                end,
                unit = function(self, unit)
                    self.p2.unit = unit or obe.transform.Units.ScenePixels;
                end,
                color = function(self, color)
                    self.p2_color = normalize_color(color, self.p2_color);
                end
            }
        },
        unit = function(self)
            return self.p1.unit;
        end,
        thickness = function(self)
            return self.thickness;
        end,
        color = {
            getters = {
                r = function(self)
                    return self.p1_color.r;
                end,
                g = function(self)
                    return self.p1_color.g;
                end,
                b = function(self)
                    return self.p1_color.b;
                end,
                a = function(self)
                    return self.p1_color.a;
                end
            },
            setters = {
                r = function(self, r)
                    self.p1_color.r = r or 0;
                    self.p2_color.r = r or 0;
                end,
                g = function(self, g)
                    self.p1_color.g = g or 0;
                    self.p2_color.g = g or 0;
                end,
                b = function(self, b)
                    self.p1_color.b = b or 0;
                    self.p2_color.b = b or 0;
                end,
                a = function(self, a)
                    self.p1_color.a = a or 255;
                    self.p2_color.a = a or 255;
                end
            }
        }
    },
    setters = {
        unit = function(self, unit)
            self.p1.unit = unit or obe.transform.Units.ScenePixels;
            self.p2.unit = unit or obe.transform.Units.ScenePixels;
        end,
        thickness = function(self, thickness)
            self.thickness = thickness or 1;
        end,
        color = function(self, color)
            self.p1_color = normalize_color(color, self.p1_color);
            self.p2_color = normalize_color(color, self.p2_color);
        end,
        p1 = function(self, p1)
            if type(p1) == "table" then
                if type(p1.x) == "number" then
                    self.p1.x = p1.x;
                end
                if type(p1.y) == "number" then
                    self.p1.y = p1.y;
                end
                if p1.color then
                    self.p1_color = normalize_color(p1.color, self.p1_color);
                end
                if p1.unit then
                    self.p1.unit = p1.unit or obe.transform.Units.ScenePixels;
                end
            end
        end,
        p2 = function(self, p2)
            if type(p2) == "table" then
                if type(p2.x) == "number" then
                    self.p2.x = p2.x;
                end
                if type(p2.y) == "number" then
                    self.p2.y = p2.y;
                end
                if p2.color then
                    self.p2_color = normalize_color(p2.color, self.p2_color);
                end
                if p2.unit then
                    self.p2.unit = p2.unit or obe.transform.Units.ScenePixels;
                end
            end
        end
    }
};

SHAPE_SCHEMAS.Shape = make_reactive {
    type = "Shape",
    bases = {SHAPE_SCHEMAS.Drawable},
    priority = {"unit"},
    getters = {
        x = function(self)
            return self.position.x;
        end,
        y = function(self)
            return self.position.y;
        end,
        unit = function(self)
            return self.position.unit;
        end,
        angle = function(self)
            return self.shape:get_rotation();
        end,
        scale = {
            getters = {
                x = function(self)
                    return self.shape:get_scale().x;
                end,
                y = function(self)
                    return self.shape:get_scale().y;
                end
            },
            setters = {
                x = function(self, x)
                    local y = self.shape:get_scale().y;
                    self.shape:set_scale(x, y);
                end,
                y = function(self, y)
                    local x = self.shape:get_scale().x;
                    self.shape:set_scale(x, y);
                end
            }
        },
        outline = {
            getters = {
                color = {
                    getters = {
                        r = function(self)
                            return self.shape:get_outline_color().r;
                        end,
                        g = function(self)
                            return self.shape:get_outline_color().g;
                        end,
                        b = function(self)
                            return self.shape:get_outline_color().b;
                        end,
                        a = function(self)
                            return self.shape:get_outline_color().a;
                        end
                    },
                    setters = {
                        r = function(self, r)
                            local color_buffer = self.shape:get_outline_color();
                            color_buffer.r = r or 0;
                            self.shape:set_outline_color(color_buffer);
                        end,
                        g = function(self, g)
                            local color_buffer = self.shape:get_outline_color();
                            color_buffer.g = g or 0;
                            self.shape:set_outline_color(color_buffer);
                        end,
                        b = function(self, b)
                            local color_buffer = self.shape:get_outline_color();
                            color_buffer.b = b or 0;
                            self.shape:set_outline_color(color_buffer);
                        end,
                        a = function(self, a)
                            local color_buffer = self.shape:get_outline_color();
                            color_buffer.a = a or 255;
                            self.shape:set_outline_color(color_buffer);
                        end
                    }
                },
                thickness = function(self)
                    return self.shape:get_outline_thickness();
                end
            },
            setters = {
                color = function(self, color)
                    self.shape:set_outline_color(
                        normalize_color(
                            color, self.shape:get_outline_color()
                        )
                    );
                end,
                thickness = function(self, thickness)
                    self.shape:set_outline_thickness(thickness or 1);
                end
            }
        },
        color = {
            getters = {
                r = function(self)
                    return self.shape:get_fill_color().r;
                end,
                g = function(self)
                    return self.shape:get_fill_color().g;
                end,
                b = function(self)
                    return self.shape:get_fill_color().b;
                end,
                a = function(self)
                    return self.shape:get_fill_color().a;
                end
            },
            setters = {
                r = function(self, r)
                    local fill_color = self.shape:get_fill_color();
                    fill_color.r = r or 0;
                    self.shape:set_fill_color(fill_color);
                end,
                g = function(self, g)
                    local fill_color = self.shape:get_fill_color();
                    fill_color.g = g or 0;
                    self.shape:set_fill_color(fill_color);
                end,
                b = function(self, b)
                    local fill_color = self.shape:get_fill_color();
                    fill_color.b = b or 0;
                    self.shape:set_fill_color(fill_color);
                end,
                a = function(self, a)
                    local fill_color = self.shape:get_fill_color();
                    fill_color.a = a or 255;
                    self.shape:set_fill_color(fill_color);
                end
            }
        }
    },
    setters = {
        outline = function(self, outline)
            if type(outline) == "table" then
                if outline.color then
                    self.shape:set_outline_color(
                        normalize_color(
                            outline.color, self.shape:get_outline_color()
                        )
                    );
                end
                if type(outline.thickness) == "number" then
                    self.shape:set_outline_thickness(outline.thickness);
                end
            else
                error("Invalid argument #1 to 'outline' (table expected, got " .. type(outline) .. ")");
            end
        end,
        color = function(self, color)
            self.shape:set_fill_color(
                normalize_color(color, self.shape:get_fill_color())
            );
        end,
        x = function(self, x)
            self.position.x = x;
            self.shape:set_position(self.position);
        end,
        y = function(self, y)
            self.position.y = y;
            self.shape:set_position(self.position);
        end,
        unit = function(self, unit)
            self.position.unit = unit or obe.transform.Units.ScenePixels;
        end,
        angle = function(self, angle)
            self.shape:set_rotation(angle or 0);
        end,
        scale = function(self, scale)
            if type(scale) == "number" then
                self.shape:set_scale(scale, scale);
            elseif type(scale) == "table" then
                self.shape:set_scale(scale.x or 1, scale.y or 1);
            end
        end,
        texture = function(self, texture)
            local texture_path = obe.system.Path(texture);
            self.shape:set_texture(Engine.Resources:get_texture(texture_path));
        end
    }
}

SHAPE_SCHEMAS.Rectangle = make_reactive {
    type = "Rectangle",
    bases = {SHAPE_SCHEMAS.Shape},
    priority = {"unit"},
    getters = {
        width = function(self)
            return self.size.x;
        end,
        height = function(self)
            return self.size.y;
        end
    },
    setters = {
        width = function(self, width)
            self.size.x = width;
            self.shape:set_size(self.size);
        end,
        height = function(self, height)
            self.size.y = height
            self.shape:set_size(self.size);
        end,
        unit = function(self, unit)
            self.position.unit = unit or obe.transform.Units.ScenePixels;
            self.size.unit = unit or obe.transform.Units.ScenePixels;
        end
    }
}

SHAPE_SCHEMAS.Circle = make_reactive {
    type = "Circle",
    bases = {SHAPE_SCHEMAS.Shape},
    getters = {
        radius = function(self)
            return self.shape:get_radius();
        end,
        width = function(self)
            return self.shape:get_global_bounds().width;
        end,
        height = function(self)
            return self.shape:get_global_bounds().height;
        end
    },
    setters = {
        radius = function(self, radius)
            return self.shape:set_radius(radius);
        end
    }
}

local function position_to_unit_vector(position)
    if type(position) == "table" then
        local x = position.x or position[1];
        local y = position.y or position[2];
        local unit = position.unit or position[3] or obe.transform.Units.ScenePixels;
        position = obe.transform.UnitVector(x, y, unit);
    end
    return position;
end

SHAPE_SCHEMAS.Polygon = make_reactive {
    type = "Polygon",
    bases = {SHAPE_SCHEMAS.Shape},
    getters = {
        points = {
            getters = {
                __number = function(self, index)
                    return self.shape:get_point_position(index);
                end
            },
            setters = {
                __number = function(self, index, position)
                    position = position_to_unit_vector(position);
                    self.shape:set_point_position(index - 1, position);
                end
            }
        }
    },
    setters = {
        points = function(self, points)
            for k, v in pairs(points) do
                local position = position_to_unit_vector(v);
                self.shape:set_point_position(k - 1, position);
            end
        end
    }
}

SHAPE_SCHEMAS.Bezier = make_reactive {
    type = "Bezier",
    bases = {SHAPE_SCHEMAS.Drawable},
    getters = {
        points = {
            getters = {
                __number = function(self, index)
                    return self.points[index];
                end
            },
            setters = {
                __number = function(self, index, position)
                    self.points[index - 1] = position_to_unit_vector(position);
                end
            }
        },
        precision = function(self)
            return self.precision;
        end
    },
    setters = {
        points = function(self, points)
            for k, v in pairs(points) do
                local color = v.color or self.colors[k - 1] or obe.graphics.Color(255, 255, 255);
                color = normalize_color(color);
                table.insert(self.points, position_to_unit_vector(v));
                table.insert(self.colors, color);
                -- self.points[k - 1] = position_to_unit_vector(v);
            end
        end,
        precision = function(self, precision)
            self.precision = precision;
        end
    }
}

SHAPE_SCHEMAS.Text = make_reactive {
    type = "Text",
    bases = {SHAPE_SCHEMAS.Shape},
    priority = {"font", "size", "color", "outline", "align"},
    getters = {
        text = function(self)
            local full_text = "";
            for _, text in pairs(self.texts) do
                full_text = full_text .. text.string;
            end
            return full_text;
        end,
        size = function(self)
            return self.shape:get_character_size();
        end,
        font = function(self)
            return self.font_path;
        end,
        width = function(self)
            return self.shape:get_global_bounds().width;
        end,
        height = function(self)
            return self.shape:get_global_bounds().height;
        end,
        align = {
            getters = {
                h = function(self)
                    return convert_horizontal_align(self.h_align);
                end,
                horizontal = function(self)
                    return convert_horizontal_align(self.h_align);
                end,
                v = function(self)
                    return convert_vertical_align(self.v_align);
                end,
                vertical = function(self)
                    return convert_vertical_align(self.v_align);
                end
            },
            setters = {
                h = function(self, h)
                    self.h_align = convert_horizontal_align(h);
                end,
                horizontal = function(self, h)
                    self.h_align = convert_horizontal_align(h);
                end,
                v = function(self, v)
                    self.v_align = convert_vertical_align(v);
                end,
                vertical = function(self, v)
                    self.v_align = convert_vertical_align(v);
                end
            }
        },
        color = {
            getters = {
                r = function(self)
                    return self.text.color.r;
                end,
                g = function(self)
                    return self.text.color.g;
                end,
                b = function(self)
                    return self.text.color.b;
                end,
                a = function(self)
                    return self.text.color.a;
                end
            },
            setters = {
                r = function(self, r)
                    self.text.color.r = r;
                    self:refresh();
                end,
                g = function(self, g)
                    self.text.color.g = g;
                    self:refresh();
                end,
                b = function(self, b)
                    self.text.color.b = b;
                    self:refresh();
                end,
                a = function(self, a)
                    self.text.color.a = a;
                    self:refresh();
                end
            }
        }
    },
    setters = {
        text = function(self, text)
            if self.font_path == "" then
                error("@Canvas.Text.setters.text : Need to set @font before @text");
            end
            self.text.string = text;
            self:refresh();
        end,
        size = function(self, size)
            self.shape:set_character_size(size);
        end,
        font = function(self, font)
            self.font_path = font;
            self.shape:set_font(Engine.Resources:get_font(font));
        end,
        color = function(self, color)
            self.text.color = normalize_color(color);
            self:refresh();
        end,
        outline = function(self, outline)
            if type(outline) == "table" then
                if outline.color then
                    self.text.outline = normalize_color(outline.color);
                    self:refresh();
                end
                if type(outline.thickness) == "number" then
                    self.text.thickness = outline.thickness;
                    self:refresh();
                end
            end
        end,
        align = function(self, al)
            if al.h or al.horizontal then
                self.h_align = convert_horizontal_align(al.h or al.horizontal);
            end
            if al.v or al.vertical then
                self.v_align = convert_vertical_align(al.v or al.vertical);
            end
        end
    }
}

SHAPE_SCHEMAS.NinePatch = make_reactive {
    type = "NinePatch",
    bases = {SHAPE_SCHEMAS.Shape},
    priority = {"unit"},
    getters = {
        width = function(self)
            return self.shape:get_size():to(self.position.unit).x;
        end,
        height = function(self)
            return self.shape:get_size():to(self.position.unit).y;
        end,
    },
    setters = {
        width = function(self, width)
            local size = self.shape:get_size():to(self.position.unit);
            size.x = width;
            self.shape:set_size(size);
        end,
        height = function(self, height)
            local size = self.shape:get_size():to(self.position.unit);
            size.y = height;
            self.shape:set_size(size);
        end,
        texture = function(self, texture)
            if type(texture) == "string" then
                self.shape:set_texture(Engine.Resources:get_texture(obe.system.Path(texture)));
            else
                error("not implemented");
            end
        end
    }
}

function obe.canvas.Canvas:_generate_id(id)
    if type(id) == "string" and self.internal:get(id) ~= nil then
        error(("CanvasElement '%s' already exists !"):format(id));
    end
    while id == nil or self.internal:get(id) ~= nil do
        id = obe.utils.string
                 .get_random_key(obe.utils.string.Alphabet .. obe.utils.string.Numbers, 12);
    end
    return id;
end

function obe.canvas.Canvas:Line(id)
    id = self:_generate_id(id);
    self.elements[id] = SHAPE_SCHEMAS.Line(self.internal:Line(id));
    return self.elements[id];
end

function obe.canvas.Canvas:Rectangle(id)
    id = self:_generate_id(id);
    self.elements[id] = SHAPE_SCHEMAS.Rectangle(self.internal:Rectangle(id));
    return self.elements[id];
end

function obe.canvas.Canvas:Text(id)
    id = self:_generate_id(id);
    self.elements[id] = SHAPE_SCHEMAS.Text(self.internal:Text(id));
    self.elements[id].font = "Data/Fonts/NotoSans.ttf";
    return self.elements[id];
end

function obe.canvas.Canvas:Circle(id)
    id = self:_generate_id(id);
    self.elements[id] = SHAPE_SCHEMAS.Circle(self.internal:Circle(id));
    return self.elements[id];
end

function obe.canvas.Canvas:Polygon(id)
    id = self:_generate_id(id);
    self.elements[id] = SHAPE_SCHEMAS.Polygon(self.internal:Polygon(id));
    return self.elements[id];
end

function obe.canvas.Canvas:Bezier(id)
    id = self:_generate_id(id);
    self.elements[id] = SHAPE_SCHEMAS.Bezier(self.internal:Bezier(id));
    return self.elements[id];
end

function obe.canvas.Canvas:NinePatch(id)
    id = self:_generate_id(id);
    self.elements[id] = SHAPE_SCHEMAS.NinePatch(self.internal:NinePatch(id));
    return self.elements[id];
end

function obe.canvas.Canvas:Sprite(id)
    id = self:_generate_id(id);
    error("not implemented yet");
    -- self.elements[id] = SHAPE_SCHEMAS.Sprite(self.internal:Sprite(id));
    -- return self.elements[id];
end

function obe.canvas.Canvas:render()
    self.internal:render();
    return self.internal:get_texture();
end

function obe.canvas.Canvas:clear()
    self.elements = {};
    self.internal:clear();
end

function obe.canvas.Canvas:remove(element)
    self.elements[element] = nil;
    self.internal:remove(element);
end
