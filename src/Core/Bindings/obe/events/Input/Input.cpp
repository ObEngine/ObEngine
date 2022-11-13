#include <Bindings/obe/events/Input/Input.hpp>

#include <Input/InputManager.hpp>

#include <Bindings/Config.hpp>

namespace obe::events::Input::bindings
{
    void load_class_text_entered(sol::state_view state)
    {
        sol::table Input_namespace = state["obe"]["events"]["Input"].get<sol::table>();
        sol::usertype<obe::events::Input::TextEntered> bind_text_entered
            = Input_namespace.new_usertype<obe::events::Input::TextEntered>("TextEntered");
        bind_text_entered["text"] = &obe::events::Input::TextEntered::text;
        bind_text_entered["unicode"] = &obe::events::Input::TextEntered::unicode;
        bind_text_entered["id"] = sol::var(&obe::events::Input::TextEntered::id);
    }
};