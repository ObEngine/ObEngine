local Class = require("Lib/StdLib/Class");

obe.Canvas.Canvas = Class("Canvas", function(self, width, height)
    self.internal = obe.Canvas.InternalCanvas(width, height);
    self.elements = {};
end);

function obe.Canvas.NormalizeColor(color, base)
    if type(color) == "table" then
        local ncolor = SFML.Color();
        base = base or { r = 0, g = 0, b = 0, a = 255 };
        ncolor.r = color.r or base.r;
        ncolor.g = color.g or base.g;
        ncolor.b = color.b or base.b;
        ncolor.a = color.a or base.a;
        return ncolor;
    elseif type(color) == "number" then
        local dalpha = self.shape:getFillColor().a;
        local ncolor = SFML.Color(color, color, color, dalpha);
    elseif type(color) == "string" then
        color = color:gsub("#","");
        if string.len(color) == 3 then
            return SFML.Color(tonumber("0x"..color:sub(1,1)) * 17, tonumber("0x"..color:sub(2,2)) * 17, tonumber("0x"..color:sub(3,3)) * 17);
        elseif string.len(color) == 6 then
            return SFML.Color(tonumber("0x"..color:sub(1,2)), tonumber("0x"..color:sub(3,4)), tonumber("0x"..color:sub(5,6)));
        end
    end
end

function obe.Canvas.ConvertHAlign(align)
    if type(align) == "string" then
        if align == "Left" then return obe.Canvas.Alignment.Horizontal.Left;
        elseif align == "Center" then return obe.Canvas.Alignment.Horizontal.Center;
        elseif align == "Right" then return obe.Canvas.Alignment.Horizontal.Right;
        end
    else
        if align == obe.Canvas.Alignment.Horizontal.Left then return "Left";
        elseif align == obe.Canvas.Alignment.Horizontal.Center then return "Center";
        elseif align == obe.Canvas.Alignment.Horizontal.Right then return "Right";
        end
    end
end

function obe.Canvas.ConvertVAlign(align)
    if type(align) == "string" then
        if align == "Top" then return obe.Canvas.Alignment.Vertical.Top;
        elseif align == "Center" then return obe.Canvas.Alignment.Vertical.Center;
        elseif align == "Bottom" then return obe.Canvas.Alignment.Vertical.Bottom;
        end
    else
        if align == obe.Canvas.Alignment.Vertical.Top then return "Top";
        elseif align == obe.Canvas.Alignment.Vertical.Center then return "Center";
        elseif align == obe.Canvas.Alignment.Vertical.Bottom then return "Bottom";
        end
    end
end

obe.Canvas.Bases = {};

function obe.Canvas.MakeMT(bases)
    local getters = {};
    local setters = {};
    local fAccess = function(a, b, c) 
        local k = getmetatable(a);
        if type(b) == "number" and not k.__setters[b] and k.__setters.__number then
            k.__setters.__number(k.__ref, c);
        else
            if k.__setters[b] then
                k.__setters[b](k.__ref, c);
            else
                error("Can't find obe.Canvas.Canvas attribute : " .. tostring(b));
            end
        end
    end
    local nAccess = function(a, b)
        local k = getmetatable(a);
        if type(k.__getters[b]) == "function" then
            return k.__getters[b](k.__ref);
        elseif type(b) == "number" and not k.__getters[b] and k.__getters.__number then
            return k.__getters.__number(k.__ref);
        elseif type(k.__getters[b]) == "table" then
            return k.__getters[b];
        end
    end
    local tAccess = function(a, b)
        b = b or {};
        for k, v in pairs(b) do
            a[k] = v;
        end
        return a;
    end
    for kb, base in pairs(bases) do
        for getterName, getterValue in pairs(base.getters) do
            getters[getterName] = getterValue;
        end
        for setterName, setterValue in pairs(base.setters) do
            setters[setterName] = setterValue;
        end
    end
    for key, getter in pairs(getters) do
        if type(getter) == "table" then
            getters[key] = obe.Canvas.MakeMT({getter});
        end
    end
    for key, setter in pairs(setters) do
        if type(setter) == "table" then
            setters[key] = obe.Canvas.MakeMT({setter});
        end
    end
    local mt = {
        __ref = nil,
        __getters = getters,
        __setters = setters,
        __index = nAccess,
        __newindex = fAccess,
        __call = tAccess
    };
    local tt = { __type = "CanvasMT" };
    setmetatable(tt, mt);
    return tt;
end

function obe.Canvas.InitializeMT(tbl, ref)
    if type(tbl) == "table" and rawget(tbl, "__type") == "CanvasMT" then
        local mt = getmetatable(tbl);
        mt.__ref = ref;
        for k, getter in pairs(mt.__getters) do
            obe.Canvas.InitializeMT(getter, ref);
        end
        for k, setter in pairs(mt.__setters) do
            obe.Canvas.InitializeMT(setter, ref);
        end
    end
end

obe.Canvas.Bases.Drawable = {
  getters = {
      layer = function(self) return self.layer; end,
      visible = function(self) return self.visible; end
  },
  setters = {
      layer = function(self, layer) self:setLayer(layer or 1); end,
      visible = function(self, visible) self.visible = visible; end
  }
}

obe.Canvas.Bases.Line = {
    getters = {
        x1 = function(self) return self.p1.x; end,
        y1 = function(self) return self.p1.y; end,
        x2 = function(self) return self.p2.x; end,
        y2 = function(self) return self.p2.y; end,
        unit = function(self) return self.p1.unit; end,
        thickness = function(self) return self.thickness; end,
        color = {
            getters = {
                r = function(self) return self.color.r; end,
                g = function(self) return self.color.g; end,
                b = function(self) return self.color.b; end,
                a = function(self) return self.color.a; end
            },
            setters = {
                r = function(self, r) self.color.r = r or 0 end,
                g = function(self, g) self.color.g = g or 0; end,
                b = function(self, b) self.color.b = b or 0; end,
                a = function(self, a) self.color.a = a or 255; end
            }
        }
    },
    setters = {
        x1 = function(self, x1) self.p1.x = x1 or 0; end,
        y1 = function(self, y1) self.p1.y = y1 or 0; end,
        x2 = function(self, x2) self.p2.x = x2 or 0; end,
        y2 = function(self, y2) self.p2.y = y2 or 0; end,
        unit = function(self, unit)
            self.p1.unit = unit or obe.Units.WorldPixels;
            self.p2.unit = unit or obe.Units.WorldPixels;
        end,
        p1Unit = function(self, unit)
            self.p1.unit = unit or obe.Units.WorldPixels;
        end,
        p2Unit = function(self, unit)
            self.p1.unit = unit or obe.Units.WorldPixels;
        end,
        thickness = function(self, thickness) self.thickness = thickness or 1; end,
        color = function(self, color)
            self.color = obe.Canvas.NormalizeColor(color, self.color);
        end
    }
};

obe.Canvas.Bases.Shape = {
    getters = {
        x = function(self) return self.shape:getPosition().x; end,
        y = function(self) return self.shape:getPosition().y; end,
        angle = function(self) return self.shape:getRotation(); end,
        scale = {
            getters = {
                x = function(self) return self.shape:getScale().x; end,
                y = function(self) return self.shape:getScale().y; end
            },
            setters = {
                x = function(self, x)
                    local y = self.shape:getScale().y;
                    self.shape:setScale(x, y);
                end,
                y = function(self, y)
                    local x = self.shape:getScale().x;
                    self.shape:setScale(x, y);
                end
            }
        },
        outline = {
            getters = {
                color = {
                    getters = {
                        r = function(self) return self.shape:getOutlineColor().r; end,
                        g = function(self) return self.shape:getOutlineColor().g; end,
                        b = function(self) return self.shape:getOutlineColor().b; end,
                        a = function(self) return self.shape:getOutlineColor().a; end
                    },
                    setters = {
                        r = function(self, r) 
                            local colorBuffer = self.shape:getOutlineColor();
                            colorBuffer.r = r or 0;
                            self.shape:setOutlineColor(colorBuffer);
                        end,
                        g = function(self, g) 
                            local colorBuffer = self.shape:getOutlineColor();
                            colorBuffer.g = g or 0;
                            self.shape:setOutlineColor(colorBuffer);
                        end,
                        b = function(self, b) 
                            local colorBuffer = self.shape:getOutlineColor();
                            colorBuffer.b = b or 0;
                            self.shape:setOutlineColor(colorBuffer);
                        end,
                        a = function(self, a) 
                            local colorBuffer = self.shape:getOutlineColor();
                            colorBuffer.a = a or 255;
                            self.shape:setOutlineColor(colorBuffer);
                        end
                    }
                },
                thickness = function(self) return self.shape:getOutlineThickness(); end
            },
            setters = {
                color = function(self, color)
                    self.shape:setOutlineColor(obe.Canvas.NormalizeColor(color, self.shape:getOutlineColor()));
                end,
                thickness = function(self, thickness) self.shape:setOutlineThickness(thickness or 1); end
            }
        },
        color = {
            getters = {
                r = function(self) return self.shape:getFillColor().r; end,
                g = function(self) return self.shape:getFillColor().g; end,
                b = function(self) return self.shape:getFillColor().b; end,
                a = function(self) return self.shape:getFillColor().a; end
            },
            setters = {
                r = function(self, r) 
                    local colorBuffer = self.shape:getFillColor();
                    colorBuffer.r = r or 0;
                    self.shape:setFillColor(colorBuffer);
                end,
                g = function(self, g) 
                    local colorBuffer = self.shape:getFillColor();
                    colorBuffer.g = g or 0;
                    self.shape:setFillColor(colorBuffer);
                end,
                b = function(self, b) 
                    local colorBuffer = self.shape:getFillColor();
                    colorBuffer.b = b or 0;
                    self.shape:setFillColor(colorBuffer);
                end,
                a = function(self, a) 
                    local colorBuffer = self.shape:getFillColor();
                    colorBuffer.a = a or 255;
                    self.shape:setFillColor(colorBuffer);
                end
            }
        }
    },
    setters = {
        outline = function(self, outline)
            if type(outline) == "table" then
                if outline.color then
                    self.shape:setOutlineColor(obe.Canvas.NormalizeColor(outline.color, self.shape:getOutlineColor()));
                end
                if type(outline.thickness) == "number" then
                    self.shape:setOutlineThickness(outline.thickness);
                end
            end
        end,
        color = function(self, color)
            self.shape:setFillColor(obe.Canvas.NormalizeColor(color, self.shape:getFillColor()));
        end,
        x = function(self, x)
            local y = self.shape:getPosition().y;
            self.shape:setPosition(SFML.Vector2f(x, y));
        end,
        y = function(self, y)
            local x = self.shape:getPosition().x;
            self.shape:setPosition(SFML.Vector2f(x, y));
        end,
        angle = function(self, angle)
            self.shape:setRotation(angle or 0);
        end,
        scale = function(self, scale)
            if type(scale) == "number" then
                self.shape:setScale(scale, scale);
            elseif type(scale) == "table" then
                self.shape:setScale(scale.x or 1, scale.y or 1);
            end
        end
    }
}

obe.Canvas.Bases.Rectangle = {
    getters = {
        width = function(self) return self.shape:getSize().x; end,
        height = function(self) return self.shape:getSize().y; end
    },
    setters = {
        width = function(self, width)
            local height = self.shape:getSize().y;
            self.shape:setSize(SFML.Vector2f(width, height));
        end,
        height = function(self, height)
            local width = self.shape:getSize().x;
            self.shape:setSize(SFML.Vector2f(width, height));
        end,
    }
}

obe.Canvas.Bases.Circle = {
    getters = {
        radius = function(self) return self.shape:getRadius(); end,
        width = function(self) return self.shape:getGlobalBounds().width; end,
        height = function(self) return self.shape:getGlobalBounds().height; end
    },
    setters = {
        radius = function(self, radius) return self.shape:setRadius(radius); end
    }
}

function GetRichTextString(shape)
    local fullText = "";
    for _, line in pairs(shape:getLines()) do
        for _, text in pairs(line:getTexts()) do
            fullText = fullText .. text:getString():toAnsiString();
        end
        fullText = fullText .. "\n";
    end
    if fullText and fullText ~= "" then
        fullText = string.sub(fullText, 1, -2);
    end
    return fullText;
end

obe.Canvas.Bases.Text = {
    getters = {
        text = function(self)
            local fulltext = "";
            for _, line in pairs(self.shape:getLines()) do
                for _, text in pairs(line:getTexts()) do
                    fullText = fulltext .. text:getString():toAnsiString();
                end
                fullText = fullText .. "\n";
            end
            if fullText ~= "" then
                fullText = fullText:sub(1, -2);
            end
            return fulltext;
        end,
        size = function(self)
            return self.shape:getCharacterSize();
        end,
        font = function(self)
            return self.fontPath;
        end,
        width = function(self)
            return self.shape:getGlobalBounds().width;
        end,
        height = function(self)
            return self.shape:getGlobalBounds().height;
        end,
        align = {
            getters = {
                h = function(self) return obe.Canvas.ConvertHAlign(self.h_align); end,
                horizontal = function(self) return obe.Canvas.ConvertHAlign(self.h_align); end,
                v = function(self) return obe.Canvas.ConvertVAlign(self.v_align); end,
                vertical = function(self) return obe.Canvas.ConvertVAlign(self.v_align); end
            },
            setters = {
                h = function(self, h) self.h_align = obe.Canvas.ConvertHAlign(h); end,
                horizontal = function(self, h) self.h_align = obe.Canvas.ConvertHAlign(h); end,
                v = function(self, v) self.v_align = obe.Canvas.ConvertVAlign(v); end,
                vertical = function(self, v) self.v_align = obe.Canvas.ConvertVAlign(v); end
            }
        }
    },
    setters = {
        text = function(self, text)
            self.shape:clear();
            -- Apply style
            if self.fontPath == "" then
                error("@Canvas.Text.setters.text : Need to set @font before @text");
            end
            self.shape:pushString(SFML.WString(text));
        end,
        size = function(self, size)
            self.shape:setCharacterSize(size);
        end,
        font = function(self, font)
            self.fontPath = font;
            self.shape:setFont(obe.ResourceManager.GetFont(font));
        end,
        color = function(self, color)
            self.shape:clear();
            self.shape:pushFillColor(obe.Canvas.NormalizeColor(color));
            self.shape:pushString(SFML.String(GetRichTextString(self.shape)));
        end,
        outline = function(self, outline)
            if type(outline) == "table" then
                if outline.color then
                    self.shape:clear();
                    self.shape:pushOutlineColor(obe.Canvas.NormalizeColor(outline.color));
                    self.shape:pushString(SFML.String(GetRichTextString(self.shape)));
                end
                if type(outline.thickness) == "number" then
                    self.shape:clear();
                    self.shape:pushOutlineThickness(outline.thickness);
                    self.shape:pushString(SFML.String(GetRichTextString(self.shape)));
                end
            end
        end,
        __number = function(self, part)
            self.shape:pushOutlineThickness(0);
            self.shape:pushOutlineColor(SFML.Color(255, 255, 255));
            self.shape:pushFillColor(SFML.Color(255, 255, 255));
            self.shape:pushStyle(SFML.Style.Regular);
            if part.color then
                self.shape:pushFillColor(obe.Canvas.NormalizeColor(part.color));
            end
            if part.style then
                self.shape:pushStyle(part.style);
            end
            if part.outline then
                if part.outline.thickness then
                    self.shape:pushOutlineThickness(part.outline.thickness);
                end
                if part.outline.color then
                    self.shape:pushOutlineColor(obe.Canvas.NormalizeColor(part.outline.color));
                end
            end
            if part.text then
                self.shape:pushString(SFML.String(part.text));
            end
        end,
        align = function(self, al)
            if al.h or al.horizontal then
                self.h_align = obe.Canvas.ConvertHAlign(al.h or al.horizontal);
            end
            if al.v or al.vertical then
                self.v_align = obe.Canvas.ConvertVAlign(al.v or al.vertical);
            end
        end
    }
}

function obe.Canvas.Canvas:GenerateId(id)
    while id == nil or self.internal:get(id) ~= nil do
        id = obe.String.getRandomKey(obe.String.Alphabet .. obe.String.Numbers, 12);
    end
    return id;
end

function obe.Canvas.Canvas:Line(id)
    id = self:GenerateId(id);
    self.elements[id] = obe.Canvas.MakeMT({ 
        obe.Canvas.Bases.Drawable, 
        obe.Canvas.Bases.Line});
    obe.Canvas.InitializeMT(self.elements[id], self.internal:Line(id));
    return self.elements[id];
end

function obe.Canvas.Canvas:Rectangle(id)
    id = self:GenerateId(id);
    self.elements[id] = obe.Canvas.MakeMT({
        obe.Canvas.Bases.Drawable,
        obe.Canvas.Bases.Shape,
        obe.Canvas.Bases.Rectangle});
    obe.Canvas.InitializeMT(self.elements[id], self.internal:Rectangle(id));
    return self.elements[id];
end

function obe.Canvas.Canvas:Text(id)
    id = self:GenerateId(id);
    self.elements[id] = obe.Canvas.MakeMT({
        obe.Canvas.Bases.Drawable,
        obe.Canvas.Bases.Shape,
        obe.Canvas.Bases.Text});
    obe.Canvas.InitializeMT(self.elements[id], self.internal:Text(id));
    self.elements[id].font = "Data/Fonts/arial.ttf";
    return self.elements[id];
end

function obe.Canvas.Canvas:Circle(id)
    id = self:GenerateId(id);
    self.elements[id] = obe.Canvas.MakeMT({
        obe.Canvas.Bases.Drawable,
        obe.Canvas.Bases.Shape,
        obe.Canvas.Bases.Circle});
    obe.Canvas.InitializeMT(self.elements[id], self.internal:Circle(id));
    return self.elements[id];
end

function obe.Canvas.Canvas:Sprite(id)
    id = self:GenerateId(id);
    self.elements[id] = { __ref = self.internal:Sprite(id); };
    return self.elements[id];
end

function obe.Canvas.Canvas:render()
    self.internal:render();
end

function obe.Canvas.Canvas:setTarget(target)
    self.internal:setTarget(target);
end

function obe.Canvas.Canvas:clear()
    self.internal:clear();
end

function obe.Canvas.Canvas:remove(element)
    self.internal:remove(element);
end