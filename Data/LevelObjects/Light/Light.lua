PowerSwitch = {};
ColorButton = {};

Import("Core.Light");
Import("Core.World");
Import("Core.Utils.Math");
Import("Core.Animation.Animator");

GetHook("World");

UseLocalTrigger("Init");

function Local.Init()
    switchKey = Require("switchKey");
    buttonKey = Require("buttonKey");
    UseCustomTrigger(switchKey, "Switch", "*", "PowerSwitch");
    UseCustomTrigger(buttonKey, "Button", "Click", "ColorButton");
    This:Animator():setKey("Off");
    state = false;
    light = Core.Light.PointLight.new("light", 1920, 1080, 400, 200, 20, 255, 255, 50, 255, false);
    light:setOffset(25, 25);
    light:hide();
    incLight = 0.0
    Hook.World:addLight(light);
end

function PowerSwitch.Off()
    state = false;
    light:hide();
    This:Animator():setKey("Off");
end

function PowerSwitch.On(param)
    print("RCV:",param.lolz);
    for k, v in pairs( param.lolz ) do
       print(k, v)
    end
    state = true;
    light:show();
    This:Animator():setKey("On");
end

function ColorButton.Click()
    local randR = Core.Utils.Math.randint(0, 255);
    local randG = Core.Utils.Math.randint(0, 255);
    local randB = Core.Utils.Math.randint(0, 255);
    light:setColor(randR, randG, randB, 255);
end