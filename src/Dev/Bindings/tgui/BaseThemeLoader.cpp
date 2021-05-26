#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Loading/ThemeLoader.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBaseThemeLoader(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BaseThemeLoader> bindBaseThemeLoader
            = tguiNamespace.new_usertype<tgui::BaseThemeLoader>("BaseThemeLoader");
        bindBaseThemeLoader["preload"] = &tgui::BaseThemeLoader::preload;
        bindBaseThemeLoader["load"] = &tgui::BaseThemeLoader::load;
        bindBaseThemeLoader["canLoad"] = &tgui::BaseThemeLoader::canLoad;
    }
};