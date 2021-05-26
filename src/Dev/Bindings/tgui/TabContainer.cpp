#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/TabContainer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTabContainer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::TabContainer> bindTabContainer
            = tguiNamespace.new_usertype<tgui::TabContainer>("TabContainer",
                sol::call_constructor,
                sol::constructors<tgui::TabContainer(), tgui::TabContainer(const char*),
                    tgui::TabContainer(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::SubwidgetContainer, tgui::Widget>());
        bindTabContainer["getTabsSharedRenderer"]
            = sol::overload(static_cast<tgui::TabsRenderer* (tgui::TabContainer::*)()>(
                                &tgui::TabContainer::getTabsSharedRenderer),
                static_cast<const tgui::TabsRenderer* (tgui::TabContainer::*)() const>(
                    &tgui::TabContainer::getTabsSharedRenderer));
        bindTabContainer["getTabsRenderer"]
            = sol::overload(static_cast<tgui::TabsRenderer* (tgui::TabContainer::*)()>(
                                &tgui::TabContainer::getTabsRenderer),
                static_cast<const tgui::TabsRenderer* (tgui::TabContainer::*)() const>(
                    &tgui::TabContainer::getTabsRenderer));
        bindTabContainer["setSize"] = sol::overload(
            static_cast<void (tgui::TabContainer::*)(const tgui::Layout2d&)>(
                &tgui::TabContainer::setSize),
            static_cast<void (tgui::TabContainer::*)(const tgui::Layout2d&)>(
                &tgui::TabContainer::setSize),
            static_cast<void (tgui::TabContainer::*)(const tgui::Layout2d&)>(
                &tgui::TabContainer::setSize),
            static_cast<void (tgui::TabContainer::*)(tgui::Layout, tgui::Layout)>(
                &tgui::TabContainer::setSize));
        bindTabContainer["setTabsHeight"] = &tgui::TabContainer::setTabsHeight;
        bindTabContainer["addPanel"] = sol::overload(
            [](tgui::TabContainer* self, tgui::Panel::Ptr ptr,
                const tgui::String& name) -> void { return self->addPanel(ptr, name); },
            [](tgui::TabContainer* self, tgui::Panel::Ptr ptr, const tgui::String& name,
                bool select) -> void { return self->addPanel(ptr, name, select); });
        bindTabContainer["insertPanel"] = sol::overload(
            [](tgui::TabContainer* self, tgui::Panel::Ptr ptr, const tgui::String& name,
                std::size_t index) -> bool {
                return self->insertPanel(ptr, name, index);
            },
            [](tgui::TabContainer* self, tgui::Panel::Ptr ptr, const tgui::String& name,
                std::size_t index, bool select) -> bool {
                return self->insertPanel(ptr, name, index, select);
            });
        bindTabContainer["removePanel"] = &tgui::TabContainer::removePanel;
        bindTabContainer["select"] = sol::overload(
            [](tgui::TabContainer* self, std::size_t index) -> void {
                return self->select(index);
            },
            [](tgui::TabContainer* self, std::size_t index, bool genEvents) -> void {
                return self->select(index, genEvents);
            });
        bindTabContainer["getPanelCount"] = &tgui::TabContainer::getPanelCount;
        bindTabContainer["getIndex"] = &tgui::TabContainer::getIndex;
        bindTabContainer["getSelected"] = &tgui::TabContainer::getSelected;
        bindTabContainer["getSelectedIndex"] = &tgui::TabContainer::getSelectedIndex;
        bindTabContainer["getPanel"] = &tgui::TabContainer::getPanel;
        bindTabContainer["getTabs"] = &tgui::TabContainer::getTabs;
        bindTabContainer["getTabText"] = &tgui::TabContainer::getTabText;
        bindTabContainer["changeTabText"] = &tgui::TabContainer::changeTabText;
        bindTabContainer["create"] = sol::overload(
            [](tgui::TabContainer* self) -> tgui::TabContainer::Ptr {
                return self->create();
            },
            [](tgui::TabContainer* self, const tgui::Layout2d& size)
                -> tgui::TabContainer::Ptr { return self->create(size); });
        bindTabContainer["copy"] = &tgui::TabContainer::copy;
        bindTabContainer["onSelectionChanged"] = &tgui::TabContainer::onSelectionChanged;
        bindTabContainer["onSelectionChanging"]
            = &tgui::TabContainer::onSelectionChanging;
    }
};