#include <Bindings/obe/events/actions/Actions.hpp>

#include <Input/InputAction.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::actions::bindings
{
    void load_class_action(sol::state_view state)
    {
        sol::table actions_namespace = state["obe"]["events"]["actions"].get<sol::table>();
        sol::usertype<obe::events::Actions::Action> bind_action
            = actions_namespace.new_usertype<obe::events::Actions::Action>("Action");
        bind_action["action"]
            = sol::property([](obe::events::Actions::Action* self) -> obe::input::InputAction&
                {
                  return self->action;
              });
        bind_action["condition"]
            = sol::property([](obe::events::Actions::Action* self) -> obe::input::InputCondition&
                {
                  return self->condition;
              });
    }
};