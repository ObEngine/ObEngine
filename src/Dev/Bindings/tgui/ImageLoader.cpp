#include <Bindings/tgui/tgui.hpp>

#include <Bindings/Patches.hpp>
#include <TGUI/Loading/ImageLoader.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassImageLoader(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ImageLoader> bindImageLoader
            = tguiNamespace.new_usertype<tgui::ImageLoader>(
                "ImageLoader", sol::call_constructor, sol::default_constructor);
        bindImageLoader["loadFromFile"] = &tgui::_ImageLoader_loadFromFile_proxy;
        bindImageLoader["loadFromMemory"] = &tgui::_ImageLoader_loadFromMemory_proxy;
    }
};