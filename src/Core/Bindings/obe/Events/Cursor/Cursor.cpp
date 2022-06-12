#include <Bindings/obe/Events/Cursor/Cursor.hpp>

#include <System/Cursor.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Cursor::Bindings
{
    void LoadClassHold(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["events"]["Cursor"].get<sol::table>();
        sol::usertype<obe::events::Cursor::Hold> bindHold
            = CursorNamespace.new_usertype<obe::events::Cursor::Hold>(
                "Hold", sol::call_constructor, sol::default_constructor);
        bindHold["x"] = &obe::events::Cursor::Hold::x;
        bindHold["y"] = &obe::events::Cursor::Hold::y;
        bindHold["left"] = &obe::events::Cursor::Hold::left;
        bindHold["middle"] = &obe::events::Cursor::Hold::middle;
        bindHold["right"] = &obe::events::Cursor::Hold::right;
        bindHold["id"] = sol::var(&obe::events::Cursor::Hold::id);
    }
    void LoadClassMove(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["events"]["Cursor"].get<sol::table>();
        sol::usertype<obe::events::Cursor::Move> bindMove
            = CursorNamespace.new_usertype<obe::events::Cursor::Move>(
                "Move", sol::call_constructor, sol::default_constructor);
        bindMove["x"] = &obe::events::Cursor::Move::x;
        bindMove["y"] = &obe::events::Cursor::Move::y;
        bindMove["previousX"] = &obe::events::Cursor::Move::previousX;
        bindMove["previousY"] = &obe::events::Cursor::Move::previousY;
        bindMove["id"] = sol::var(&obe::events::Cursor::Move::id);
    }
    void LoadClassPress(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["events"]["Cursor"].get<sol::table>();
        sol::usertype<obe::events::Cursor::Press> bindPress
            = CursorNamespace.new_usertype<obe::events::Cursor::Press>(
                "Press", sol::call_constructor, sol::default_constructor);
        bindPress["x"] = &obe::events::Cursor::Press::x;
        bindPress["y"] = &obe::events::Cursor::Press::y;
        bindPress["left"] = &obe::events::Cursor::Press::left;
        bindPress["middle"] = &obe::events::Cursor::Press::middle;
        bindPress["right"] = &obe::events::Cursor::Press::right;
        bindPress["id"] = sol::var(&obe::events::Cursor::Press::id);
    }
    void LoadClassRelease(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["events"]["Cursor"].get<sol::table>();
        sol::usertype<obe::events::Cursor::Release> bindRelease
            = CursorNamespace.new_usertype<obe::events::Cursor::Release>(
                "Release", sol::call_constructor, sol::default_constructor);
        bindRelease["x"] = &obe::events::Cursor::Release::x;
        bindRelease["y"] = &obe::events::Cursor::Release::y;
        bindRelease["left"] = &obe::events::Cursor::Release::left;
        bindRelease["middle"] = &obe::events::Cursor::Release::middle;
        bindRelease["right"] = &obe::events::Cursor::Release::right;
        bindRelease["id"] = sol::var(&obe::events::Cursor::Release::id);
    }
};