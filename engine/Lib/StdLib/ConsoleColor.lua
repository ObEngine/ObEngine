local Color = {};

inspect = require("Lib/StdLib/Inspect");

function Color.print(texttable, indent)
    local indentString = "";
    if indent ~= nil then
        for i = 0, indent - 1 do
            indentString = indentString .. "    ";
        end
    end
    local allTexts = {};
    local allColors = {};
    local firstString = true;
    for k, v in pairs(texttable) do
        local cText = v.text;
        if firstString then
            firstString = false;
            cText = indentString .. v.text;
        else
            cText = v.text;
        end
        table.insert(allTexts, cText);
        table.insert(allColors, SFML.Color(v.color[1], v.color[2], v.color[3]));
    end
    _term_display(allTexts, allColors);
end

return Color;