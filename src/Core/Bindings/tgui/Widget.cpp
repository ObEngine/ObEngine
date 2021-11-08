#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widget.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassWidget(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Widget> bindWidget = tguiNamespace.new_usertype<tgui::Widget>("Widget");
        bindWidget["operator="]
            = sol::overload(static_cast<tgui::Widget& (tgui::Widget::*)(const tgui::Widget&)>(
                                &tgui::Widget::operator=),
                static_cast<tgui::Widget& (tgui::Widget::*)(tgui::Widget &&)>(
                    &tgui::Widget::operator=));
        bindWidget["setRenderer"] = &tgui::Widget::setRenderer;
        bindWidget["getSharedRenderer"]
            = sol::overload(static_cast<tgui::WidgetRenderer* (tgui::Widget::*)()>(
                                &tgui::Widget::getSharedRenderer),
                static_cast<const tgui::WidgetRenderer* (tgui::Widget::*)() const>(
                    &tgui::Widget::getSharedRenderer));
        bindWidget["getRenderer"] = sol::overload(
            static_cast<tgui::WidgetRenderer* (tgui::Widget::*)()>(&tgui::Widget::getRenderer),
            static_cast<const tgui::WidgetRenderer* (tgui::Widget::*)() const>(
                &tgui::Widget::getRenderer));
        bindWidget["setPosition"] = sol::overload(
            static_cast<void (tgui::Widget::*)(const tgui::Layout2d&)>(&tgui::Widget::setPosition),
            static_cast<void (tgui::Widget::*)(tgui::Layout, tgui::Layout)>(
                &tgui::Widget::setPosition));
        bindWidget["getPosition"] = &tgui::Widget::getPosition;
        bindWidget["setSize"] = sol::overload(
            static_cast<void (tgui::Widget::*)(const tgui::Layout2d&)>(&tgui::Widget::setSize),
            static_cast<void (tgui::Widget::*)(tgui::Layout, tgui::Layout)>(
                &tgui::Widget::setSize));
        bindWidget["setWidth"] = &tgui::Widget::setWidth;
        bindWidget["setHeight"] = &tgui::Widget::setHeight;
        bindWidget["getSize"] = &tgui::Widget::getSize;
        bindWidget["getFullSize"] = &tgui::Widget::getFullSize;
        bindWidget["getAbsolutePosition"] = &tgui::Widget::getAbsolutePosition;
        bindWidget["getWidgetOffset"] = &tgui::Widget::getWidgetOffset;
        bindWidget["setOrigin"] = sol::overload(
            static_cast<void (tgui::Widget::*)(float, float)>(&tgui::Widget::setOrigin),
            static_cast<void (tgui::Widget::*)(tgui::Vector2f)>(&tgui::Widget::setOrigin));
        bindWidget["getOrigin"] = &tgui::Widget::getOrigin;
        bindWidget["setScale"] = sol::overload(
            static_cast<void (tgui::Widget::*)(tgui::Vector2f)>(&tgui::Widget::setScale),
            static_cast<void (tgui::Widget::*)(tgui::Vector2f, tgui::Vector2f)>(
                &tgui::Widget::setScale),
            static_cast<void (tgui::Widget::*)(float)>(&tgui::Widget::setScale),
            static_cast<void (tgui::Widget::*)(float, tgui::Vector2f)>(&tgui::Widget::setScale));
        bindWidget["getScale"] = &tgui::Widget::getScale;
        bindWidget["getScaleOrigin"] = &tgui::Widget::getScaleOrigin;
        bindWidget["setRotation"] = sol::overload(
            static_cast<void (tgui::Widget::*)(float)>(&tgui::Widget::setRotation),
            static_cast<void (tgui::Widget::*)(float, tgui::Vector2f)>(&tgui::Widget::setRotation));
        bindWidget["getRotation"] = &tgui::Widget::getRotation;
        bindWidget["getRotationOrigin"] = &tgui::Widget::getRotationOrigin;
        bindWidget["showWithEffect"] = &tgui::Widget::showWithEffect;
        bindWidget["hideWithEffect"] = &tgui::Widget::hideWithEffect;
        bindWidget["setVisible"] = &tgui::Widget::setVisible;
        bindWidget["isVisible"] = &tgui::Widget::isVisible;
        bindWidget["setEnabled"] = &tgui::Widget::setEnabled;
        bindWidget["isEnabled"] = &tgui::Widget::isEnabled;
        bindWidget["setFocused"] = &tgui::Widget::setFocused;
        bindWidget["isFocused"] = &tgui::Widget::isFocused;
        bindWidget["getWidgetType"] = &tgui::Widget::getWidgetType;
        bindWidget["getParent"] = &tgui::Widget::getParent;
        bindWidget["getParentGui"] = &tgui::Widget::getParentGui;
        bindWidget["isAnimationPlaying"] = &tgui::Widget::isAnimationPlaying;
        bindWidget["moveToFront"] = &tgui::Widget::moveToFront;
        bindWidget["moveToBack"] = &tgui::Widget::moveToBack;
        bindWidget["setUserData"] = &tgui::Widget::setUserData;
        bindWidget["setInheritedFont"] = &tgui::Widget::setInheritedFont;
        bindWidget["getInheritedFont"] = &tgui::Widget::getInheritedFont;
        bindWidget["setInheritedOpacity"] = &tgui::Widget::setInheritedOpacity;
        bindWidget["getInheritedOpacity"] = &tgui::Widget::getInheritedOpacity;
        bindWidget["setTextSize"] = &tgui::Widget::setTextSize;
        bindWidget["getTextSize"] = &tgui::Widget::getTextSize;
        bindWidget["setToolTip"] = &tgui::Widget::setToolTip;
        bindWidget["getToolTip"] = &tgui::Widget::getToolTip;
        bindWidget["setWidgetName"] = &tgui::Widget::setWidgetName;
        bindWidget["getWidgetName"] = &tgui::Widget::getWidgetName;
        bindWidget["setMouseCursor"] = &tgui::Widget::setMouseCursor;
        bindWidget["getMouseCursor"] = &tgui::Widget::getMouseCursor;
        bindWidget["setFocusable"] = &tgui::Widget::setFocusable;
        bindWidget["isFocusable"] = &tgui::Widget::isFocusable;
        bindWidget["canGainFocus"] = &tgui::Widget::canGainFocus;
        bindWidget["isContainer"] = &tgui::Widget::isContainer;
        bindWidget["isDraggableWidget"] = &tgui::Widget::isDraggableWidget;
        bindWidget["isMouseDown"] = &tgui::Widget::isMouseDown;
        bindWidget["getSignal"] = &tgui::Widget::getSignal;
        bindWidget["setParent"] = &tgui::Widget::setParent;
        bindWidget["updateTime"] = &tgui::Widget::updateTime;
        bindWidget["isMouseOnWidget"] = &tgui::Widget::isMouseOnWidget;
        bindWidget["leftMousePressed"] = &tgui::Widget::leftMousePressed;
        bindWidget["leftMouseReleased"] = &tgui::Widget::leftMouseReleased;
        bindWidget["rightMousePressed"] = &tgui::Widget::rightMousePressed;
        bindWidget["rightMouseReleased"] = &tgui::Widget::rightMouseReleased;
        bindWidget["mousePressed"] = &tgui::Widget::mousePressed;
        bindWidget["mouseReleased"] = &tgui::Widget::mouseReleased;
        bindWidget["mouseMoved"] = &tgui::Widget::mouseMoved;
        bindWidget["keyPressed"] = &tgui::Widget::keyPressed;
        bindWidget["textEntered"] = &tgui::Widget::textEntered;
        bindWidget["mouseWheelScrolled"] = &tgui::Widget::mouseWheelScrolled;
        bindWidget["mouseNoLongerOnWidget"] = &tgui::Widget::mouseNoLongerOnWidget;
        bindWidget["leftMouseButtonNoLongerDown"] = &tgui::Widget::leftMouseButtonNoLongerDown;
        bindWidget["rightMouseButtonNoLongerDown"] = &tgui::Widget::rightMouseButtonNoLongerDown;
        bindWidget["askToolTip"] = &tgui::Widget::askToolTip;
        bindWidget["getPositionLayout"] = &tgui::Widget::getPositionLayout;
        bindWidget["getSizeLayout"] = &tgui::Widget::getSizeLayout;
        bindWidget["bindPositionLayout"] = &tgui::Widget::bindPositionLayout;
        bindWidget["unbindPositionLayout"] = &tgui::Widget::unbindPositionLayout;
        bindWidget["bindSizeLayout"] = &tgui::Widget::bindSizeLayout;
        bindWidget["unbindSizeLayout"] = &tgui::Widget::unbindSizeLayout;
        bindWidget["draw"] = &tgui::Widget::draw;
        bindWidget["onPositionChange"] = &tgui::Widget::onPositionChange;
        bindWidget["onSizeChange"] = &tgui::Widget::onSizeChange;
        bindWidget["onFocus"] = &tgui::Widget::onFocus;
        bindWidget["onUnfocus"] = &tgui::Widget::onUnfocus;
        bindWidget["onMouseEnter"] = &tgui::Widget::onMouseEnter;
        bindWidget["onMouseLeave"] = &tgui::Widget::onMouseLeave;
        bindWidget["onAnimationFinish"] = &tgui::Widget::onAnimationFinish;
    }
};