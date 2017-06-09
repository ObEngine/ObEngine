local Constraints = {};

function Constraints.StaticWhenColliding(self, callback)
    print("Current speed :", self.speed);
    while This:Collider():testAllColliders(allColliders, math.ceil(self.addX), math.ceil(self.addY), true) do
        if self.speed < 1 then
            self.speed = 0;
            self.static = true;
            callback();
            break;
        else
            self.speed = self.speed - 1;
            print("DECREASE", self.addX, self.addY);
        end
        self:updatePosition();
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
    while This:Collider():testAllColliders(allColliders, self.addX, self.addY, true) do
        if self.speed < 1 then
            self.speed = 0;
            callback();
            break;
        else
            self.speed = self.speed - 1;
        end
        self:updatePosition();
    end
end

return Constraints;