#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/VerticalLayout.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassVerticalLayout(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::VerticalLayout> bindVerticalLayout
            = tguiNamespace.new_usertype<tgui::VerticalLayout>("VerticalLayout",
                sol::call_constructor,
                sol::constructors<tgui::VerticalLayout(),
                    tgui::VerticalLayout(const char*),
                    tgui::VerticalLayout(const char*, bool)>(),
                sol::base_classes,
                sol::bases<tgui::BoxLayoutRatios, tgui::BoxLayout, tgui::Group,
                    tgui::Container, tgui::Widget>());
        bindVerticalLayout["create"] = sol::overload(
            [](tgui::VerticalLayout* self) -> tgui::VerticalLayout::Ptr {
                return self->create();
            },
            [](tgui::VerticalLayout* self, const tgui::Layout2d& size)
                -> tgui::VerticalLayout::Ptr { return self->create(size); });
        bindVerticalLayout["copy"] = &tgui::VerticalLayout::copy;
    }
};