Keys = {};

Import("Core.Animation");

inspect = require("Lib/StdLib/Inspect");
contains = require("Lib/StdLib/Contains");
Linear = require("Lib/GameLib/Trajectories/Linear");

This:useLocalTrigger("Init");
This:useLocalTrigger("Update");
This:useExternalTrigger("Global", "Keys", "*");

function Local.Init()
    upAction = Require("UpAction");
    downAction = Require("DownAction");
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
    if This:Collider():getPointCoordinates(0):second() < 1 then
        PaddleTrajectory:setSpeed(0);
    elseif This:Collider():getPointCoordinates(2):second() > 1079 then
        PaddleTrajectory:setSpeed(0);
    end
end

function Keys.ActionToggled(P)
    if contains(P.ToggledActions, upAction) then
        PaddleTrajectory:setSpeed(-speed);
    elseif contains(P.ToggledActions, downAction) then
        PaddleTrajectory:setSpeed(speed);
    end
end

function Keys.ActionReleased(P)
    if contains(P.ReleasedActions, upAction) then
        PaddleTrajectory:setSpeed(0);
    elseif contains(P.ReleasedActions, downAction) then
        PaddleTrajectory:setSpeed(0);
    end
end