#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/HorizontalWrap.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassHorizontalWrap(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::HorizontalWrap> bindHorizontalWrap
            = tguiNamespace.new_usertype<tgui::HorizontalWrap>("HorizontalWrap",
                sol::call_constructor,
                sol::constructors<tgui::HorizontalWrap(), tgui::HorizontalWrap(const char*),
                    tgui::HorizontalWrap(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::BoxLayout, tgui::Group, tgui::Container, tgui::Widget>());
        bindHorizontalWrap["create"] = sol::overload(
            []() -> tgui::HorizontalWrap::Ptr { return tgui::HorizontalWrap::create(); },
            [](const tgui::Layout2d& size) -> tgui::HorizontalWrap::Ptr {
                return tgui::HorizontalWrap::create(size);
            });
        bindHorizontalWrap["copy"] = &tgui::HorizontalWrap::copy;
    }
};