---@class SampleObject : GameObjectCls
local SampleObject = GameObject();

local _canvas;

function SampleObject:init()
    local screen_size = Engine.Window:get_size();
    _canvas = obe.Canvas.Canvas(screen_size.x, screen_size.y);

    _canvas:Text "hello" {
        text = "Hello, world!",
        size = 128,
        color = obe.Graphics.Color.White,
        x = 0.5,
        y = 0.5,
        unit = obe.Transform.Units.ViewPercentage,
        align = {
            horizontal = "Center",
            vertical = "Center"
        }
    };
end

function Event.Game.Render()
    _canvas:render(SampleObject.components.Sprite);
end