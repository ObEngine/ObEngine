#include <Bindings/obe/Events/Actions/Actions.hpp>

#include <Input/InputAction.hpp>

#include <Bindings/Config.hpp>

namespace obe::Events::Actions::Bindings
{
    void LoadClassAction(sol::state_view state)
    {
        sol::table ActionsNamespace = state["obe"]["Events"]["Actions"].get<sol::table>();
        sol::usertype<obe::Events::Actions::Action> bindAction
            = ActionsNamespace.new_usertype<obe::Events::Actions::Action>("Action");
        bindAction["action"] = sol::property(
            [](obe::Events::Actions::Action* self) -> Input::InputAction& {
                return self->action;
            });
        bindAction["condition"] = sol::property(
            [](obe::Events::Actions::Action* self) -> Input::InputCondition& {
                return self->condition;
            });
    }
};