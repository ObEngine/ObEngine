local Color = {};

function Color.print(tables, indent)
    if indent ~= nil then
        for i = 0, indent - 1 do
            io.write("    ");
        end
    end
    for k, v in pairs(tables) do
        if type(v) == "string" then
            _term_display(v);
        elseif type(v) == "table" then
            if v.dark == nil then
                _term_setcolor(v.color, false);
            else 
                _term_setcolor(v.color, v.dark);
            end
            _term_display(v.text);
        end
    end
    _term_setcolor("white", false);
end

return Color;