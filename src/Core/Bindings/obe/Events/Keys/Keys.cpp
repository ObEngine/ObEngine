#include <Bindings/obe/Events/Keys/Keys.hpp>

#include <Input/InputButtonMonitor.hpp>

#include <Bindings/Config.hpp>

namespace obe::Events::Keys::Bindings
{
    void LoadClassStateChanged(sol::state_view state)
    {
        sol::table KeysNamespace = state["obe"]["Events"]["Keys"].get<sol::table>();
        sol::usertype<obe::Events::Keys::StateChanged> bindStateChanged
            = KeysNamespace.new_usertype<obe::Events::Keys::StateChanged>("StateChanged");
        bindStateChanged["state"] = &obe::Events::Keys::StateChanged::state;
        bindStateChanged["previousState"] = &obe::Events::Keys::StateChanged::previousState;
    }
};