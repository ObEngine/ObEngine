#include <Bindings/obe/Events/Keys/Keys.hpp>

#include <Input/InputButtonMonitor.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::keys::Bindings
{
    void LoadClassStateChanged(sol::state_view state)
    {
        sol::table KeysNamespace = state["obe"]["events"]["keys"].get<sol::table>();
        sol::usertype<obe::events::keys::StateChanged> bindStateChanged
            = KeysNamespace.new_usertype<obe::events::keys::StateChanged>("StateChanged");
        bindStateChanged["state"] = &obe::events::keys::StateChanged::state;
        bindStateChanged["previous_state"] = &obe::events::keys::StateChanged::previous_state;
    }
};