#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/SeparatorLine.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSeparatorLine(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SeparatorLine> bindSeparatorLine
            = tguiNamespace.new_usertype<tgui::SeparatorLine>("SeparatorLine",
                sol::call_constructor,
                sol::constructors<tgui::SeparatorLine(), tgui::SeparatorLine(const char*),
                    tgui::SeparatorLine(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::ClickableWidget, tgui::Widget>());
        bindSeparatorLine["getSharedRenderer"]
            = sol::overload(static_cast<tgui::SeparatorLineRenderer* (tgui::SeparatorLine::*)()>(
                                &tgui::SeparatorLine::getSharedRenderer),
                static_cast<const tgui::SeparatorLineRenderer* (tgui::SeparatorLine::*)() const>(
                    &tgui::SeparatorLine::getSharedRenderer));
        bindSeparatorLine["getRenderer"]
            = sol::overload(static_cast<tgui::SeparatorLineRenderer* (tgui::SeparatorLine::*)()>(
                                &tgui::SeparatorLine::getRenderer),
                static_cast<const tgui::SeparatorLineRenderer* (tgui::SeparatorLine::*)() const>(
                    &tgui::SeparatorLine::getRenderer));
        bindSeparatorLine["draw"] = &tgui::SeparatorLine::draw;
        bindSeparatorLine["create"] = sol::overload(
            []() -> tgui::SeparatorLine::Ptr { return tgui::SeparatorLine::create(); },
            [](tgui::Layout2d size) -> tgui::SeparatorLine::Ptr {
                return tgui::SeparatorLine::create(size);
            });
        bindSeparatorLine["copy"] = &tgui::SeparatorLine::copy;
    }
};