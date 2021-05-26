#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/Scrollbar.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassScrollbarChildWidget(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ScrollbarChildWidget> bindScrollbarChildWidget
            = tguiNamespace.new_usertype<tgui::ScrollbarChildWidget>(
                "ScrollbarChildWidget", sol::call_constructor, sol::default_constructor,
                sol::base_classes, sol::bases<tgui::Scrollbar, tgui::Widget>());
        bindScrollbarChildWidget["isMouseDownOnThumb"]
            = &tgui::ScrollbarChildWidget::isMouseDownOnThumb;
        bindScrollbarChildWidget["isShown"] = &tgui::ScrollbarChildWidget::isShown;
        bindScrollbarChildWidget["draw"] =

            [](tgui::ScrollbarChildWidget* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
    }
};