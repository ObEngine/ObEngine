#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Animation.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadEnumShowAnimationType(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        tguiNamespace.new_enum<tgui::ShowAnimationType>("ShowAnimationType",
            { { "Fade", tgui::ShowAnimationType::Fade },
                { "Scale", tgui::ShowAnimationType::Scale },
                { "SlideToRight", tgui::ShowAnimationType::SlideToRight },
                { "SlideToLeft", tgui::ShowAnimationType::SlideToLeft },
                { "SlideToBottom", tgui::ShowAnimationType::SlideToBottom },
                { "SlideToTop", tgui::ShowAnimationType::SlideToTop },
                { "SlideFromLeft", tgui::ShowAnimationType::SlideFromLeft },
                { "SlideFromRight", tgui::ShowAnimationType::SlideFromRight },
                { "SlideFromTop", tgui::ShowAnimationType::SlideFromTop },
                { "SlideFromBottom", tgui::ShowAnimationType::SlideFromBottom } });
    }
};