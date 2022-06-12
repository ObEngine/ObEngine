#include <Bindings/obe/Events/Keys/Keys.hpp>

#include <Input/InputButtonMonitor.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Keys::Bindings
{
    void LoadClassStateChanged(sol::state_view state)
    {
        sol::table KeysNamespace = state["obe"]["events"]["Keys"].get<sol::table>();
        sol::usertype<obe::events::Keys::StateChanged> bindStateChanged
            = KeysNamespace.new_usertype<obe::events::Keys::StateChanged>("StateChanged");
        bindStateChanged["state"] = &obe::events::Keys::StateChanged::state;
        bindStateChanged["previousState"] = &obe::events::Keys::StateChanged::previousState;
    }
};