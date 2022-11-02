#include <Bindings/obe/events/Keys/Keys.hpp>

#include <Input/InputButtonMonitor.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Keys::bindings
{
    void load_class_pressed(sol::state_view state)
    {
        sol::table Keys_namespace = state["obe"]["events"]["Keys"].get<sol::table>();
        sol::usertype<obe::events::Keys::Pressed> bind_pressed
            = Keys_namespace.new_usertype<obe::events::Keys::Pressed>(
                "Pressed", sol::call_constructor, sol::default_constructor);
    }
    void load_class_state_changed(sol::state_view state)
    {
        sol::table Keys_namespace = state["obe"]["events"]["Keys"].get<sol::table>();
        sol::usertype<obe::events::Keys::StateChanged> bind_state_changed
            = Keys_namespace.new_usertype<obe::events::Keys::StateChanged>("StateChanged");
        bind_state_changed["state"] = &obe::events::Keys::StateChanged::state;
        bind_state_changed["previous_state"] = &obe::events::Keys::StateChanged::previous_state;
    }
};