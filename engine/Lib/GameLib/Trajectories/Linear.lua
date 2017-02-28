local Class = require("Lib/StdLib/Class");
local Trajectory = require("Lib/GameLib/Trajectory");

local Linear = Class("Linear", Trajectory, function(self, speed, acceleration, angle)
    self:super();
    self.trajName = "Linear";
    self.speed = speed;
    self.acceleration = acceleration;
    self.angle = angle;
    self.dt = 0;
    self.addX = 0;
    self.addY = 0;
end);

function Linear:setAngle(angle)
    self.angle = angle;
end

function Linear:getAngle()
    return self.angle;
end

function Linear:setSpeed(speed)
    self.speed = speed;
end

function Linear:getSpeed()
    return self.speed;
end

function Linear:setAcceleration(acceleration)
    self.acceleration = acceleration;
end

function Linear:getAcceleration()
    return self.acceleration;
end

function Linear:updatePosition()
    local radAngle = (math.pi / 180.0) * ((90 - self.angle) * -1);
    self.addX = math.cos(radAngle) * (self.speed * self.dt);
    self.addY = math.sin(radAngle) * (self.speed * self.dt);
end

function Linear:update(dt)
    self.dt = dt;
    if self.enabled then
        self:updatePosition();
        self:updateConstraints();
        if not self.static then
            self:move(self.addX, self.addY);
            self.speed = self.speed + (self.acceleration * self.dt);
        end
    end
end

return Linear;