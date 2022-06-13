#include <Bindings/obe/Events/Cursor/Cursor.hpp>

#include <System/Cursor.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::cursor::Bindings
{
    void LoadClassHold(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["events"]["cursor"].get<sol::table>();
        sol::usertype<obe::events::cursor::Hold> bindHold
            = CursorNamespace.new_usertype<obe::events::cursor::Hold>(
                "Hold", sol::call_constructor, sol::default_constructor);
        bindHold["x"] = &obe::events::cursor::Hold::x;
        bindHold["y"] = &obe::events::cursor::Hold::y;
        bindHold["left"] = &obe::events::cursor::Hold::left;
        bindHold["middle"] = &obe::events::cursor::Hold::middle;
        bindHold["right"] = &obe::events::cursor::Hold::right;
        bindHold["id"] = sol::var(&obe::events::cursor::Hold::id);
    }
    void LoadClassMove(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["events"]["cursor"].get<sol::table>();
        sol::usertype<obe::events::cursor::Move> bindMove
            = CursorNamespace.new_usertype<obe::events::cursor::Move>(
                "Move", sol::call_constructor, sol::default_constructor);
        bindMove["x"] = &obe::events::cursor::Move::x;
        bindMove["y"] = &obe::events::cursor::Move::y;
        bindMove["previous_x"] = &obe::events::cursor::Move::previous_x;
        bindMove["previous_y"] = &obe::events::cursor::Move::previous_y;
        bindMove["id"] = sol::var(&obe::events::cursor::Move::id);
    }
    void LoadClassPress(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["events"]["cursor"].get<sol::table>();
        sol::usertype<obe::events::cursor::Press> bindPress
            = CursorNamespace.new_usertype<obe::events::cursor::Press>(
                "Press", sol::call_constructor, sol::default_constructor);
        bindPress["x"] = &obe::events::cursor::Press::x;
        bindPress["y"] = &obe::events::cursor::Press::y;
        bindPress["left"] = &obe::events::cursor::Press::left;
        bindPress["middle"] = &obe::events::cursor::Press::middle;
        bindPress["right"] = &obe::events::cursor::Press::right;
        bindPress["id"] = sol::var(&obe::events::cursor::Press::id);
    }
    void LoadClassRelease(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["events"]["cursor"].get<sol::table>();
        sol::usertype<obe::events::cursor::Release> bindRelease
            = CursorNamespace.new_usertype<obe::events::cursor::Release>(
                "Release", sol::call_constructor, sol::default_constructor);
        bindRelease["x"] = &obe::events::cursor::Release::x;
        bindRelease["y"] = &obe::events::cursor::Release::y;
        bindRelease["left"] = &obe::events::cursor::Release::left;
        bindRelease["middle"] = &obe::events::cursor::Release::middle;
        bindRelease["right"] = &obe::events::cursor::Release::right;
        bindRelease["id"] = sol::var(&obe::events::cursor::Release::id);
    }
};