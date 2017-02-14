local Color = {};

function Color.print(tables, indent)
    if indent ~= nil then
        for i = 0, indent - 1 do
            io.write("    ");
        end
    end
    for k, v in pairs(tables) do
        if type(v) == "string" then
            io.write(v); io.flush();
        elseif type(v) == "table" then
            io.write(color(v.color) .. v.text); io.flush();
        end
    end
    color("white");
end

return Color;