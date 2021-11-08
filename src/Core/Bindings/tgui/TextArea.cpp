#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/TextArea.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTextArea(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TextArea> bindTextArea
            = tguiNamespace.new_usertype<tgui::TextArea>("TextArea", sol::call_constructor,
                sol::constructors<tgui::TextArea(), tgui::TextArea(const char*),
                    tgui::TextArea(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindTextArea["getSharedRenderer"]
            = sol::overload(static_cast<tgui::TextAreaRenderer* (tgui::TextArea::*)()>(
                                &tgui::TextArea::getSharedRenderer),
                static_cast<const tgui::TextAreaRenderer* (tgui::TextArea::*)() const>(
                    &tgui::TextArea::getSharedRenderer));
        bindTextArea["getRenderer"]
            = sol::overload(static_cast<tgui::TextAreaRenderer* (tgui::TextArea::*)()>(
                                &tgui::TextArea::getRenderer),
                static_cast<const tgui::TextAreaRenderer* (tgui::TextArea::*)() const>(
                    &tgui::TextArea::getRenderer));
        bindTextArea["setSize"] = sol::overload(
            static_cast<void (tgui::TextArea::*)(const tgui::Layout2d&)>(&tgui::TextArea::setSize),
            static_cast<void (tgui::TextArea::*)(const tgui::Layout2d&)>(&tgui::TextArea::setSize),
            static_cast<void (tgui::TextArea::*)(tgui::Layout, tgui::Layout)>(
                &tgui::TextArea::setSize));
        bindTextArea["setText"] = &tgui::TextArea::setText;
        bindTextArea["addText"] = &tgui::TextArea::addText;
        bindTextArea["getText"] = &tgui::TextArea::getText;
        bindTextArea["setDefaultText"] = &tgui::TextArea::setDefaultText;
        bindTextArea["getDefaultText"] = &tgui::TextArea::getDefaultText;
        bindTextArea["setSelectedText"] = &tgui::TextArea::setSelectedText;
        bindTextArea["getSelectedText"] = &tgui::TextArea::getSelectedText;
        bindTextArea["getSelectionStart"] = &tgui::TextArea::getSelectionStart;
        bindTextArea["getSelectionEnd"] = &tgui::TextArea::getSelectionEnd;
        bindTextArea["setTextSize"] = &tgui::TextArea::setTextSize;
        bindTextArea["setMaximumCharacters"] = sol::overload(
            [](tgui::TextArea* self) -> void { return self->setMaximumCharacters(); },
            [](tgui::TextArea* self, std::size_t maxChars) -> void {
                return self->setMaximumCharacters(maxChars);
            });
        bindTextArea["getMaximumCharacters"] = &tgui::TextArea::getMaximumCharacters;
        bindTextArea["setCaretPosition"] = &tgui::TextArea::setCaretPosition;
        bindTextArea["getCaretPosition"] = &tgui::TextArea::getCaretPosition;
        bindTextArea["setReadOnly"]
            = sol::overload([](tgui::TextArea* self) -> void { return self->setReadOnly(); },
                [](tgui::TextArea* self, bool readOnly) -> void {
                    return self->setReadOnly(readOnly);
                });
        bindTextArea["isReadOnly"] = &tgui::TextArea::isReadOnly;
        bindTextArea["setVerticalScrollbarPolicy"] = &tgui::TextArea::setVerticalScrollbarPolicy;
        bindTextArea["getVerticalScrollbarPolicy"] = &tgui::TextArea::getVerticalScrollbarPolicy;
        bindTextArea["setHorizontalScrollbarPolicy"]
            = &tgui::TextArea::setHorizontalScrollbarPolicy;
        bindTextArea["getHorizontalScrollbarPolicy"]
            = &tgui::TextArea::getHorizontalScrollbarPolicy;
        bindTextArea["getLinesCount"] = &tgui::TextArea::getLinesCount;
        bindTextArea["setFocused"] = &tgui::TextArea::setFocused;
        bindTextArea["enableMonospacedFontOptimization"] = sol::overload(
            [](tgui::TextArea* self) -> void { return self->enableMonospacedFontOptimization(); },
            [](tgui::TextArea* self, bool enable) -> void {
                return self->enableMonospacedFontOptimization(enable);
            });
        bindTextArea["setVerticalScrollbarValue"] = &tgui::TextArea::setVerticalScrollbarValue;
        bindTextArea["getVerticalScrollbarValue"] = &tgui::TextArea::getVerticalScrollbarValue;
        bindTextArea["setHorizontalScrollbarValue"] = &tgui::TextArea::setHorizontalScrollbarValue;
        bindTextArea["getHorizontalScrollbarValue"] = &tgui::TextArea::getHorizontalScrollbarValue;
        bindTextArea["isMouseOnWidget"] = &tgui::TextArea::isMouseOnWidget;
        bindTextArea["leftMousePressed"] = &tgui::TextArea::leftMousePressed;
        bindTextArea["leftMouseReleased"] = &tgui::TextArea::leftMouseReleased;
        bindTextArea["mouseMoved"] = &tgui::TextArea::mouseMoved;
        bindTextArea["keyPressed"] = &tgui::TextArea::keyPressed;
        bindTextArea["textEntered"] = &tgui::TextArea::textEntered;
        bindTextArea["mouseWheelScrolled"] = &tgui::TextArea::mouseWheelScrolled;
        bindTextArea["mouseNoLongerOnWidget"] = &tgui::TextArea::mouseNoLongerOnWidget;
        bindTextArea["leftMouseButtonNoLongerDown"] = &tgui::TextArea::leftMouseButtonNoLongerDown;
        bindTextArea["create"] = &tgui::TextArea::create;
        bindTextArea["copy"] = &tgui::TextArea::copy;
        bindTextArea["onTextChange"] = &tgui::TextArea::onTextChange;
        bindTextArea["onSelectionChange"] = &tgui::TextArea::onSelectionChange;
    }
};