#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Backend.hpp>
#include <TGUI/BackendFont.hpp>
#include <TGUI/BackendText.hpp>
#include <TGUI/BackendTexture.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassBackendBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::BackendBase> bindBackendBase
            = tguiNamespace.new_usertype<tgui::BackendBase>("BackendBase");
        bindBackendBase["setDestroyOnLastGuiDetatch"]
            = &tgui::BackendBase::setDestroyOnLastGuiDetatch;
        bindBackendBase["attachGui"] = &tgui::BackendBase::attachGui;
        bindBackendBase["detatchGui"] = &tgui::BackendBase::detatchGui;
        bindBackendBase["createDefaultFont"] = &tgui::BackendBase::createDefaultFont;
        bindBackendBase["createFont"] = &tgui::BackendBase::createFont;
        bindBackendBase["createText"] = &tgui::BackendBase::createText;
        bindBackendBase["createTexture"] = &tgui::BackendBase::createTexture;
        bindBackendBase["setMouseCursorStyle"] = &tgui::BackendBase::setMouseCursorStyle;
        bindBackendBase["resetMouseCursorStyle"]
            = &tgui::BackendBase::resetMouseCursorStyle;
        bindBackendBase["setMouseCursor"] = &tgui::BackendBase::setMouseCursor;
        bindBackendBase["openVirtualKeyboard"] = &tgui::BackendBase::openVirtualKeyboard;
        bindBackendBase["closeVirtualKeyboard"]
            = &tgui::BackendBase::closeVirtualKeyboard;
        bindBackendBase["isKeyboardModifierPressed"]
            = &tgui::BackendBase::isKeyboardModifierPressed;
        bindBackendBase["setClipboard"] = &tgui::BackendBase::setClipboard;
        bindBackendBase["getClipboard"] = &tgui::BackendBase::getClipboard;
        bindBackendBase["readFileFromAndroidAssets"] =

            [](tgui::BackendBase* self, const tgui::String& filename,
                std::size_t fileSize) {
                self->readFileFromAndroidAssets(filename, fileSize);
            }

        ;
    }
};