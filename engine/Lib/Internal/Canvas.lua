local class = require("extlibs://pl.class"); -- NOTE: we are not using the global class() since it is not loaded yet
local tablex = require("extlibs://pl.tablex");

obe.canvas = {};

obe.canvas.Canvas = class();
function obe.canvas.Canvas:_init(width, height, usecache)
    self.internal = obe.graphics.canvas.Canvas(math.floor(width), math.floor(height));
    self.elements = {};
    self.useCache = usecache or false;
    self.bases = {
        Line = obe.canvas.MakeMT({obe.canvas.Bases.Drawable, obe.canvas.Bases.Line}, self.useCache),
        Rectangle = obe.canvas.MakeMT(
            {obe.canvas.Bases.Drawable, obe.canvas.Bases.Shape, obe.canvas.Bases.Rectangle},
                self.useCache
        ),
        Text = obe.canvas.MakeMT(
            {obe.canvas.Bases.Drawable, obe.canvas.Bases.Shape, obe.canvas.Bases.Text},
                self.useCache
        ),
        Circle = obe.canvas.MakeMT(
            {obe.canvas.Bases.Drawable, obe.canvas.Bases.Shape, obe.canvas.Bases.Circle},
                self.useCache
        ),
        Polygon = obe.canvas.MakeMT(
            {obe.canvas.Bases.Drawable, obe.canvas.Bases.Shape, obe.canvas.Bases.Polygon},
                self.useCache
        ),
        Bezier = obe.canvas.MakeMT(
            {obe.canvas.Bases.Drawable, obe.canvas.Bases.Bezier}, self.useCache
        )
    };
end

function obe.canvas.normalize_color(color, base)
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
        local newColor = obe.graphics.Color();
        newColor:from_string(color);
        return newColor;
    elseif type(color) == "userdata" then
        return color;
    end
end

function obe.canvas.ConvertHAlign(align)
    if type(align) == "string" then
        if align == "Left" then
            return obe.graphics.canvas.TextHorizontalAlign.Left;
        elseif align == "Center" then
            return obe.graphics.canvas.TextHorizontalAlign.Center;
        elseif align == "Right" then
            return obe.graphics.canvas.TextHorizontalAlign.Right;
        else
            error(
                "Horizontal Alignment", align,
                    "does not exists, use one of those [Left, Center, Right]"
            )
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

function obe.canvas.ConvertVAlign(align)
    if type(align) == "string" then
        if align == "Top" then
            return obe.graphics.canvas.TextVerticalAlign.Top;
        elseif align == "Center" then
            return obe.graphics.canvas.TextVerticalAlign.Center;
        elseif align == "Bottom" then
            return obe.graphics.canvas.TextVerticalAlign.Bottom;
        else
            error(
                "Vertical Alignment", align,
                    "does not exists, use one of those [Top, Center, Botton]"
            )
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

obe.canvas.Bases = {};

function obe.canvas.ApplyCache(element)
    local mt = getmetatable(element);
    -- print("Cache :", inspect(mt.__cache));
    if #mt.__priority > 0 then
        for k, v in pairs(mt.__priority) do
            if mt.__cache[v] then
                obe.canvas.__set(element, v, mt.__cache[v]);
                mt.__cache[v] = nil;
            end
        end
    end
    for k, v in pairs(mt.__cache) do
        obe.canvas.__set(element, k, v);
    end
    for k, v in pairs(mt.__getters) do
        if type(v) == "table" then
            obe.canvas.ApplyCache(v);
        end
    end
    mt.__cache = {};
end

function obe.canvas.__set_cached(tbl, key, value)
    local k = getmetatable(tbl);
    if type(value) == "table" then
        k.__getters[key](value);
    else
        k.__cache[key] = value;
        k.__rcache[key] = value;
    end
end

function obe.canvas.__get_cached(tbl, key)
    local k = getmetatable(tbl);
    if k.__rcache[key] and type(k.__rcache[key]) ~= "table" then
        return k.__rcache[key];
    else
        if type(k.__getters[key]) == "function" then
            return k.__getters[key](tbl.ref);
        elseif type(key) == "number" and not k.__getters[key] and k.__getters.__number then
            return setmetatable(tbl, k.__getters.__number(tbl.ref, key));
        elseif type(k.__getters[key]) == "table" then
            -- print("Found table", inspect(k.__getters[key]));
            return setmetatable(tbl, k.__getters[key]);
        end
    end
end

function obe.canvas.__set(tbl, key, value)
    local k = getmetatable(tbl);
    if type(key) == "number" and not k.__setters[key] and k.__setters.__number then
        k.__setters.__number(tbl.ref, key, value);
    else
        if k.__setters[key] then
            k.__setters[key](tbl.ref, value);
        else
            error("Can't find obe.canvas.Canvas attribute : " .. tostring(key));
        end
    end
end

function obe.canvas.__get(tbl, key)
    local k = getmetatable(tbl);
    if type(k.__getters[key]) == "function" then
        return k.__getters[key](tbl.ref);
    elseif type(key) == "number" and not k.__getters[key] and k.__getters.__number then
        k.__getters.__number(tbl.ref)
    elseif type(k.__getters[key]) == "table" then
        if rawget(tbl, key) == nil then
            rawset(tbl, key, setmetatable({ref = rawget(tbl, "ref")}, k.__getters[key]));
        end
        return rawget(tbl, key);
    end
end

function obe.canvas.__call(tbl, values, usecache)
    values = values or {};
    local mt = getmetatable(tbl);
    if usecache then
        for k, v in pairs(values) do
            mt.__cache[k] = v;
        end
    else
        if #mt.__priority > 0 then
            for k, v in pairs(mt.__priority) do
                if values[v] then
                    obe.canvas.__set(tbl, v, values[v]);
                    values[v] = nil;
                end
            end
        end
        for k, v in pairs(values) do
            obe.canvas.__set(tbl, k, v);
        end
    end
    return tbl;
end

function obe.canvas.MakeMT(bases, usecache)
    usecache = usecache or false;
    local getters = {};
    local setters = {};
    local priority = {};

    for _, base in pairs(bases) do
        if base.priority then
            for _, priorityName in pairs(base.priority) do
                if not tablex.find(priority, priorityName) then
                    table.insert(priority, priorityName);
                end
            end
        end
        for getterName, getterValue in pairs(base.getters) do
            getters[getterName] = getterValue;
        end
        for setterName, setterValue in pairs(base.setters) do
            setters[setterName] = setterValue;
        end
    end
    for key, getter in pairs(getters) do
        if type(getter) == "table" then
            getters[key] = obe.canvas.MakeMT({getter}, usecache);
        end
    end
    for key, setter in pairs(setters) do
        if type(setter) == "table" then
            setters[key] = obe.canvas.MakeMT({setter}, usecache);
        end
    end
    local getfunc = usecache and obe.canvas.__get_cached or obe.canvas.__get;
    local setfunc = usecache and obe.canvas.__set_cached or obe.canvas.__set;
    local mt = {
        __getters = getters,
        __setters = setters,
        __priority = priority,
        __index = getfunc,
        __newindex = setfunc,
        __call = function(t, v)
            return obe.canvas.__call(t, v, usecache)
        end,
        __cache = {},
        __rcache = {}
    };

    return mt;
end

function obe.canvas.Canvas:InstanciateMT(type, internal)
    local mt = self.bases[type];
    return setmetatable({type = type, ref = internal}, mt);
end

obe.canvas.Bases.Drawable = {
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

obe.canvas.Bases.Line = {
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
                    self.p1_color = obe.canvas.normalize_color(color, self.p1_color);
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
                    self.p2_color = obe.canvas.normalize_color(color, self.p2_color);
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
            self.p1_color = obe.canvas.normalize_color(color, self.p1_color);
            self.p2_color = obe.canvas.normalize_color(color, self.p2_color);
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
                    self.p1_color = obe.canvas.normalize_color(p1.color, self.p1_color);
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
                    self.p2_color = obe.canvas.normalize_color(p2.color, self.p2_color);
                end
                if p2.unit then
                    self.p2.unit = p2.unit or obe.transform.Units.ScenePixels;
                end
            end
        end
    }
};

obe.canvas.Bases.Shape = {
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
                        obe.canvas.normalize_color(
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
                    local colorBuffer = self.shape:get_fill_color();
                    colorBuffer.r = r or 0;
                    self.shape:set_fill_color(colorBuffer);
                end,
                g = function(self, g)
                    local colorBuffer = self.shape:get_fill_color();
                    colorBuffer.g = g or 0;
                    self.shape:set_fill_color(colorBuffer);
                end,
                b = function(self, b)
                    local colorBuffer = self.shape:get_fill_color();
                    colorBuffer.b = b or 0;
                    self.shape:set_fill_color(colorBuffer);
                end,
                a = function(self, a)
                    local colorBuffer = self.shape:get_fill_color();
                    colorBuffer.a = a or 255;
                    self.shape:set_fill_color(colorBuffer);
                end
            }
        }
    },
    setters = {
        outline = function(self, outline)
            if type(outline) == "table" then
                if outline.color then
                    self.shape:set_outline_color(
                        obe.canvas.normalize_color(
                            outline.color, self.shape:get_outline_color()
                        )
                    );
                end
                if type(outline.thickness) == "number" then
                    self.shape:set_outline_thickness(outline.thickness);
                end
            end
        end,
        color = function(self, color)
            self.shape:set_fill_color(
                obe.canvas.normalize_color(color, self.shape:get_fill_color())
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

obe.canvas.Bases.Rectangle = {
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

obe.canvas.Bases.Circle = {
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

function positionToUnitVector(position)
    if type(position) == "table" then
        local x = position.x or position[1];
        local y = position.y or position[2];
        local unit = position.unit or position[3] or obe.transform.Units.ScenePixels;
        position = obe.transform.UnitVector(x, y, unit);
    end
    return position;
end
obe.canvas.Bases.Polygon = {
    getters = {
        points = {
            getters = {
                __number = function(self, index)
                    return self.shape:get_point_position(index);
                end
            },
            setters = {
                __number = function(self, index, position)
                    position = positionToUnitVector(position);
                    self.shape:set_point_position(index - 1, position);
                end
            }
        }
    },
    setters = {
        points = function(self, points)
            for k, v in pairs(points) do
                local position = positionToUnitVector(v);
                self.shape:set_point_position(k - 1, position);
            end
        end
    }
}

obe.canvas.Bases.Bezier = {
    getters = {
        points = {
            getters = {
                __number = function(self, index)
                    return self.points[index];
                end
            },
            setters = {
                __number = function(self, index, position)
                    self.points[index - 1] = positionToUnitVector(position);
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
                color = obe.canvas.normalize_color(color);
                table.insert(self.points, positionToUnitVector(v));
                table.insert(self.colors, color);
                -- self.points[k - 1] = positionToUnitVector(v);
            end
        end,
        precision = function(self, precision)
            self.precision = precision;
        end
    }
}

obe.canvas.Bases.Text = {
    priority = {"font", "size", "color", "outline", "align"},
    getters = {
        text = function(self)
            local fullText = "";
            for _, text in pairs(self.texts) do
                fullText = fullText .. text.string;
            end
            return fullText;
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
                    return obe.canvas.ConvertHAlign(self.h_align);
                end,
                horizontal = function(self)
                    return obe.canvas.ConvertHAlign(self.h_align);
                end,
                v = function(self)
                    return obe.canvas.ConvertVAlign(self.v_align);
                end,
                vertical = function(self)
                    return obe.canvas.ConvertVAlign(self.v_align);
                end
            },
            setters = {
                h = function(self, h)
                    self.h_align = obe.canvas.ConvertHAlign(h);
                end,
                horizontal = function(self, h)
                    self.h_align = obe.canvas.ConvertHAlign(h);
                end,
                v = function(self, v)
                    self.v_align = obe.canvas.ConvertVAlign(v);
                end,
                vertical = function(self, v)
                    self.v_align = obe.canvas.ConvertVAlign(v);
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
            self.text.color = obe.canvas.normalize_color(color);
            self:refresh();
        end,
        outline = function(self, outline)
            if type(outline) == "table" then
                if outline.color then
                    self.text.outline = obe.canvas.normalize_color(outline.color);
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
                self.h_align = obe.canvas.ConvertHAlign(al.h or al.horizontal);
            end
            if al.v or al.vertical then
                self.v_align = obe.canvas.ConvertVAlign(al.v or al.vertical);
            end
        end
    }
}

function obe.canvas.Canvas:GenerateId(id)
    if type(id) == "string" and self.internal:get(id) ~= nil then
        error("CanvasElement '" .. tostring(id) .. "' already exists !");
    end
    while id == nil or self.internal:get(id) ~= nil do
        id = obe.utils.string
                 .get_random_key(obe.utils.string.Alphabet .. obe.utils.string.Numbers, 12);
    end
    return id;
end

function obe.canvas.Canvas:Line(id)
    id = self:GenerateId(id);
    self.elements[id] = self:InstanciateMT("Line", self.internal:Line(id));
    -- print(inspect(self.elements[id]));
    return self.elements[id];
end

function obe.canvas.Canvas:Rectangle(id)
    id = self:GenerateId(id);
    self.elements[id] = self:InstanciateMT("Rectangle", self.internal:Rectangle(id));
    return self.elements[id];
end

function obe.canvas.Canvas:Text(id)
    id = self:GenerateId(id);
    self.elements[id] = self:InstanciateMT("Text", self.internal:Text(id));
    self.elements[id].font = "Data/Fonts/NotoSans.ttf";
    return self.elements[id];
end

function obe.canvas.Canvas:Circle(id)
    id = self:GenerateId(id);
    self.elements[id] = self:InstanciateMT("Circle", self.internal:Circle(id));
    return self.elements[id];
end

function obe.canvas.Canvas:Polygon(id)
    id = self:GenerateId(id);
    self.elements[id] = self:InstanciateMT("Polygon", self.internal:Polygon(id));
    return self.elements[id];
end

function obe.canvas.Canvas:Bezier(id)
    id = self:GenerateId(id);
    self.elements[id] = self:InstanciateMT("Bezier", self.internal:Bezier(id));
    return self.elements[id];
end

function obe.canvas.Canvas:Sprite(id)
    id = self:GenerateId(id);
    self.elements[id] = {ref = self.internal:Sprite(id)};
    return self.elements[id];
end

function obe.canvas.Canvas:render(target)
    if self.useCache then
        for id, element in pairs(self.elements) do
            obe.canvas.ApplyCache(element);
        end
    end
    self.internal:render(target);
end

function obe.canvas.Canvas:clear()
    self.elements = {};
    self.internal:clear();
end

function obe.canvas.Canvas:remove(element)
    self.elements[element] = nil;
    self.internal:remove(element);
end
