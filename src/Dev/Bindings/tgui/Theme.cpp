#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Loading/Theme.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTheme(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Theme> bindTheme
            = tguiNamespace.new_usertype<tgui::Theme>("Theme", sol::call_constructor,
                sol::constructors<tgui::Theme(), tgui::Theme(const tgui::String&)>());
        bindTheme["load"] = &tgui::Theme::load;
        bindTheme["getRenderer"] = &tgui::Theme::getRenderer;
        bindTheme["getRendererNoThrow"] = &tgui::Theme::getRendererNoThrow;
        bindTheme["addRenderer"] = &tgui::Theme::addRenderer;
        bindTheme["removeRenderer"] = &tgui::Theme::removeRenderer;
        bindTheme["getPrimary"] = &tgui::Theme::getPrimary;
        bindTheme["create"] = sol::overload(
            [](tgui::Theme* self) -> tgui::Theme::Ptr { return self->create(); },
            [](tgui::Theme* self, const tgui::String& primary) -> tgui::Theme::Ptr {
                return self->create(primary);
            });
        bindTheme["setThemeLoader"] = &tgui::Theme::setThemeLoader;
        bindTheme["getThemeLoader"] = &tgui::Theme::getThemeLoader;
        bindTheme["setDefault"] = sol::overload(
            static_cast<void (*)(const tgui::String&)>(&tgui::Theme::setDefault),
            static_cast<void (*)(std::shared_ptr<tgui::Theme>)>(&tgui::Theme::setDefault),
            static_cast<void (*)(std::nullptr_t)>(&tgui::Theme::setDefault));
        bindTheme["getDefault"] = &tgui::Theme::getDefault;
    }
};