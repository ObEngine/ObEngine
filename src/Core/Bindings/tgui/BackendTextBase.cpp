#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/BackendText.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBackendTextBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendTextBase> bindBackendTextBase
            = tguiNamespace.new_usertype<tgui::BackendTextBase>("BackendTextBase");
        bindBackendTextBase["getSize"] = &tgui::BackendTextBase::getSize;
        bindBackendTextBase["setString"] = &tgui::BackendTextBase::setString;
        bindBackendTextBase["setCharacterSize"] = &tgui::BackendTextBase::setCharacterSize;
        bindBackendTextBase["setFillColor"] = &tgui::BackendTextBase::setFillColor;
        bindBackendTextBase["setOutlineColor"] = &tgui::BackendTextBase::setOutlineColor;
        bindBackendTextBase["setOutlineThickness"] = &tgui::BackendTextBase::setOutlineThickness;
        bindBackendTextBase["setStyle"] = &tgui::BackendTextBase::setStyle;
        bindBackendTextBase["setFont"] = &tgui::BackendTextBase::setFont;
        bindBackendTextBase["findCharacterPos"] = &tgui::BackendTextBase::findCharacterPos;
    }
};