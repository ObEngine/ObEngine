#include <Bindings/tgui/keyboard/keyboard.hpp>

#include <TGUI/Keyboard.hpp>

#include <Bindings/Config.hpp>

namespace tgui::keyboard::Bindings
{
    void LoadFunctionIsShiftPressed(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function("isShiftPressed", tgui::keyboard::isShiftPressed);
    }
    void LoadFunctionOpenVirtualKeyboard(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "openVirtualKeyboard", tgui::keyboard::openVirtualKeyboard);
    }
    void LoadFunctionCloseVirtualKeyboard(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "closeVirtualKeyboard", tgui::keyboard::closeVirtualKeyboard);
    }
    void LoadFunctionIsMultiselectModifierPressed(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isMultiselectModifierPressed", tgui::keyboard::isMultiselectModifierPressed);
    }
    void LoadFunctionIsKeyPressCopy(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function("isKeyPressCopy", tgui::keyboard::isKeyPressCopy);
    }
    void LoadFunctionIsKeyPressCut(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function("isKeyPressCut", tgui::keyboard::isKeyPressCut);
    }
    void LoadFunctionIsKeyPressPaste(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressPaste", tgui::keyboard::isKeyPressPaste);
    }
    void LoadFunctionIsKeyPressSelectAll(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressSelectAll", tgui::keyboard::isKeyPressSelectAll);
    }
    void LoadFunctionIsKeyPressMoveCaretLeft(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressMoveCaretLeft", tgui::keyboard::isKeyPressMoveCaretLeft);
    }
    void LoadFunctionIsKeyPressMoveCaretRight(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressMoveCaretRight", tgui::keyboard::isKeyPressMoveCaretRight);
    }
    void LoadFunctionIsKeyPressMoveCaretWordBegin(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressMoveCaretWordBegin", tgui::keyboard::isKeyPressMoveCaretWordBegin);
    }
    void LoadFunctionIsKeyPressMoveCaretWordEnd(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressMoveCaretWordEnd", tgui::keyboard::isKeyPressMoveCaretWordEnd);
    }
    void LoadFunctionIsKeyPressMoveCaretUp(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressMoveCaretUp", tgui::keyboard::isKeyPressMoveCaretUp);
    }
    void LoadFunctionIsKeyPressMoveCaretDown(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressMoveCaretDown", tgui::keyboard::isKeyPressMoveCaretDown);
    }
    void LoadFunctionIsKeyPressMoveCaretLineStart(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressMoveCaretLineStart", tgui::keyboard::isKeyPressMoveCaretLineStart);
    }
    void LoadFunctionIsKeyPressMoveCaretLineEnd(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function(
            "isKeyPressMoveCaretLineEnd", tgui::keyboard::isKeyPressMoveCaretLineEnd);
    }
    void LoadFunctionIsKeyPressMoveCaretDocumentBegin(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function("isKeyPressMoveCaretDocumentBegin",
            tgui::keyboard::isKeyPressMoveCaretDocumentBegin);
    }
    void LoadFunctionIsKeyPressMoveCaretDocumentEnd(sol::state_view state)
    {
        sol::table keyboardNamespace = state["tgui"]["keyboard"].get<sol::table>();
        keyboardNamespace.set_function("isKeyPressMoveCaretDocumentEnd",
            tgui::keyboard::isKeyPressMoveCaretDocumentEnd);
    }
};