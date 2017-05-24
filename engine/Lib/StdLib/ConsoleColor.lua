local Color = {};

function Color.print(text, indent)
    local indentString = "";
    if indent ~= nil then
        for i = 0, indent - 1 do
            indentString = indentString .. "    ";
        end
    end
    _term_display(indentString .. text.text, text.color[1], text.color[2], text.color[3]);
end

return Color;