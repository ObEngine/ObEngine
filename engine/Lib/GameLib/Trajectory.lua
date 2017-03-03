local Class = require("Lib/StdLib/Class");
local Overload = require("Lib/StdLib/Overload");
local inspect = require("Lib/StdLib/Inspect");

Import("Core.Collision");
Import("Core.LevelSprite");
Import("Core.STD.Pair");

local Trajectory = Class("Trajectory", function(self)
    self.trajName = "Trajectory";
    self.bindingList = {};
    self.constraintList = {};
    self.enabled = true;
    self.static = false;
end);

Trajectory.bind = Overload();
-- Overloads
function Trajectory.bind.Trajectory.obe__Collision__PolygonalCollider(self, col, offset)
    offset = offset == nil and offset or {0, 0};
    table.insert(self.bindingList, {col, offset
    , function(item) return {x = item:getPointPosition(0):first(), y = item:getPointPosition(0):second()}; end
    , function(item, x, y) item:setPosition(x, y, 0); end});
end
function Trajectory.bind.Trajectory.obe__Graphics__LevelSprite(self, spr, offset)
    offset = offset == nil and offset or {0, 0};
    table.insert(self.bindingList, {spr, offset
    , function(item) return {x = item:getX(), y = item:getY()}; end
    , function(item, x, y) item:setPosition(x, y); end});
end
function Trajectory.bind.Trajectory.obe__Script__GameObject(self, obj, offset)
    offset = offset == nil and offset or {0, 0};
    table.insert(self.bindingList, {obj, offset
    , function(item) return {x = item:Collider():getPointPosition(0):first(), y = item:Collider():getPointPosition(0):second()}; end
    , function(item, x, y) item:LevelSprite():setPosition(x, y); item:Collider():setPosition(x, y, 0); end});
end

function Trajectory:setPosition(x, y)
    for k,v in pairs(self.bindingList) do
        local offx, offy = v[2][1], v[2][2];
        v[4](v[1], x + offx, y + offy);
    end
end

function Trajectory:getBindingPosition(index)
    return self.bindingList[index][3](self.bindingList[index][1]);
end

function Trajectory:move(x, y)
    for k,v in pairs(self.bindingList) do
        local bx, by = v[3](v[1]).x, v[3](v[1]).y;
        local offx, offy = v[2][1], v[2][2];
        v[4](v[1], bx + x + offx, by + y + offy);
    end
end

function Trajectory:getTrajectoryName()
    return self.trajName;
end

function Trajectory:update()
    self:updateConstraints();
end

function Trajectory:enable()
    self.enabled = true;
end

function Trajectory:disable()
    self.enabled = false;
end

function Trajectory:isEnabled()
    return self.enabled;
end

function Trajectory:updateConstraints()
    for k,v in pairs(self.constraintList) do
        v(self);
    end
end

function Trajectory:setConstraint(id, constraint)
    self.constraintList[id] = constraint;
end

function Trajectory:removeConstraint(id)
    self.constraintList[id] = nil;
end

return Trajectory;
