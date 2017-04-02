if Core == nil then
    Core = {};
    Core.Canvas = {};
elseif Core.Canvas == nil then
    Core.Canvas = {};
end

function Core.Canvas.DefaultValues(self, requires)
    for k, v in pairs(requires) do
        if self[v:first()] == nil then
            self[v:first()] = load("return " .. v:second())();
        end
    end
end
