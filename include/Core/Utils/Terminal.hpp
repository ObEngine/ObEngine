#pragma once

#include <string>

namespace obe::utils::terminal
{
    void styled_print(const std::string& str);

    struct CursorPosition
    {
        int x = 0;
        int y = 0;
    };

    CursorPosition get_cursor_position();
    void set_cursor_position(CursorPosition position);
    void set_terminal_mode_to_utf8();
}