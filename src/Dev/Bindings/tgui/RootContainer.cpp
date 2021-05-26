#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Container.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassRootContainer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::RootContainer> bindRootContainer
            = tguiNamespace.new_usertype<tgui::RootContainer>("RootContainer",
                sol::call_constructor,
                sol::constructors<tgui::RootContainer(), tgui::RootContainer(const char*),
                    tgui::RootContainer(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Container, tgui::Widget>());
        bindRootContainer["setSize"] = sol::overload(
            static_cast<void (tgui::RootContainer::*)(const tgui::Layout2d&)>(
                &tgui::RootContainer::setSize),
            static_cast<void (tgui::RootContainer::*)(const tgui::Layout2d&)>(
                &tgui::RootContainer::setSize),
            static_cast<void (tgui::RootContainer::*)(tgui::Layout, tgui::Layout)>(
                &tgui::RootContainer::setSize));
        bindRootContainer["setFocused"] = &tgui::RootContainer::setFocused;
        bindRootContainer["isMouseOnWidget"] = &tgui::RootContainer::isMouseOnWidget;
        bindRootContainer["draw"] =

            [](tgui::RootContainer* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
    }
};