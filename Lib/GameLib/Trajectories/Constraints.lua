local Constraints = {};

function Constraints.StaticWhenColliding(self, callback)
    while This:Collider():doesPathCollide(allColliders, 0, 0, self.addX, self.addY, true) do
        if self.speed < 1 then
            self.speed = 0;
            self.static = true;
            callback();
            break;
        else
            self.speed = self.speed - 1;
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
    self:updatePosition();
    while This:Collider():doesPathCollide(allColliders, 0, 0, self.addX, self.addY, true) do
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