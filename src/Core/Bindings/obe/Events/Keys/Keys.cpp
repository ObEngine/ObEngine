#include <Bindings/obe/events/keys/Keys.hpp>

#include <Input/InputButtonMonitor.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::keys::bindings
{
    void load_class_state_changed(sol::state_view state)
    {
        sol::table keys_namespace = state["obe"]["events"]["keys"].get<sol::table>();
        sol::usertype<obe::events::Keys::StateChanged> bind_state_changed
            = keys_namespace.new_usertype<obe::events::Keys::StateChanged>("StateChanged");
        bind_state_changed["state"] = &obe::events::Keys::StateChanged::state;
        bind_state_changed["previous_state"] = &obe::events::Keys::StateChanged::previous_state;
    }
};