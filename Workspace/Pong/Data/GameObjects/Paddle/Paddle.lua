Keys = {};

Import("Core.Animation");
Import("Core.Collision");

inspect = require("Lib/StdLib/Inspect");
contains = require("Lib/StdLib/Contains");
Linear = require("Lib/GameLib/Trajectories/Linear");

This:useLocalTrigger("Init");
This:useLocalTrigger("Update");
This:useExternalTrigger("Global", "Keys", "*");

function Local.Init(upAction, downAction, posX, posY)
    Keys.upAction = upAction;
    Keys.downAction = downAction;
    This:Collider():setPosition(posX, posY);
    print("PaddleInitialised");
    This:Animator():setKey("Paddle");
    PaddleTrajectory = Linear(0, 0, 180);
    PaddleTrajectory:bind(This, {0, 0});
    speed = 5;
    This:setInitialised(true);
end

function Local.Update(P)
    PaddleTrajectory:setDeltaTime(P.dt);
    PaddleTrajectory:update(); 
    if This:Collider():getPointPosition(0):second() < 1 then
        PaddleTrajectory:setSpeed(0);
    elseif This:Collider():getPointPosition(2):second() > 1079 then
        PaddleTrajectory:setSpeed(0);
    end
end

function Keys.ActionToggled(P)
    if contains(P.ToggledActions, Keys.upAction) then
        PaddleTrajectory:setSpeed(-speed);
    elseif contains(P.ToggledActions, Keys.downAction) then
        PaddleTrajectory:setSpeed(speed);
    end
end

function Keys.ActionReleased(P)
    if contains(P.ReleasedActions, Keys.upAction) then
        PaddleTrajectory:setSpeed(0);
    elseif contains(P.ReleasedActions, Keys.downAction) then
        PaddleTrajectory:setSpeed(0);
    end
end