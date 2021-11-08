#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/CustomWidgetForBindings.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassCustomWidgetForBindings(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::CustomWidgetForBindings> bindCustomWidgetForBindings
            = tguiNamespace.new_usertype<tgui::CustomWidgetForBindings>("CustomWidgetForBindings",
                sol::call_constructor,
                sol::constructors<tgui::CustomWidgetForBindings(),
                    tgui::CustomWidgetForBindings(const char*),
                    tgui::CustomWidgetForBindings(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindCustomWidgetForBindings["setPosition"] = &tgui::CustomWidgetForBindings::setPosition;
        bindCustomWidgetForBindings["setSize"] = &tgui::CustomWidgetForBindings::setSize;
        bindCustomWidgetForBindings["getFullSize"] = &tgui::CustomWidgetForBindings::getFullSize;
        bindCustomWidgetForBindings["getAbsolutePosition"]
            = &tgui::CustomWidgetForBindings::getAbsolutePosition;
        bindCustomWidgetForBindings["getWidgetOffset"]
            = &tgui::CustomWidgetForBindings::getWidgetOffset;
        bindCustomWidgetForBindings["setVisible"] = &tgui::CustomWidgetForBindings::setVisible;
        bindCustomWidgetForBindings["setEnabled"] = &tgui::CustomWidgetForBindings::setEnabled;
        bindCustomWidgetForBindings["setFocused"] = &tgui::CustomWidgetForBindings::setFocused;
        bindCustomWidgetForBindings["canGainFocus"] = &tgui::CustomWidgetForBindings::canGainFocus;
        bindCustomWidgetForBindings["updateTime"] = &tgui::CustomWidgetForBindings::updateTime;
        bindCustomWidgetForBindings["isMouseOnWidget"]
            = &tgui::CustomWidgetForBindings::isMouseOnWidget;
        bindCustomWidgetForBindings["leftMousePressed"]
            = &tgui::CustomWidgetForBindings::leftMousePressed;
        bindCustomWidgetForBindings["leftMouseReleased"]
            = &tgui::CustomWidgetForBindings::leftMouseReleased;
        bindCustomWidgetForBindings["rightMousePressed"]
            = &tgui::CustomWidgetForBindings::rightMousePressed;
        bindCustomWidgetForBindings["rightMouseReleased"]
            = &tgui::CustomWidgetForBindings::rightMouseReleased;
        bindCustomWidgetForBindings["mouseMoved"] = &tgui::CustomWidgetForBindings::mouseMoved;
        bindCustomWidgetForBindings["keyPressed"] = &tgui::CustomWidgetForBindings::keyPressed;
        bindCustomWidgetForBindings["textEntered"] = &tgui::CustomWidgetForBindings::textEntered;
        bindCustomWidgetForBindings["mouseWheelScrolled"]
            = &tgui::CustomWidgetForBindings::mouseWheelScrolled;
        bindCustomWidgetForBindings["mouseNoLongerOnWidget"]
            = &tgui::CustomWidgetForBindings::mouseNoLongerOnWidget;
        bindCustomWidgetForBindings["leftMouseButtonNoLongerDown"]
            = &tgui::CustomWidgetForBindings::leftMouseButtonNoLongerDown;
        bindCustomWidgetForBindings["draw"] = &tgui::CustomWidgetForBindings::draw;
        bindCustomWidgetForBindings["clone"] = &tgui::CustomWidgetForBindings::clone;
        bindCustomWidgetForBindings["create"] = &tgui::CustomWidgetForBindings::create;
        bindCustomWidgetForBindings["implPositionChanged"]
            = &tgui::CustomWidgetForBindings::implPositionChanged;
        bindCustomWidgetForBindings["implSizeChanged"]
            = &tgui::CustomWidgetForBindings::implSizeChanged;
        bindCustomWidgetForBindings["implVisibleChanged"]
            = &tgui::CustomWidgetForBindings::implVisibleChanged;
        bindCustomWidgetForBindings["implEnableChanged"]
            = &tgui::CustomWidgetForBindings::implEnableChanged;
        bindCustomWidgetForBindings["implFocusChanged"]
            = &tgui::CustomWidgetForBindings::implFocusChanged;
        bindCustomWidgetForBindings["implCanGainFocus"]
            = &tgui::CustomWidgetForBindings::implCanGainFocus;
        bindCustomWidgetForBindings["implGetFullSize"]
            = &tgui::CustomWidgetForBindings::implGetFullSize;
        bindCustomWidgetForBindings["implGetAbsolutePosition"]
            = &tgui::CustomWidgetForBindings::implGetAbsolutePosition;
        bindCustomWidgetForBindings["implGetWidgetOffset"]
            = &tgui::CustomWidgetForBindings::implGetWidgetOffset;
        bindCustomWidgetForBindings["implUpdateTimeFunction"]
            = &tgui::CustomWidgetForBindings::implUpdateTimeFunction;
        bindCustomWidgetForBindings["implMouseOnWidget"]
            = &tgui::CustomWidgetForBindings::implMouseOnWidget;
        bindCustomWidgetForBindings["implLeftMousePressed"]
            = &tgui::CustomWidgetForBindings::implLeftMousePressed;
        bindCustomWidgetForBindings["implLeftMouseReleased"]
            = &tgui::CustomWidgetForBindings::implLeftMouseReleased;
        bindCustomWidgetForBindings["implRightMousePressed"]
            = &tgui::CustomWidgetForBindings::implRightMousePressed;
        bindCustomWidgetForBindings["implRightMouseReleased"]
            = &tgui::CustomWidgetForBindings::implRightMouseReleased;
        bindCustomWidgetForBindings["implMouseMoved"]
            = &tgui::CustomWidgetForBindings::implMouseMoved;
        bindCustomWidgetForBindings["implKeyPressed"]
            = &tgui::CustomWidgetForBindings::implKeyPressed;
        bindCustomWidgetForBindings["implTextEntered"]
            = &tgui::CustomWidgetForBindings::implTextEntered;
        bindCustomWidgetForBindings["implMouseWheelScrolled"]
            = &tgui::CustomWidgetForBindings::implMouseWheelScrolled;
        bindCustomWidgetForBindings["implMouseNoLongerOnWidget"]
            = &tgui::CustomWidgetForBindings::implMouseNoLongerOnWidget;
        bindCustomWidgetForBindings["implLeftMouseButtonNoLongerDown"]
            = &tgui::CustomWidgetForBindings::implLeftMouseButtonNoLongerDown;
        bindCustomWidgetForBindings["implMouseEnteredWidget"]
            = &tgui::CustomWidgetForBindings::implMouseEnteredWidget;
        bindCustomWidgetForBindings["implMouseLeftWidget"]
            = &tgui::CustomWidgetForBindings::implMouseLeftWidget;
        bindCustomWidgetForBindings["implRendererChanged"]
            = &tgui::CustomWidgetForBindings::implRendererChanged;
        bindCustomWidgetForBindings["implDrawFunction"]
            = &tgui::CustomWidgetForBindings::implDrawFunction;
    }
};