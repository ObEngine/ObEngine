#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/Group.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassGroup(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Group> bindGroup
            = tguiNamespace.new_usertype<tgui::Group>("Group", sol::call_constructor,
                sol::constructors<tgui::Group(), tgui::Group(const char*),
                    tgui::Group(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Container, tgui::Widget>());
        bindGroup["getSharedRenderer"]
            = sol::overload(static_cast<tgui::GroupRenderer* (tgui::Group::*)()>(
                                &tgui::Group::getSharedRenderer),
                static_cast<const tgui::GroupRenderer* (tgui::Group::*)() const>(
                    &tgui::Group::getSharedRenderer));
        bindGroup["getRenderer"]
            = sol::overload(static_cast<tgui::GroupRenderer* (tgui::Group::*)()>(
                                &tgui::Group::getRenderer),
                static_cast<const tgui::GroupRenderer* (tgui::Group::*)() const>(
                    &tgui::Group::getRenderer));
        bindGroup["setSize"]
            = sol::overload(static_cast<void (tgui::Group::*)(const tgui::Layout2d&)>(
                                &tgui::Group::setSize),
                static_cast<void (tgui::Group::*)(const tgui::Layout2d&)>(
                    &tgui::Group::setSize),
                static_cast<void (tgui::Group::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::Group::setSize));
        bindGroup["getInnerSize"] = &tgui::Group::getInnerSize;
        bindGroup["getChildWidgetsOffset"] = &tgui::Group::getChildWidgetsOffset;
        bindGroup["isMouseOnWidget"] = &tgui::Group::isMouseOnWidget;
        bindGroup["draw"] =

            [](tgui::Group* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindGroup["create"] = sol::overload(
            [](tgui::Group* self) -> tgui::Group::Ptr { return self->create(); },
            [](tgui::Group* self, const tgui::Layout2d& size) -> tgui::Group::Ptr {
                return self->create(size);
            });
        bindGroup["copy"] = &tgui::Group::copy;
    }
};