local Class = require("Lib/StdLib/Class");

obe.Canvas.Canvas = Class("Canvas", function(self, width, height)
    self.internal = obe.Canvas.InternalCanvas(width, height);
    self.elements = {};
end);

obe.Canvas.Bases = {};

function obe.Canvas.MakeMT(bases)
    print("MAKE MT CALLED");
    local getters = {};
    local setters = {};
    local fAccess = function(a, b, c) 
        print("SETTER MT", a, b, c); 
        k = getmetatable(a);
        k.__setters[b](k.__ref, c);
    end
    local nAccess = function(a, b)
        print("GETTER MT", a, b);
        k = getmetatable(a);
        print(k.__getters[b]);
        if type(k.__getters[b]) == "function" then
            return k.__getters[b](k.__ref);
        else
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
      layer = function(self) return self.layer; end
  },
  setters = {
      layer = function(self, layer) self.layer = layer or self.layer or 0; end
  }
}

obe.Canvas.Bases.Colorable = {
    getters = {
        color = {
            getters = {
                r = function(self) print("r getter"); return self.color.r; end,
                g = function(self) print("g getter"); return self.color.g; end,
                b = function(self) print("b getter"); return self.color.b; end,
                a = function(self) print("a getter"); return self.color.a; end
            },
            setters = {
                r = function(self, r) self.color.r = r or self.color.r or 0; end,
                g = function(self, g) self.color.g = g or self.color.g or 0; end,
                b = function(self, b) self.color.b = b or self.color.b or 0; end,
                a = function(self, a) self.color.a = a or self.color.a or 255; end
            }
        }
    },
    setters = {
        color = function(self, color)
            print("tbl setter");
            if type(color) == "number" then
                self.color.r = color;
                self.color.g = color;
                self.color.b = color;
                self.color.a = self.color.a or 255;
            elseif type(color) == "table" then
                self.color.r = color.r or self.color.r or 0;
                self.color.g = color.g or self.color.g or 0;
                self.color.b = color.b or self.color.b or 0;
                self.color.a = color.a or self.color.a or 255;
            end
        end
    }
}

obe.Canvas.Bases.Transformable = {
    getters = {

    },
    setters = {

    }
}

obe.Canvas.Bases.Line = {
    getters = {
        x1 = function(self) return self.p1.x; end,
        y1 = function(self) return self.p1.y; end,
        x2 = function(self) return self.p2.x; end,
        y2 = function(self) return self.p2.y; end,
        unit = function(self) return self.p1.unit; end,
        thickness = function(self) return self.thickness; end
    },
    setters = {
        x1 = function(self, x1) self.p1.x = x1; end,
        y1 = function(self, y1) self.p1.y = y1; end,
        x2 = function(self, x2) self.p2.x = x2; end,
        y2 = function(self, y2) self.p2.y = y2; end,
        unit = function(self, unit)
            self.p1.unit = unit;
            self.p2.unit = unit;
        end,
        thickness = function(self, thickness) self.thickness = thickness; end
    }
};

--[[obe.Canvas.Canvas.RectangleMT = obe.Canvas.Canvas.MakeMT(
    {
        obe.Canvas.Canvas.ColorableMT,
        obe.Canvas.Canvas.TransformableMT
    },
    {
    },
    {
        color = function(self)
            self.shape:setColor(self.color.r, self.color.g, self.color.b, self.color.a);
        end,
        width = function(self)
            self.shape:setSize(self.psize.x, self.psize.y);
        end,
        height = function(self)
            self.shape:setSize(self.psize.x, self.psize.y);
        end,
        x = function(self)
            self.shape:setPosition(self.pposition.x, self.pposition.y);
        end,
        y = function(self)
            self.shape:setPosition(self.pposition.x, self.pposition.y);
        end,
        angle = function(self)
            self.shape:setRotation(self.angle);
        end,

    }
)]]--

function obe.Canvas.Canvas:Line(id)
    self.elements[id] = obe.Canvas.MakeMT({ 
        d = obe.Canvas.Bases.Drawable, 
        c = obe.Canvas.Bases.Colorable,
        l = obe.Canvas.Bases.Line});
    obe.Canvas.InitializeMT(self.elements[id], self.internal:Line(id));
    return self.elements[id];
end

function obe.Canvas.Canvas:Rectangle(id)
    self.elements[id] = { __ref = self.internal:Rectangle(id); };
    return self.elements[id];
end

function obe.Canvas.Canvas:Text(id)
    self.elements[id] = { __ref = self.internal:Text(id); };
    return self.elements[id];
end

function obe.Canvas.Canvas:Circle(id)
    self.elements[id] = { __ref = self.internal:Circle(id); };
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