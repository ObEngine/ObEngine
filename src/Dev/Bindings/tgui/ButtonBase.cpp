#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/ButtonBase.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassButtonBase(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ButtonBase> bindButtonBase
            = tguiNamespace.new_usertype<tgui::ButtonBase>("ButtonBase",
                sol::call_constructor,
                sol::constructors<tgui::ButtonBase(const char*, bool),
                    tgui::ButtonBase(const tgui::ButtonBase&)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindButtonBase["operator="] = sol::overload(
            static_cast<tgui::ButtonBase& (tgui::ButtonBase::*)(const tgui::ButtonBase&)>(
                &tgui::ButtonBase::operator=),
            [](tgui::ButtonBase* self, tgui::ButtonBase p0) {
                self->operator=(std::move(p0));
            });
        bindButtonBase["getSharedRenderer"]
            = sol::overload(static_cast<tgui::ButtonRenderer* (tgui::ButtonBase::*)()>(
                                &tgui::ButtonBase::getSharedRenderer),
                static_cast<const tgui::ButtonRenderer* (tgui::ButtonBase::*)() const>(
                    &tgui::ButtonBase::getSharedRenderer));
        bindButtonBase["getRenderer"]
            = sol::overload(static_cast<tgui::ButtonRenderer* (tgui::ButtonBase::*)()>(
                                &tgui::ButtonBase::getRenderer),
                static_cast<const tgui::ButtonRenderer* (tgui::ButtonBase::*)() const>(
                    &tgui::ButtonBase::getRenderer));
        bindButtonBase["setSize"] = sol::overload(
            static_cast<void (tgui::ButtonBase::*)(const tgui::Layout2d&)>(
                &tgui::ButtonBase::setSize),
            static_cast<void (tgui::ButtonBase::*)(const tgui::Layout2d&)>(
                &tgui::ButtonBase::setSize),
            static_cast<void (tgui::ButtonBase::*)(tgui::Layout, tgui::Layout)>(
                &tgui::ButtonBase::setSize));
        bindButtonBase["setEnabled"] = &tgui::ButtonBase::setEnabled;
        bindButtonBase["setText"] = &tgui::ButtonBase::setText;
        bindButtonBase["getText"] = &tgui::ButtonBase::getText;
        bindButtonBase["setTextSize"] = &tgui::ButtonBase::setTextSize;
        bindButtonBase["getTextSize"] = &tgui::ButtonBase::getTextSize;
        bindButtonBase["setFocused"] = &tgui::ButtonBase::setFocused;
        bindButtonBase["isMouseOnWidget"] = &tgui::ButtonBase::isMouseOnWidget;
        bindButtonBase["leftMousePressed"] = &tgui::ButtonBase::leftMousePressed;
        bindButtonBase["leftMouseReleased"] = &tgui::ButtonBase::leftMouseReleased;
        bindButtonBase["leftMouseButtonNoLongerDown"]
            = &tgui::ButtonBase::leftMouseButtonNoLongerDown;
        bindButtonBase["draw"] =

            [](tgui::ButtonBase* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
    }
};