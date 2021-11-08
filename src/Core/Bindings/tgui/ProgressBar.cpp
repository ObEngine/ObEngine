#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/ProgressBar.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassProgressBar(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ProgressBar> bindProgressBar
            = tguiNamespace.new_usertype<tgui::ProgressBar>("ProgressBar", sol::call_constructor,
                sol::constructors<tgui::ProgressBar(), tgui::ProgressBar(const char*),
                    tgui::ProgressBar(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindProgressBar["getSharedRenderer"]
            = sol::overload(static_cast<tgui::ProgressBarRenderer* (tgui::ProgressBar::*)()>(
                                &tgui::ProgressBar::getSharedRenderer),
                static_cast<const tgui::ProgressBarRenderer* (tgui::ProgressBar::*)() const>(
                    &tgui::ProgressBar::getSharedRenderer));
        bindProgressBar["getRenderer"]
            = sol::overload(static_cast<tgui::ProgressBarRenderer* (tgui::ProgressBar::*)()>(
                                &tgui::ProgressBar::getRenderer),
                static_cast<const tgui::ProgressBarRenderer* (tgui::ProgressBar::*)() const>(
                    &tgui::ProgressBar::getRenderer));
        bindProgressBar["setSize"]
            = sol::overload(static_cast<void (tgui::ProgressBar::*)(const tgui::Layout2d&)>(
                                &tgui::ProgressBar::setSize),
                static_cast<void (tgui::ProgressBar::*)(const tgui::Layout2d&)>(
                    &tgui::ProgressBar::setSize),
                static_cast<void (tgui::ProgressBar::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::ProgressBar::setSize));
        bindProgressBar["setMinimum"] = &tgui::ProgressBar::setMinimum;
        bindProgressBar["getMinimum"] = &tgui::ProgressBar::getMinimum;
        bindProgressBar["setMaximum"] = &tgui::ProgressBar::setMaximum;
        bindProgressBar["getMaximum"] = &tgui::ProgressBar::getMaximum;
        bindProgressBar["setValue"] = &tgui::ProgressBar::setValue;
        bindProgressBar["getValue"] = &tgui::ProgressBar::getValue;
        bindProgressBar["incrementValue"] = &tgui::ProgressBar::incrementValue;
        bindProgressBar["setText"] = &tgui::ProgressBar::setText;
        bindProgressBar["getText"] = &tgui::ProgressBar::getText;
        bindProgressBar["setTextSize"] = &tgui::ProgressBar::setTextSize;
        bindProgressBar["getTextSize"] = &tgui::ProgressBar::getTextSize;
        bindProgressBar["setFillDirection"] = &tgui::ProgressBar::setFillDirection;
        bindProgressBar["getFillDirection"] = &tgui::ProgressBar::getFillDirection;
        bindProgressBar["isMouseOnWidget"] = &tgui::ProgressBar::isMouseOnWidget;
        bindProgressBar["draw"] = &tgui::ProgressBar::draw;
        bindProgressBar["create"] = &tgui::ProgressBar::create;
        bindProgressBar["copy"] = &tgui::ProgressBar::copy;
        bindProgressBar["onValueChange"] = &tgui::ProgressBar::onValueChange;
        bindProgressBar["onFull"] = &tgui::ProgressBar::onFull;
    }
};