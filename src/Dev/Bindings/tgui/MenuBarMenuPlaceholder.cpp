#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/MenuBar.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassMenuBarMenuPlaceholder(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MenuBarMenuPlaceholder> bindMenuBarMenuPlaceholder
            = tguiNamespace.new_usertype<tgui::MenuBarMenuPlaceholder>(
                "MenuBarMenuPlaceholder", sol::call_constructor,
                sol::constructors<tgui::MenuBarMenuPlaceholder(tgui::MenuBar*)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindMenuBarMenuPlaceholder["getFullSize"]
            = &tgui::MenuBarMenuPlaceholder::getFullSize;
        bindMenuBarMenuPlaceholder["getWidgetOffset"]
            = &tgui::MenuBarMenuPlaceholder::getWidgetOffset;
        bindMenuBarMenuPlaceholder["isMouseOnWidget"]
            = &tgui::MenuBarMenuPlaceholder::isMouseOnWidget;
        bindMenuBarMenuPlaceholder["draw"] =

            [](tgui::MenuBarMenuPlaceholder* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindMenuBarMenuPlaceholder["leftMouseButtonNoLongerDown"]
            = &tgui::MenuBarMenuPlaceholder::leftMouseButtonNoLongerDown;
        bindMenuBarMenuPlaceholder["mouseMoved"]
            = &tgui::MenuBarMenuPlaceholder::mouseMoved;
        bindMenuBarMenuPlaceholder["clone"] = &tgui::MenuBarMenuPlaceholder::clone;
    }
};