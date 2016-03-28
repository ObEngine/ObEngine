Character = {}

Import("Core.Trajectory");
Import("Core.Utils.Math");

UseLocalTrigger("Init");
UseLocalTrigger("Update");
UseLocalTrigger("Collide");

UseGlobalTrigger("KeyBind", "*");

function Local.Init()
    jumpPower = 30;
    This.Collider:AddTrajectory(Core.Trajectory.new("Gravity", 180, 0, 1));
    This.Collider:AddTrajectory(Core.Trajectory.new("Move", 90, 0, -0.5));
end

function Local.Update()
end

function Local.Collide(Parameters)
    if Parameters.side == 0 then
        This.Collider:RemoveTrajectory("Jump");
    elseif Parameters.side == 2 then
        This.Collider:RemoveTrajectory("Gravity");
    end
end

function Character.SetDirectionAnimation(wanim)
    This.Animation:setKey(wanim + (direction == "Left" and "_LEFT" or "_RIGHT"));
end

function Character.Move(direction)
    local speedDirection = direction == "Left" and -1 or 1;
    local totalSpeed = (Core.Utils.Math.isSameSign(speedDirection, This:Collider:GetTrajectory("Move"):GetSpeed()) * This:Collider:GetTrajectory("Move"):GetSpeed()) + speedDirection;
    This.Collider:GetTrajectory("Move"):SetSpeed(totalSpeed);
end

function Character.Jump()
    if not This:Collider:HasTrajectory("Jump") then
        This.Collider:RemoveTrajectory("Gravity");
        local jumpMove = Core.Trajectory.new("Jump", 0, jumpPower, -1);
        jumpMove:onRemove(Core.Trajectory.new("Gravity", 180, 0, 1));
        This.Collider:AddTrajectory(jumpMove);
    end
end

function KeyBind.onActionEnabled(Parameters)
    if Parameters.action == "Move" then
        Character.Move(Parameters.direction);
    end
end

function KeyBind.onActionToggle(Parameters)
    if Parameters.action == "Jump" then
        Character.Jump();
    end
end