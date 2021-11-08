#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/EditBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassValidator(sol::state_view state)
    {
        sol::table EditBoxNamespace = state["tgui"]["EditBox"].get<sol::table>();
        sol::usertype<tgui::EditBox::Validator> bindValidator
            = EditBoxNamespace.new_usertype<tgui::EditBox::Validator>(
                "Validator", sol::call_constructor, sol::default_constructor);
        bindValidator["All"] = sol::var(&tgui::EditBox::Validator::All);
        bindValidator["Int"] = sol::var(&tgui::EditBox::Validator::Int);
        bindValidator["UInt"] = sol::var(&tgui::EditBox::Validator::UInt);
        bindValidator["Float"] = sol::var(&tgui::EditBox::Validator::Float);
    }
};