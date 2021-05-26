#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/EditBox.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassEditBox(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::EditBox> bindEditBox
            = tguiNamespace.new_usertype<tgui::EditBox>("EditBox", sol::call_constructor,
                sol::constructors<tgui::EditBox(), tgui::EditBox(const char*),
                    tgui::EditBox(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindEditBox["getSharedRenderer"]
            = sol::overload(static_cast<tgui::EditBoxRenderer* (tgui::EditBox::*)()>(
                                &tgui::EditBox::getSharedRenderer),
                static_cast<const tgui::EditBoxRenderer* (tgui::EditBox::*)() const>(
                    &tgui::EditBox::getSharedRenderer));
        bindEditBox["getRenderer"]
            = sol::overload(static_cast<tgui::EditBoxRenderer* (tgui::EditBox::*)()>(
                                &tgui::EditBox::getRenderer),
                static_cast<const tgui::EditBoxRenderer* (tgui::EditBox::*)() const>(
                    &tgui::EditBox::getRenderer));
        bindEditBox["setSize"]
            = sol::overload(static_cast<void (tgui::EditBox::*)(const tgui::Layout2d&)>(
                                &tgui::EditBox::setSize),
                static_cast<void (tgui::EditBox::*)(const tgui::Layout2d&)>(
                    &tgui::EditBox::setSize),
                static_cast<void (tgui::EditBox::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::EditBox::setSize));
        bindEditBox["setEnabled"] = &tgui::EditBox::setEnabled;
        bindEditBox["setText"] = &tgui::EditBox::setText;
        bindEditBox["getText"] = &tgui::EditBox::getText;
        bindEditBox["setDefaultText"] = &tgui::EditBox::setDefaultText;
        bindEditBox["getDefaultText"] = &tgui::EditBox::getDefaultText;
        bindEditBox["selectText"] = sol::overload(
            [](tgui::EditBox* self) -> void { return self->selectText(); },
            [](tgui::EditBox* self, std::size_t start) -> void {
                return self->selectText(start);
            },
            [](tgui::EditBox* self, std::size_t start, std::size_t length) -> void {
                return self->selectText(start, length);
            });
        bindEditBox["getSelectedText"] = &tgui::EditBox::getSelectedText;
        bindEditBox["setTextSize"] = &tgui::EditBox::setTextSize;
        bindEditBox["getTextSize"] = &tgui::EditBox::getTextSize;
        bindEditBox["setPasswordCharacter"] = &tgui::EditBox::setPasswordCharacter;
        bindEditBox["getPasswordCharacter"] = &tgui::EditBox::getPasswordCharacter;
        bindEditBox["setMaximumCharacters"] = &tgui::EditBox::setMaximumCharacters;
        bindEditBox["getMaximumCharacters"] = &tgui::EditBox::getMaximumCharacters;
        bindEditBox["setAlignment"] = &tgui::EditBox::setAlignment;
        bindEditBox["getAlignment"] = &tgui::EditBox::getAlignment;
        bindEditBox["limitTextWidth"] = sol::overload(
            [](tgui::EditBox* self) -> void { return self->limitTextWidth(); },
            [](tgui::EditBox* self, bool limitWidth) -> void {
                return self->limitTextWidth(limitWidth);
            });
        bindEditBox["isTextWidthLimited"] = &tgui::EditBox::isTextWidthLimited;
        bindEditBox["setReadOnly"] = sol::overload(
            [](tgui::EditBox* self) -> void { return self->setReadOnly(); },
            [](tgui::EditBox* self, bool readOnly) -> void {
                return self->setReadOnly(readOnly);
            });
        bindEditBox["isReadOnly"] = &tgui::EditBox::isReadOnly;
        bindEditBox["setCaretPosition"] = &tgui::EditBox::setCaretPosition;
        bindEditBox["getCaretPosition"] = &tgui::EditBox::getCaretPosition;
        bindEditBox["setInputValidator"] = sol::overload(
            [](tgui::EditBox* self) -> bool { return self->setInputValidator(); },
            [](tgui::EditBox* self, const tgui::String& regex) -> bool {
                return self->setInputValidator(regex);
            });
        bindEditBox["getInputValidator"] = &tgui::EditBox::getInputValidator;
        bindEditBox["setSuffix"] = &tgui::EditBox::setSuffix;
        bindEditBox["getSuffix"] = &tgui::EditBox::getSuffix;
        bindEditBox["setFocused"] = &tgui::EditBox::setFocused;
        bindEditBox["isMouseOnWidget"] = &tgui::EditBox::isMouseOnWidget;
        bindEditBox["leftMousePressed"] = &tgui::EditBox::leftMousePressed;
        bindEditBox["mouseMoved"] = &tgui::EditBox::mouseMoved;
        bindEditBox["keyPressed"] = &tgui::EditBox::keyPressed;
        bindEditBox["textEntered"] = &tgui::EditBox::textEntered;
        bindEditBox["draw"] =

            [](tgui::EditBox* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindEditBox["create"] = &tgui::EditBox::create;
        bindEditBox["copy"] = &tgui::EditBox::copy;
        bindEditBox["onTextChange"] = &tgui::EditBox::onTextChange;
        bindEditBox["onReturnKeyPress"] = &tgui::EditBox::onReturnKeyPress;
        bindEditBox["onReturnOrUnfocus"] = &tgui::EditBox::onReturnOrUnfocus;
    }
};