#include <Bindings/obe/Events/Actions/Actions.hpp>

#include <Input/InputAction.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::actions::Bindings
{
    void LoadClassAction(sol::state_view state)
    {
        sol::table ActionsNamespace = state["obe"]["events"]["actions"].get<sol::table>();
        sol::usertype<obe::events::actions::Action> bindAction
            = ActionsNamespace.new_usertype<obe::events::actions::Action>("Action");
        bindAction["action"]
            = sol::property([](obe::events::actions::Action* self) -> obe::input::InputAction& {
                  return self->action;
              });
        bindAction["condition"]
            = sol::property([](obe::events::actions::Action* self) -> obe::input::InputCondition& {
                  return self->condition;
              });
    }
};