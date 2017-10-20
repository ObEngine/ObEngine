local Class = require("Lib/StdLib/Class");

obe.Canvas.Canvas = Class("Canvas", function(self, width, height)
    self.internal = obe.Canvas.InternalCanvas(width, height);
    self.elements = {};
end);

function obe.Canvas.Canvas.MakeMT(bases, attributes)
    local gbase = {};
    for _, base in pairs(bases) do 
        for accid, accessor in pairs(base.__accessors) do 
            gbase[accid] = accessor;
        end
    end
    return {
        __accessors = gbase,
        
    }
end

obe.Canvas.Canvas.LineMT = obe.Canvas.Canvas.MakeMT(
    {
        obe.Canvas.Canvas.CanvasElementMT,
        obe.Canvas.Canvas.ColorableMT
    },
    {
        x1 = function(self, x1) self.p1.x = x1; end,
        y1 = function(self, y1) self.p1.y = y1; end,
        x2 = function(self, x2) self.p2.x = x2; end,
        y2 = function(self, y2) self.p2.y = y2; end,
        unit = function(self, unit)
            self.p1.unit = unit;
            self.p2.unit = unit;
        end
    }
);

function obe.Canvas.Canvas:Line(id)
    self.elements[id] = { __ref = self.internal:Line(id); };
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