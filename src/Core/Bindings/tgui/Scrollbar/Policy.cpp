#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Scrollbar.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumPolicy(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::Scrollbar::Policy>("Policy",
            { { "Automatic", tgui::Scrollbar::Policy::Automatic },
                { "Always", tgui::Scrollbar::Policy::Always },
                { "Never", tgui::Scrollbar::Policy::Never } });
    }
};