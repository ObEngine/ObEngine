#pragma once

namespace sol
{
    class state_view;
};
namespace tgui::keyboard::Bindings
{
    void LoadFunctionIsShiftPressed(sol::state_view state);
    void LoadFunctionOpenVirtualKeyboard(sol::state_view state);
    void LoadFunctionCloseVirtualKeyboard(sol::state_view state);
    void LoadFunctionIsMultiselectModifierPressed(sol::state_view state);
    void LoadFunctionIsKeyPressCopy(sol::state_view state);
    void LoadFunctionIsKeyPressCut(sol::state_view state);
    void LoadFunctionIsKeyPressPaste(sol::state_view state);
    void LoadFunctionIsKeyPressSelectAll(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretLeft(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretRight(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretWordBegin(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretWordEnd(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretUp(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretDown(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretLineStart(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretLineEnd(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretDocumentBegin(sol::state_view state);
    void LoadFunctionIsKeyPressMoveCaretDocumentEnd(sol::state_view state);
};