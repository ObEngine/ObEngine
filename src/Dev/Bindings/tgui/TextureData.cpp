#include <Bindings/tgui/tgui.hpp>

#include <TGUI/TextureData.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTextureData(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextureData> bindTextureData
            = tguiNamespace.new_usertype<tgui::TextureData>(
                "TextureData", sol::call_constructor, sol::default_constructor);
        bindTextureData["svgImage"] = &tgui::TextureData::svgImage;
        bindTextureData["backendTexture"] = &tgui::TextureData::backendTexture;
    }
};