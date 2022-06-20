#include <Bindings/obe/events/cursor/Cursor.hpp>

#include <System/Cursor.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::cursor::bindings
{
    void load_class_hold(sol::state_view state)
    {
        sol::table cursor_namespace = state["obe"]["events"]["cursor"].get<sol::table>();
        sol::usertype<obe::events::Cursor::Hold> bind_hold
            = cursor_namespace.new_usertype<obe::events::Cursor::Hold>(
                "Hold", sol::call_constructor, sol::default_constructor);
        bind_hold["x"] = &obe::events::Cursor::Hold::x;
        bind_hold["y"] = &obe::events::Cursor::Hold::y;
        bind_hold["left"] = &obe::events::Cursor::Hold::left;
        bind_hold["middle"] = &obe::events::Cursor::Hold::middle;
        bind_hold["right"] = &obe::events::Cursor::Hold::right;
        bind_hold["id"] = sol::var(&obe::events::Cursor::Hold::id);
    }
    void load_class_move(sol::state_view state)
    {
        sol::table cursor_namespace = state["obe"]["events"]["cursor"].get<sol::table>();
        sol::usertype<obe::events::Cursor::Move> bind_move
            = cursor_namespace.new_usertype<obe::events::Cursor::Move>(
                "Move", sol::call_constructor, sol::default_constructor);
        bind_move["x"] = &obe::events::Cursor::Move::x;
        bind_move["y"] = &obe::events::Cursor::Move::y;
        bind_move["previous_x"] = &obe::events::Cursor::Move::previous_x;
        bind_move["previous_y"] = &obe::events::Cursor::Move::previous_y;
        bind_move["id"] = sol::var(&obe::events::Cursor::Move::id);
    }
    void load_class_press(sol::state_view state)
    {
        sol::table cursor_namespace = state["obe"]["events"]["cursor"].get<sol::table>();
        sol::usertype<obe::events::Cursor::Press> bind_press
            = cursor_namespace.new_usertype<obe::events::Cursor::Press>(
                "Press", sol::call_constructor, sol::default_constructor);
        bind_press["x"] = &obe::events::Cursor::Press::x;
        bind_press["y"] = &obe::events::Cursor::Press::y;
        bind_press["left"] = &obe::events::Cursor::Press::left;
        bind_press["middle"] = &obe::events::Cursor::Press::middle;
        bind_press["right"] = &obe::events::Cursor::Press::right;
        bind_press["id"] = sol::var(&obe::events::Cursor::Press::id);
    }
    void load_class_release(sol::state_view state)
    {
        sol::table cursor_namespace = state["obe"]["events"]["cursor"].get<sol::table>();
        sol::usertype<obe::events::Cursor::Release> bind_release
            = cursor_namespace.new_usertype<obe::events::Cursor::Release>(
                "Release", sol::call_constructor, sol::default_constructor);
        bind_release["x"] = &obe::events::Cursor::Release::x;
        bind_release["y"] = &obe::events::Cursor::Release::y;
        bind_release["left"] = &obe::events::Cursor::Release::left;
        bind_release["middle"] = &obe::events::Cursor::Release::middle;
        bind_release["right"] = &obe::events::Cursor::Release::right;
        bind_release["id"] = sol::var(&obe::events::Cursor::Release::id);
    }
};