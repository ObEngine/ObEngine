#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/TextureManager.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTextureManager(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextureManager> bindTextureManager
            = tguiNamespace.new_usertype<tgui::TextureManager>(
                "TextureManager", sol::call_constructor, sol::default_constructor);
        bindTextureManager["getTexture"] = &tgui::TextureManager::getTexture;
        bindTextureManager["copyTexture"] = &tgui::TextureManager::copyTexture;
        bindTextureManager["removeTexture"] = &tgui::TextureManager::removeTexture;
        bindTextureManager["getCachedImagesCount"] = &tgui::TextureManager::getCachedImagesCount;
    }
};