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

obe.Canvas.Bases = {};

function obe.Canvas.MakeMT(bases)
    print("MAKE MT CALLED");
    local getters = {};
    local setters = {};
    local fAccess = function(a, b, c) 
        print("SETTER MTo", a, b, c); 
        k = getmetatable(a);
        if type(b) == "number" and not k.__setters[b] and k.__setters.__number then
            k.__setters.__number(k.__ref, c);
        else
            k.__setters[b](k.__ref, c);
        end
    end
    local nAccess = function(a, b)
        print("GETTER MT", a, b);
        k = getmetatable(a);
        print(k.__getters[b]);
        if type(k.__getters[b]) == "function" then
            return k.__getters[b](k.__ref);
        elseif type(b) == "number" and not k.__getters[b] and k.__getters.__number then
            return k.__getters.__number(k.__ref);
        elseif type(k.__getters[b]) == "table" then
            return k.__getters[b];
        end
    end
    local tAccess = function(a, b)
        for k, v in pairs(b) do
            a[k] = v;
        end
        return a;
    end
    for kb, base in pairs(bases) do
        print(kb, base, inspect(base));
        for getterName, getterValue in pairs(base.getters) do
            getters[getterName] = getterValue;
        end
        for setterName, setterValue in pairs(base.setters) do
            setters[setterName] = setterValue;
        end
    end
    for key, getter in pairs(getters) do
        if type(getter) == "table" then
            print("Call MAKEMT on gt subtable", key);
            getters[key] = obe.Canvas.MakeMT({getter});
        end
    end
    for key, setter in pairs(setters) do
        if type(setter) == "table" then
            print("Call MAKEMT on st subtable", key);
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
        print("On ", rawget(tbl, "__id"));
        print("INITIALIZING MT");
        local mt = getmetatable(tbl);
        mt.__ref = ref;
        for k, getter in pairs(mt.__getters) do
            print("Subinitialize Getter : ", k)
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
      layer = function(self, layer) self.layer = layer or 1; end,
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
            if type(color) == "number" then
                self.color.r = color;
                self.color.g = color;
                self.color.b = color;
                self.color.a = self.color.a or 255;
            elseif type(color) == "table" then
                self.color.r = color.r or self.color.r;
                self.color.g = color.g or self.color.g;
                self.color.b = color.b or self.color.b;
                self.color.a = color.a or self.color.a;
            end
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
                    if type(color) == "number" then
                        local dalpha = self.shape:getOutlineColor().a;
                        local ncolor = SFML.Color(color, color, color, dalpha);
                        self.shape:setOutlineColor(ncolor);
                    elseif type(color) == "table" then
                        local dcolor = self.shape:getOutlineColor();
                        local ncolor = SFML.Color();
                        ncolor.r = color.r or dcolor.r;
                        ncolor.g = color.g or dcolor.g;
                        ncolor.b = color.b or dcolor.b;
                        ncolor.a = color.a or dcolor.a;
                        self.shape:setOutlineColor(ncolor);
                    end
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
                if type(outline.color) == "table" then
                    local dcolor = self.shape:getOutlineColor();
                    local ncolor = SFML.Color();
                    ncolor.r = outline.color.r or dcolor.r;
                    ncolor.g = outline.color.g or dcolor.g;
                    ncolor.b = outline.color.b or dcolor.b;
                    ncolor.a = outline.color.a or dcolor.a;
                    self.shape:setOutlineColor(ncolor);
                elseif (outline.color) == "number" then
                    local dalpha = self.shape:getOutlineColor().a;
                    local ncolor = SFML.Color(outline.color, outline.color, outline.color, dalpha);
                    self.shape:setOutlineColor(ncolor);
                end
                if type(outline.thickness) == "number" then
                    self.shape:setOutlineThickness(outline.thickness);
                end
            end
        end,
        color = function(self, color)
            if type(color) == "table" then
                local dcolor = self.shape:getFillColor();
                local ncolor = SFML.Color();
                ncolor.r = color.r or dcolor.r;
                ncolor.g = color.g or dcolor.g;
                ncolor.b = color.b or dcolor.b;
                ncolor.a = color.a or dcolor.a;
                self.shape:setFillColor(ncolor);
            elseif type(color) == "number" then
                local dalpha = self.shape:getFillColor().a;
                local ncolor = SFML.Color(color, color, color, dalpha);
                self.shape:setFillColor(ncolor);
            elseif type(color) == "string" then
                local dalpha = self.shape:getFillColor().a;
                
            end
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
        end
    },
    setters = {
        text = function(self, text)
            self.shape:clear();
            -- Apply style
            if self.fontPath == "" then
                error("@Canvas.Text.setters.text : Need to set @font before @text");
            end
            self.shape:pushString(SFML.String(text));
        end,
        size = function(self, size)
            self.shape:setCharacterSize(size);
        end,
        font = function(self, font)
            print("MMMMMMMMMMMMDDDDDDDDDDDRRRRRRRRRR");
            self.fontPath = font;
            self.shape:setFont(obe.ResourceManager.GetFont(font));
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
        end
    }
}

function obe.Canvas.Canvas:Line(id)
    self.elements[id] = obe.Canvas.MakeMT({ 
        obe.Canvas.Bases.Drawable, 
        obe.Canvas.Bases.Line});
    obe.Canvas.InitializeMT(self.elements[id], self.internal:Line(id));
    return self.elements[id];
end

function obe.Canvas.Canvas:Rectangle(id)
    self.elements[id] = obe.Canvas.MakeMT({
        obe.Canvas.Bases.Drawable,
        obe.Canvas.Bases.Shape,
        obe.Canvas.Bases.Rectangle});
    obe.Canvas.InitializeMT(self.elements[id], self.internal:Rectangle(id));
    return self.elements[id];
end

function obe.Canvas.Canvas:Text(id)
    self.elements[id] = obe.Canvas.MakeMT({
        obe.Canvas.Bases.Drawable,
        obe.Canvas.Bases.Shape,
        obe.Canvas.Bases.Text});
    obe.Canvas.InitializeMT(self.elements[id], self.internal:Text(id));
    self.elements[id].font = "Data/Fonts/arial.ttf";
    return self.elements[id];
end

function obe.Canvas.Canvas:Circle(id)
    self.elements[id] = obe.Canvas.MakeMT({
        obe.Canvas.Bases.Drawable,
        obe.Canvas.Bases.Shape,
        obe.Canvas.Bases.Circle});
    obe.Canvas.InitializeMT(self.elements[id], self.internal:Circle(id));
    return self.elements[id];
end

function obe.Canvas.Canvas:Sprite(id)
    self.elements[id] = { __ref = self.internal:Sprite(id); };
    return self.elements[id];
end

function obe.Canvas.Canvas:render()
    self.internal:render();
end

function obe.Canvas.Canvas:setTarget(target)
    self.internal:setTarget(target);
end