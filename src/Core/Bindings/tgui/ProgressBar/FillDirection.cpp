#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ProgressBar.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumFillDirection(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::ProgressBar::FillDirection>("FillDirection",
            { { "LeftToRight", tgui::ProgressBar::FillDirection::LeftToRight },
                { "RightToLeft", tgui::ProgressBar::FillDirection::RightToLeft },
                { "TopToBottom", tgui::ProgressBar::FillDirection::TopToBottom },
                { "BottomToTop", tgui::ProgressBar::FillDirection::BottomToTop } });
    }
};