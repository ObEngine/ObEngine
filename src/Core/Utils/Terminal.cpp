#include <iostream>

#include <fmt/color.h>
#include <fmt/core.h>

#include <Exception.hpp>
#include <Types/SmartEnum.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/Terminal.hpp>

template <>
struct magic_enum::customize::enum_range<fmt::emphasis>
{
    static constexpr bool is_flags = true;
};

namespace
{
    std::unordered_map<std::string, fmt::color> fmt_color_mapping = {
        { "alice_blue", fmt::color::alice_blue },
        { "antique_white", fmt::color::antique_white },
        { "aqua", fmt::color::aqua },
        { "aquamarine", fmt::color::aquamarine },
        { "azure", fmt::color::azure },
        { "beige", fmt::color::beige },
        { "bisque", fmt::color::bisque },
        { "black", fmt::color::black },
        { "blanched_almond", fmt::color::blanched_almond },
        { "blue", fmt::color::blue },
        { "blue_violet", fmt::color::blue_violet },
        { "brown", fmt::color::brown },
        { "burly_wood", fmt::color::burly_wood },
        { "cadet_blue", fmt::color::cadet_blue },
        { "chartreuse", fmt::color::chartreuse },
        { "chocolate", fmt::color::chocolate },
        { "coral", fmt::color::coral },
        { "cornflower_blue", fmt::color::cornflower_blue },
        { "cornsilk", fmt::color::cornsilk },
        { "crimson", fmt::color::crimson },
        { "cyan", fmt::color::cyan },
        { "dark_blue", fmt::color::dark_blue },
        { "dark_cyan", fmt::color::dark_cyan },
        { "dark_golden_rod", fmt::color::dark_golden_rod },
        { "dark_gray", fmt::color::dark_gray },
        { "dark_green", fmt::color::dark_green },
        { "dark_khaki", fmt::color::dark_khaki },
        { "dark_magenta", fmt::color::dark_magenta },
        { "dark_olive_green", fmt::color::dark_olive_green },
        { "dark_orange", fmt::color::dark_orange },
        { "dark_orchid", fmt::color::dark_orchid },
        { "dark_red", fmt::color::dark_red },
        { "dark_salmon", fmt::color::dark_salmon },
        { "dark_sea_green", fmt::color::dark_sea_green },
        { "dark_slate_blue", fmt::color::dark_slate_blue },
        { "dark_slate_gray", fmt::color::dark_slate_gray },
        { "dark_turquoise", fmt::color::dark_turquoise },
        { "dark_violet", fmt::color::dark_violet },
        { "deep_pink", fmt::color::deep_pink },
        { "deep_sky_blue", fmt::color::deep_sky_blue },
        { "dim_gray", fmt::color::dim_gray },
        { "dodger_blue", fmt::color::dodger_blue },
        { "fire_brick", fmt::color::fire_brick },
        { "floral_white", fmt::color::floral_white },
        { "forest_green", fmt::color::forest_green },
        { "fuchsia", fmt::color::fuchsia },
        { "gainsboro", fmt::color::gainsboro },
        { "ghost_white", fmt::color::ghost_white },
        { "gold", fmt::color::gold },
        { "golden_rod", fmt::color::golden_rod },
        { "gray", fmt::color::gray },
        { "green", fmt::color::green },
        { "green_yellow", fmt::color::green_yellow },
        { "honey_dew", fmt::color::honey_dew },
        { "hot_pink", fmt::color::hot_pink },
        { "indian_red", fmt::color::indian_red },
        { "indigo", fmt::color::indigo },
        { "ivory", fmt::color::ivory },
        { "khaki", fmt::color::khaki },
        { "lavender", fmt::color::lavender },
        { "lavender_blush", fmt::color::lavender_blush },
        { "lawn_green", fmt::color::lawn_green },
        { "lemon_chiffon", fmt::color::lemon_chiffon },
        { "light_blue", fmt::color::light_blue },
        { "light_coral", fmt::color::light_coral },
        { "light_cyan", fmt::color::light_cyan },
        { "light_golden_rod_yellow", fmt::color::light_golden_rod_yellow },
        { "light_gray", fmt::color::light_gray },
        { "light_green", fmt::color::light_green },
        { "light_pink", fmt::color::light_pink },
        { "light_salmon", fmt::color::light_salmon },
        { "light_sea_green", fmt::color::light_sea_green },
        { "light_sky_blue", fmt::color::light_sky_blue },
        { "light_slate_gray", fmt::color::light_slate_gray },
        { "light_steel_blue", fmt::color::light_steel_blue },
        { "light_yellow", fmt::color::light_yellow },
        { "lime", fmt::color::lime },
        { "lime_green", fmt::color::lime_green },
        { "linen", fmt::color::linen },
        { "magenta", fmt::color::magenta },
        { "maroon", fmt::color::maroon },
        { "medium_aquamarine", fmt::color::medium_aquamarine },
        { "medium_blue", fmt::color::medium_blue },
        { "medium_orchid", fmt::color::medium_orchid },
        { "medium_purple", fmt::color::medium_purple },
        { "medium_sea_green", fmt::color::medium_sea_green },
        { "medium_slate_blue", fmt::color::medium_slate_blue },
        { "medium_spring_green", fmt::color::medium_spring_green },
        { "medium_turquoise", fmt::color::medium_turquoise },
        { "medium_violet_red", fmt::color::medium_violet_red },
        { "midnight_blue", fmt::color::midnight_blue },
        { "mint_cream", fmt::color::mint_cream },
        { "misty_rose", fmt::color::misty_rose },
        { "moccasin", fmt::color::moccasin },
        { "navajo_white", fmt::color::navajo_white },
        { "navy", fmt::color::navy },
        { "old_lace", fmt::color::old_lace },
        { "olive", fmt::color::olive },
        { "olive_drab", fmt::color::olive_drab },
        { "orange", fmt::color::orange },
        { "orange_red", fmt::color::orange_red },
        { "orchid", fmt::color::orchid },
        { "pale_golden_rod", fmt::color::pale_golden_rod },
        { "pale_green", fmt::color::pale_green },
        { "pale_turquoise", fmt::color::pale_turquoise },
        { "pale_violet_red", fmt::color::pale_violet_red },
        { "papaya_whip", fmt::color::papaya_whip },
        { "peach_puff", fmt::color::peach_puff },
        { "peru", fmt::color::peru },
        { "pink", fmt::color::pink },
        { "plum", fmt::color::plum },
        { "powder_blue", fmt::color::powder_blue },
        { "red", fmt::color::red },
        { "rosy_brown", fmt::color::rosy_brown },
        { "royal_blue", fmt::color::royal_blue },
        { "saddle_brown", fmt::color::saddle_brown },
        { "salmon", fmt::color::salmon },
        { "sandy_brown", fmt::color::sandy_brown },
        { "sea_green", fmt::color::sea_green },
        { "sea_shell", fmt::color::sea_shell },
        { "sienna", fmt::color::sienna },
        { "silver", fmt::color::silver },
        { "sky_blue", fmt::color::sky_blue },
        { "slate_blue", fmt::color::slate_blue },
        { "slate_gray", fmt::color::slate_gray },
        { "snow", fmt::color::snow },
        { "spring_green", fmt::color::spring_green },
        { "steel_blue", fmt::color::steel_blue },
        { "tan", fmt::color::tan },
        { "teal", fmt::color::teal },
        { "thistle", fmt::color::thistle },
        { "tomato", fmt::color::tomato },
        { "turquoise", fmt::color::turquoise },
        { "violet", fmt::color::violet },
        { "wheat", fmt::color::wheat },
        { "white", fmt::color::white },
        { "white_smoke", fmt::color::white_smoke },
        { "yellow", fmt::color::yellow },
        { "yellow_green", fmt::color::yellow_green },
    };

    template <class Enum>
    bool contains_enum_value(const std::string& value)
    {
        auto enum_value = magic_enum::enum_cast<Enum>(value);
        return enum_value.has_value();
    }
}

namespace obe::utils::terminal
{
    namespace exceptions
    {
        class InvalidStyle : public Exception<InvalidStyle>
        {
        public:
            using Exception::Exception;
            InvalidStyle(std::string_view style,
                std::source_location location = std::source_location::current())
                : Exception(location)
            {
                this->error("Invalid style : '{}'", style);
            }
        };
    }

    void styled_print(const std::string& str)
    {
        bool in_tag = false;
        size_t previous_tag_end = 0;
        size_t tag_start = 0;
        fmt::text_style text_style = fmt::text_style {};
        for (size_t i = 0; i < str.size(); i++)
        {
            if (in_tag && str.substr(i, 2) == "}}")
            {
                in_tag = false;

                std::string tag_content = str.substr(tag_start + 2, i - tag_start - 2);
                std::vector<std::string> style_parts = utils::string::split(tag_content, "|");
                text_style = fmt::text_style {};
                for (const std::string& style_part : style_parts)
                {
                    if (style_part.starts_with("fg:"))
                    {
                        std::string color_name = style_part.substr(3);
                        if (fmt_color_mapping.contains(color_name))
                        {
                            text_style |= fg(fmt_color_mapping.at(color_name));
                        }
                        else
                        {
                            throw exceptions::InvalidStyle(style_part);
                        }
                    }
                    else if (style_part.starts_with("bg:"))
                    {
                        std::string color_name = style_part.substr(3);
                        if (fmt_color_mapping.contains(color_name))
                        {
                            text_style |= bg(fmt_color_mapping.at(color_name));
                        }
                        else
                        {
                            throw exceptions::InvalidStyle(style_part);
                        }
                    }
                    else if (style_part.starts_with("em:"))
                    {
                        std::string emphasis_name = style_part.substr(3);
                        if (contains_enum_value<fmt::emphasis>(emphasis_name))
                        {
                            text_style |= fmt::text_style(
                                magic_enum::enum_cast<fmt::emphasis>(emphasis_name).value());
                        }
                        else
                        {
                            throw exceptions::InvalidStyle(style_part);
                        }
                    }
                    else if (fmt_color_mapping.contains(style_part))
                    {
                        text_style |= fmt::fg(fmt_color_mapping.at(style_part));
                    }
                    else if (contains_enum_value<fmt::emphasis>(style_part))
                    {
                        text_style |= fmt::text_style(
                            magic_enum::enum_cast<fmt::emphasis>(style_part).value());
                    }
                    else if (style_part == "reset")
                    {
                        text_style = {};
                    }
                    else
                    {
                        throw exceptions::InvalidStyle(style_part);
                    }
                }

                previous_tag_end = i + 2;
            }
            else if (str.substr(i, 2) == "{{")
            {
                if (previous_tag_end != 0)
                {
                    fmt::print(text_style, str.substr(previous_tag_end, i - previous_tag_end));
                }

                in_tag = true;
                tag_start = i;
            }
        }
        fmt::print(text_style, str.substr(previous_tag_end, str.size() - previous_tag_end));
        std::cout << std::flush;
    }

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#elif __unix__
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#endif

    CursorPosition get_cursor_position()
    {
        CursorPosition position;
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        position.x = csbi.dwCursorPosition.X;
        position.y = csbi.dwCursorPosition.Y;
#elif __unix__
        printf("\033[6n");
        scanf("\033[%d;%dR", &position.y, &position.x);
        // Restore standard input settings
        struct termios original_ts, raw_ts;
        tcgetattr(STDIN_FILENO, &original_ts);
        raw_ts = original_ts;
        raw_ts.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_ts);
        while ((x = getchar()) != EOF && x != 'R')
            ;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_ts);
#else
        #error "OS not supported!"
#endif
        return position;
    }

    void set_cursor_position(CursorPosition position)
    {
#ifdef _WIN32
        COORD coord = { position.x, position.y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#elif __unix__
        printf("\033[%d;%dH", y, x);
#else
#error "OS not supported!"
#endif
    }

    void set_terminal_mode_to_utf8()
    {
#ifdef _WIN32
        // Set the console code page to UTF-8
        SetConsoleOutputCP(CP_UTF8);

        // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
        setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
    }
}