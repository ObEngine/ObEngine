#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/RadioButtonGroup.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRadioButtonGroup(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RadioButtonGroup> bindRadioButtonGroup
            = tguiNamespace.new_usertype<tgui::RadioButtonGroup>("RadioButtonGroup",
                sol::call_constructor,
                sol::constructors<tgui::RadioButtonGroup(), tgui::RadioButtonGroup(const char*),
                    tgui::RadioButtonGroup(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Group, tgui::Container, tgui::Widget>());
        bindRadioButtonGroup["uncheckRadioButtons"] = &tgui::RadioButtonGroup::uncheckRadioButtons;
        bindRadioButtonGroup["getCheckedRadioButton"]
            = &tgui::RadioButtonGroup::getCheckedRadioButton;
        bindRadioButtonGroup["draw"] = &tgui::RadioButtonGroup::draw;
        bindRadioButtonGroup["create"] = &tgui::RadioButtonGroup::create;
        bindRadioButtonGroup["copy"] = &tgui::RadioButtonGroup::copy;
    }
};