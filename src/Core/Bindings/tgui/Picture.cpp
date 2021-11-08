#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/Picture.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassPicture(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Picture> bindPicture
            = tguiNamespace.new_usertype<tgui::Picture>("Picture", sol::call_constructor,
                sol::constructors<tgui::Picture(), tgui::Picture(const char*),
                    tgui::Picture(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindPicture["getSharedRenderer"]
            = sol::overload(static_cast<tgui::PictureRenderer* (tgui::Picture::*)()>(
                                &tgui::Picture::getSharedRenderer),
                static_cast<const tgui::PictureRenderer* (tgui::Picture::*)() const>(
                    &tgui::Picture::getSharedRenderer));
        bindPicture["getRenderer"] = sol::overload(
            static_cast<tgui::PictureRenderer* (tgui::Picture::*)()>(&tgui::Picture::getRenderer),
            static_cast<const tgui::PictureRenderer* (tgui::Picture::*)() const>(
                &tgui::Picture::getRenderer));
        bindPicture["setSize"] = sol::overload(
            static_cast<void (tgui::Picture::*)(const tgui::Layout2d&)>(&tgui::Picture::setSize),
            static_cast<void (tgui::Picture::*)(const tgui::Layout2d&)>(&tgui::Picture::setSize),
            static_cast<void (tgui::Picture::*)(tgui::Layout, tgui::Layout)>(
                &tgui::Picture::setSize));
        bindPicture["ignoreMouseEvents"]
            = sol::overload([](tgui::Picture* self) -> void { return self->ignoreMouseEvents(); },
                [](tgui::Picture* self, bool ignore) -> void {
                    return self->ignoreMouseEvents(ignore);
                });
        bindPicture["isIgnoringMouseEvents"] = &tgui::Picture::isIgnoringMouseEvents;
        bindPicture["canGainFocus"] = &tgui::Picture::canGainFocus;
        bindPicture["isMouseOnWidget"] = &tgui::Picture::isMouseOnWidget;
        bindPicture["leftMouseReleased"] = &tgui::Picture::leftMouseReleased;
        bindPicture["draw"] = &tgui::Picture::draw;
        bindPicture["create"] = sol::overload(
            static_cast<tgui::Picture::Ptr (tgui::Picture::*)()>(&tgui::Picture::create),
            [](const tgui::Texture& texture) -> tgui::Picture::Ptr {
                return tgui::Picture::create(texture);
            },
            [](const tgui::Texture& texture, bool transparentTexture) -> tgui::Picture::Ptr {
                return tgui::Picture::create(texture, transparentTexture);
            });
        bindPicture["copy"] = &tgui::Picture::copy;
        bindPicture["onDoubleClick"] = &tgui::Picture::onDoubleClick;
    }
};