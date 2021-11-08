#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ComboBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumExpandDirection(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::ComboBox::ExpandDirection>("ExpandDirection",
            { { "Down", tgui::ComboBox::ExpandDirection::Down },
                { "Up", tgui::ComboBox::ExpandDirection::Up },
                { "Automatic", tgui::ComboBox::ExpandDirection::Automatic } });
    }
};