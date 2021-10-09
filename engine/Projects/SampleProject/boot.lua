function Game.Start()
    assert(io.open("root://boot.lua"), "can't find boot.lua");
    Engine.Scene:loadFromFile("scenes://sample.map.vili");
end