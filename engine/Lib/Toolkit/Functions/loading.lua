local Commands = require("Lib/Toolkit/Commands");

local function sleep(n)
    local t0 = os.clock()
    while os.clock() - t0 <= n do end
end

local function repeat_string(str, n)
    local final_str = "";
    for i = 1, n do
        final_str = final_str .. str;
    end
    return final_str;
end

local color_list = {
    "alice_blue",
    "antique_white",
    "aqua",
    "aquamarine",
    "azure",
    "beige",
    "bisque",
    "black",
    "blanched_almond",
    "blue",
    "blue_violet",
    "brown",
    "burly_wood",
    "cadet_blue",
    "chartreuse",
    "chocolate",
    "coral",
    "cornflower_blue",
    "cornsilk",
    "crimson",
    "cyan",
    "dark_blue",
    "dark_cyan",
    "dark_golden_rod",
    "dark_gray",
    "dark_green",
    "dark_khaki",
    "dark_magenta",
    "dark_olive_green",
    "dark_orange",
    "dark_orchid",
    "dark_red",
    "dark_salmon",
    "dark_sea_green",
    "dark_slate_blue",
    "dark_slate_gray",
    "dark_turquoise",
    "dark_violet",
    "deep_pink",
    "deep_sky_blue",
    "dim_gray",
    "dodger_blue",
    "fire_brick",
    "floral_white",
    "forest_green",
    "fuchsia",
    "gainsboro",
    "ghost_white",
    "gold",
    "golden_rod",
    "gray",
    "green",
    "green_yellow",
    "honey_dew",
    "hot_pink",
    "indian_red",
    "indigo",
    "ivory",
    "khaki",
    "lavender",
    "lavender_blush",
    "lawn_green",
    "lemon_chiffon",
    "light_blue",
    "light_coral",
    "light_cyan",
    "light_golden_rod_yellow",
    "light_gray",
    "light_green",
    "light_pink",
    "light_salmon",
    "light_sea_green",
    "light_sky_blue",
    "light_slate_gray",
    "light_steel_blue",
    "light_yellow",
    "lime",
    "lime_green",
    "linen",
    "magenta",
    "maroon",
    "medium_aquamarine",
    "medium_blue",
    "medium_orchid",
    "medium_purple",
    "medium_sea_green",
    "medium_slate_blue",
    "medium_spring_green",
    "medium_turquoise",
    "medium_violet_red",
    "midnight_blue",
    "mint_cream",
    "misty_rose",
    "moccasin",
    "navajo_white",
    "navy",
    "old_lace",
    "olive",
    "olive_drab",
    "orange",
    "orange_red",
    "orchid",
    "pale_golden_rod",
    "pale_green",
    "pale_turquoise",
    "pale_violet_red",
    "papaya_whip",
    "peach_puff",
    "peru",
    "pink",
    "plum",
    "powder_blue",
    "red",
    "rosy_brown",
    "royal_blue",
    "saddle_brown",
    "salmon",
    "sandy_brown",
    "sea_green",
    "sea_shell",
    "sienna",
    "silver",
    "sky_blue",
    "slate_blue",
    "slate_gray",
    "snow",
    "spring_green",
    "steel_blue",
    "tan",
    "teal",
    "thistle",
    "tomato",
    "turquoise",
    "violet",
    "wheat",
    "white",
    "white_smoke",
    "yellow",
    "yellow_green"
};

local function pad(space)
    io.write(("%s"):format(repeat_string(" ", space)));
    io.flush();
end

local function progress_bar_widget(config)
    local cursor_position = obe.utils.terminal.get_cursor_position();
    local color = config.color or "green";
    local total = config.total or 50;

    pad(total);

    return function(progress)
        obe.utils.terminal.set_cursor_position(cursor_position);
        local left_bar = repeat_string("━", progress);
        local right_bar = repeat_string("━", total - progress - 1);
        if progress ~= total then
            right_bar = "╺" .. right_bar;
        end
        obe.utils.terminal.styled_print(("{{%s}}%s{{faint|dim_gray}}%s"):format(color, left_bar, right_bar));
    end
end

local function text_widget()
    local cursor_position = obe.utils.terminal.get_cursor_position();
    local previous_text_length = 0;
    ---@param text string
    return function(text)
        obe.utils.terminal.set_cursor_position(cursor_position);
        print(("%s"):format(repeat_string(" ", previous_text_length)));
        obe.utils.terminal.set_cursor_position(cursor_position);
        obe.utils.terminal.styled_print(text);
        previous_text_length = text:len();

    end
end

local function time_format(seconds)
    local hours = math.floor(seconds / 3600)
    local minutes = math.floor(seconds / 60 % 60)
    local seconds = math.floor(seconds % 60)

    return string.format("%02d:%02d:%02d", hours, minutes, seconds)
end

local function _loading_()
    local total_size = 14.8;

    for _, color in pairs(color_list) do
        -- obe.utils.terminal.styled_print(("{{blink|bold|italic|%s}}%s{{italic}}text\n"):format(color, color));
    end

    local pbar = progress_bar_widget {
        color = "deep_pink",
        total = 50
    };
    pad(1);
    local utext = text_widget();
    for i = 0, 50 do
        pbar(i);
        local current_size = i * (total_size / 50);
        local random_speed = math.random() * 4;
        local eta = (total_size - current_size) / random_speed;
        utext(("{{lime}}%.2f/%.2f MB {{crimson}}%.2f MB/s {{white}}eta {{dodger_blue}}%s"):format(current_size, total_size, random_speed, time_format(eta)));
        sleep(0.05);
    end
end

return {
    Commands.call(_loading_);
    Commands.help("Display a loading bar");
};