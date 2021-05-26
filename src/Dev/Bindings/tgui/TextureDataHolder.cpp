#include <Bindings/tgui/tgui.hpp>

#include <TGUI/TextureData.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTextureDataHolder(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextureDataHolder> bindTextureDataHolder
            = tguiNamespace.new_usertype<tgui::TextureDataHolder>(
                "TextureDataHolder", sol::call_constructor, sol::default_constructor);
        bindTextureDataHolder["data"] = &tgui::TextureDataHolder::data;
        bindTextureDataHolder["filename"] = &tgui::TextureDataHolder::filename;
        bindTextureDataHolder["smooth"] = &tgui::TextureDataHolder::smooth;
        bindTextureDataHolder["users"] = &tgui::TextureDataHolder::users;
    }
};