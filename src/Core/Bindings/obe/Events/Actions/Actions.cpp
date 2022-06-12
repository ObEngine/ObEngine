#include <Bindings/obe/Events/Actions/Actions.hpp>

#include <Input/InputAction.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Actions::Bindings
{
    void LoadClassAction(sol::state_view state)
    {
        sol::table ActionsNamespace = state["obe"]["events"]["Actions"].get<sol::table>();
        sol::usertype<obe::events::Actions::Action> bindAction
            = ActionsNamespace.new_usertype<obe::events::Actions::Action>("Action");
        bindAction["action"]
            = sol::property([](obe::events::Actions::Action* self) -> obe::Input::InputAction& {
                  return self->action;
              });
        bindAction["condition"]
            = sol::property([](obe::events::Actions::Action* self) -> obe::Input::InputCondition& {
                  return self->condition;
              });
    }
};