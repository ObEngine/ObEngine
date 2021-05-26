#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/ClickableWidget.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassClickableWidget(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::ClickableWidget> bindClickableWidget
            = tguiNamespace.new_usertype<tgui::ClickableWidget>("ClickableWidget",
                sol::call_constructor,
                sol::constructors<tgui::ClickableWidget(),
                    tgui::ClickableWidget(const char*),
                    tgui::ClickableWidget(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindClickableWidget["isMouseOnWidget"] = &tgui::ClickableWidget::isMouseOnWidget;
        bindClickableWidget["leftMousePressed"]
            = &tgui::ClickableWidget::leftMousePressed;
        bindClickableWidget["leftMouseReleased"]
            = &tgui::ClickableWidget::leftMouseReleased;
        bindClickableWidget["rightMousePressed"]
            = &tgui::ClickableWidget::rightMousePressed;
        bindClickableWidget["rightMouseReleased"]
            = &tgui::ClickableWidget::rightMouseReleased;
        bindClickableWidget["rightMouseButtonNoLongerDown"]
            = &tgui::ClickableWidget::rightMouseButtonNoLongerDown;
        bindClickableWidget["draw"] =

            [](tgui::ClickableWidget* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindClickableWidget["create"] = sol::overload(
            [](tgui::ClickableWidget* self) -> tgui::ClickableWidget::Ptr {
                return self->create();
            },
            [](tgui::ClickableWidget* self, tgui::Layout2d size)
                -> tgui::ClickableWidget::Ptr { return self->create(size); });
        bindClickableWidget["copy"] = &tgui::ClickableWidget::copy;
        bindClickableWidget["onMousePress"] = &tgui::ClickableWidget::onMousePress;
        bindClickableWidget["onMouseRelease"] = &tgui::ClickableWidget::onMouseRelease;
        bindClickableWidget["onClick"] = &tgui::ClickableWidget::onClick;
        bindClickableWidget["onRightMousePress"]
            = &tgui::ClickableWidget::onRightMousePress;
        bindClickableWidget["onRightMouseRelease"]
            = &tgui::ClickableWidget::onRightMouseRelease;
        bindClickableWidget["onRightClick"] = &tgui::ClickableWidget::onRightClick;
    }
};