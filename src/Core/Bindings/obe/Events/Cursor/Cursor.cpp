#include <Bindings/obe/Events/Cursor/Cursor.hpp>

#include <System/Cursor.hpp>

#include <Bindings/Config.hpp>

namespace obe::Events::Cursor::Bindings
{
    void LoadClassHold(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["Events"]["Cursor"].get<sol::table>();
        sol::usertype<obe::Events::Cursor::Hold> bindHold
            = CursorNamespace.new_usertype<obe::Events::Cursor::Hold>(
                "Hold", sol::call_constructor, sol::default_constructor);
        bindHold["x"] = &obe::Events::Cursor::Hold::x;
        bindHold["y"] = &obe::Events::Cursor::Hold::y;
        bindHold["left"] = &obe::Events::Cursor::Hold::left;
        bindHold["middle"] = &obe::Events::Cursor::Hold::middle;
        bindHold["right"] = &obe::Events::Cursor::Hold::right;
        bindHold["id"] = sol::var(&obe::Events::Cursor::Hold::id);
    }
    void LoadClassMove(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["Events"]["Cursor"].get<sol::table>();
        sol::usertype<obe::Events::Cursor::Move> bindMove
            = CursorNamespace.new_usertype<obe::Events::Cursor::Move>(
                "Move", sol::call_constructor, sol::default_constructor);
        bindMove["x"] = &obe::Events::Cursor::Move::x;
        bindMove["y"] = &obe::Events::Cursor::Move::y;
        bindMove["previousX"] = &obe::Events::Cursor::Move::previousX;
        bindMove["previousY"] = &obe::Events::Cursor::Move::previousY;
        bindMove["id"] = sol::var(&obe::Events::Cursor::Move::id);
    }
    void LoadClassPress(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["Events"]["Cursor"].get<sol::table>();
        sol::usertype<obe::Events::Cursor::Press> bindPress
            = CursorNamespace.new_usertype<obe::Events::Cursor::Press>(
                "Press", sol::call_constructor, sol::default_constructor);
        bindPress["x"] = &obe::Events::Cursor::Press::x;
        bindPress["y"] = &obe::Events::Cursor::Press::y;
        bindPress["left"] = &obe::Events::Cursor::Press::left;
        bindPress["middle"] = &obe::Events::Cursor::Press::middle;
        bindPress["right"] = &obe::Events::Cursor::Press::right;
        bindPress["id"] = sol::var(&obe::Events::Cursor::Press::id);
    }
    void LoadClassRelease(sol::state_view state)
    {
        sol::table CursorNamespace = state["obe"]["Events"]["Cursor"].get<sol::table>();
        sol::usertype<obe::Events::Cursor::Release> bindRelease
            = CursorNamespace.new_usertype<obe::Events::Cursor::Release>(
                "Release", sol::call_constructor, sol::default_constructor);
        bindRelease["x"] = &obe::Events::Cursor::Release::x;
        bindRelease["y"] = &obe::Events::Cursor::Release::y;
        bindRelease["left"] = &obe::Events::Cursor::Release::left;
        bindRelease["middle"] = &obe::Events::Cursor::Release::middle;
        bindRelease["right"] = &obe::Events::Cursor::Release::right;
        bindRelease["id"] = sol::var(&obe::Events::Cursor::Release::id);
    }
};