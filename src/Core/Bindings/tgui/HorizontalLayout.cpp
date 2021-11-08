#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/HorizontalLayout.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassHorizontalLayout(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::HorizontalLayout> bindHorizontalLayout
            = tguiNamespace.new_usertype<tgui::HorizontalLayout>("HorizontalLayout",
                sol::call_constructor,
                sol::constructors<tgui::HorizontalLayout(), tgui::HorizontalLayout(const char*),
                    tgui::HorizontalLayout(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::BoxLayoutRatios, tgui::BoxLayout, tgui::Group, tgui::Container,
                    tgui::Widget>());
        bindHorizontalLayout["create"] = sol::overload(
            []() -> tgui::HorizontalLayout::Ptr { return tgui::HorizontalLayout::create(); },
            [](const tgui::Layout2d& size) -> tgui::HorizontalLayout::Ptr {
                return tgui::HorizontalLayout::create(size);
            });
        bindHorizontalLayout["copy"] = &tgui::HorizontalLayout::copy;
    }
};