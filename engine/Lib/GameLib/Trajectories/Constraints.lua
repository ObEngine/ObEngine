local Constraints = {};

function Constraints.StaticWhenColliding(self, callback)
    print("Current speed :", self.speed);
    local offset = obe.Vec2(self.addX, self.addY);
    local maxDist = self.collider:getMaximumDistanceBeforeCollision(self.allColliders, offset);
    if maxDist:different(offset) then
        self.speed = 0;
        self.static = true;
        callback();
    end
end

function Constraints.StaticWhenSpeedIsNull(self, callback)
    if self.speed <= 0 then
        self.speed = 0;
        self.static = true;
        callback();
    end
end

function Constraints.StopWhenColliding(self, callback)
    --[[while This:Collider():testAllColliders(allColliders, self.addX, self.addY, true) do
        if self.speed < 1 then
            self.speed = 0;
            callback();
            break;
        else
            self.speed = self.speed - 1;
        end
        self:updatePosition();
    end]]--
end

return Constraints;