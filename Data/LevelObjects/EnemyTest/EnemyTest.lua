Enemy = {}

Import("Core.Animation.Animator");
Import("Core.Collision");
Import("Core.MathExp");
Import("Core.LevelSprite");

This:useLocalTrigger("Init");
This:useLocalTrigger("Update");

function Local.Init()
    This:Animator():setKey("Left");
    local basePosX = This:LevelSprite():getX();
    local basePosY = This:LevelSprite():getY();
    xMovement = Core.MathExp.MathExp.new("cos@(t/10) * 250 + bx");
    xMovement:buildMathExp();
    xMovement:setVar("bx", basePosX);
    yMovement = Core.MathExp.MathExp.new("cos@(t) * 30 + by");
    yMovement:buildMathExp();
    yMovement:setVar("by", basePosY);
    dMovement = Core.MathExp.MathExp.new("cos@(t/10)");
    dMovement:buildMathExp();
    t = 0;
end

function Local.Update(param)
    local x = xMovement:getResult();
    local y = yMovement:getResult();
    This:LevelSprite():setPosition(x, y);
    This:Collider():setPosition(math.floor(x), math.floor(y));
    t = t + (param.dt / 10);
    xMovement:setVar("t", t);
    yMovement:setVar("t", t);
    dMovement:setVar("t", t);
    if dMovement:getResult() < -0.99 then
        This:Animator():setKey("Right");
    elseif dMovement:getResult() > 0.99 then
        This:Animator():setKey("Left");
    end
end