#include <Bindings/obe/events/Actions/Actions.hpp>

#include <Input/InputAction.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Actions::bindings
{
    void load_class_action(sol::state_view state)
    {
        sol::table Actions_namespace = state["obe"]["events"]["Actions"].get<sol::table>();
        sol::usertype<obe::events::Actions::Action> bind_action
            = Actions_namespace.new_usertype<obe::events::Actions::Action>("Action");
        bind_action["action"]
            = sol::property([](obe::events::Actions::Action* self) -> obe::input::InputAction&
                { return self->action; });
        bind_action["condition"]
            = sol::property([](obe::events::Actions::Action* self) -> obe::input::InputCondition&
                { return self->condition; });
    }
};