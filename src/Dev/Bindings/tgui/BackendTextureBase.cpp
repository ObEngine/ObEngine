#include <Bindings/tgui/tgui.hpp>

#include <TGUI/BackendTexture.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBackendTextureBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendTextureBase> bindBackendTextureBase
            = tguiNamespace.new_usertype<tgui::BackendTextureBase>("BackendTextureBase");
        bindBackendTextureBase["getSize"] = &tgui::BackendTextureBase::getSize;
        bindBackendTextureBase["setSmooth"] = &tgui::BackendTextureBase::setSmooth;
        bindBackendTextureBase["isSmooth"] = &tgui::BackendTextureBase::isSmooth;
        bindBackendTextureBase["isTransparentPixel"]
            = &tgui::BackendTextureBase::isTransparentPixel;
    }
};