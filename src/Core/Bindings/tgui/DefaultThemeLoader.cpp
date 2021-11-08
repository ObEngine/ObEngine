#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Loading/ThemeLoader.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassDefaultThemeLoader(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::DefaultThemeLoader> bindDefaultThemeLoader
            = tguiNamespace.new_usertype<tgui::DefaultThemeLoader>("DefaultThemeLoader",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::BaseThemeLoader>());
        bindDefaultThemeLoader["preload"] = &tgui::DefaultThemeLoader::preload;
        bindDefaultThemeLoader["load"] = &tgui::DefaultThemeLoader::load;
        bindDefaultThemeLoader["canLoad"] = &tgui::DefaultThemeLoader::canLoad;
        bindDefaultThemeLoader["flushCache"]
            = sol::overload([]() -> void { return tgui::DefaultThemeLoader::flushCache(); },
                [](const tgui::String& filename) -> void {
                    return tgui::DefaultThemeLoader::flushCache(filename);
                });
    }
};