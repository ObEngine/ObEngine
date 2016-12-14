Import("Core.Animation");
Import("Core.Collision");
Import("Core.STD");
Import("Core.MathExp");
Import("Core.Particle");
Import("Core.Light");
Import("Core.GUI");
Import("Core.SFML");

GetHook("GUI");

Linear = require("Lib/GameLib/Trajectories/Linear");

This:useLocalTrigger("Init");
This:useLocalTrigger("Update");


function Local.Init(posX, posY)
    score1, score2 = 0, 0;
    This:Collider():setPosition(posX, posY);
    score1Lbl = Hook.GUI:createLabel("Score", "score1Lbl", 650, 35, "0", "arial.ttf", 48, Core.SFML.Color.new(255,255,255,255));
    score2Lbl = Hook.GUI:createLabel("Score", "score2Lbl", 1250, 35, "0", "arial.ttf", 48, Core.SFML.Color.new(255,255,255,255));
    trail = Core.Particle.MathParticle.new("bx", "by", "(sin@(t))^2 * 255", "(sin@(t+pi/2))^2 * 255", "(sin@(t+pi/4))^2 * 255", "255", "-1", 0.0001);
    trail:registerMathExp("trailLength", "500");
	trail:registerMathExp("trailAlpha", "1.007");
    trail:registerMathExp("size", "5");
    light = Core.Light.DynamicPointLight.new("ball", 1920, 1080, 0.003);
    light:setSizeExp("15 + abs@(sin@(3 * t) * 3 + 1)");
    light:setRExp("255");
    light:setBExp("255");
    light:setGExp("0");
    light:setAExp("255");
    light:setOffsetXExp("48");
    light:setOffsetYExp("48");
    BallTrajectory = Linear(3, 0, 270);
    This:Animator():setKey("Ball");
    BallTrajectory:bind(This, {0, 0});
    bounceSwitch = 0;
    World:addParticle(trail);
    World:addLight(light);
    This:setInitialised(true);
end

function Local.Update(P)
    -- Position
    BallTrajectory:updatePosition();
    local selfPoint = This:Collider():getMasterPointPosition();
    local bx, by = selfPoint:first(), selfPoint:second();

    -- Trail Update
    trail:setGlobalVar("bx", bx - 2);
    trail:setGlobalVar("by", by - 2);
    trail:update();

    -- Paddle Reaction
    if This:Collider():doesPathCollide(allColliders, 0, 0, BallTrajectory.addX, BallTrajectory.addY, true) then
        bounceSwitch = 0;
        local currentPaddle;
        local orientAngle;
        if bx < 960 then
            currentPaddle = World:getGameObject("leftPaddle");
            orientAngle = 90;
        else
            currentPaddle = World:getGameObject("rightPaddle");
            orientAngle = 270;
        end
        local currentPaddlePoint = currentPaddle:Collider():getMasterPointPosition();
        local px, py = currentPaddlePoint:first(), currentPaddlePoint:second();
        local adj, opo = math.abs(px - bx), math.abs(py - by);
        local orientTraj;
        if orientAngle == 90 then orientTraj = by < py and -1 or 1;
        else orientTraj = by < py and 1 or -1;
        end
        BallTrajectory:setAngle(math.deg(math.atan(opo / adj)) * orientTraj + orientAngle);
        BallTrajectory:setSpeed(BallTrajectory:getSpeed() + 1);
    end

    -- Trajectory
    BallTrajectory:setDeltaTime(P.dt);
    BallTrajectory:update();
    allColliders = World:getColliders();

    -- World Bounds
    if by <= 32 and (bounceSwitch == 0 or bounceSwitch == 2) then
        BallTrajectory:setAngle(180 - BallTrajectory:getAngle());
        bounceSwitch = 1;
    elseif by >= 1048 and (bounceSwitch == 0 or bounceSwitch == 1) then
        BallTrajectory:setAngle(180 - BallTrajectory:getAngle());
        bounceSwitch = 2;
    end

    -- Win / Loss
    if bx < 48 then
        score2 = score2 + 1;
        score2Lbl:setText(tostring(score2), Core.SFML.Color.new(255,255,255,255));
        This:Collider():setPositionFromMaster(960, 540);
        BallTrajectory:setSpeed(3);
    elseif bx > 1968 then
        score1 = score1 + 1;
        score1Lbl:setText(tostring(score1), Core.SFML.Color.new(255,255,255,255));
        This:Collider():setPositionFromMaster(960, 540);
        BallTrajectory:setSpeed(3);
    end
end