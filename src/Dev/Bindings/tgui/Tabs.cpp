#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Widgets/Tabs.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTabs(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Tabs> bindTabs
            = tguiNamespace.new_usertype<tgui::Tabs>("Tabs", sol::call_constructor,
                sol::constructors<tgui::Tabs(), tgui::Tabs(const char*),
                    tgui::Tabs(const char*, bool)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindTabs["getSharedRenderer"]
            = sol::overload(static_cast<tgui::TabsRenderer* (tgui::Tabs::*)()>(
                                &tgui::Tabs::getSharedRenderer),
                static_cast<const tgui::TabsRenderer* (tgui::Tabs::*)() const>(
                    &tgui::Tabs::getSharedRenderer));
        bindTabs["getRenderer"] = sol::overload(
            static_cast<tgui::TabsRenderer* (tgui::Tabs::*)()>(&tgui::Tabs::getRenderer),
            static_cast<const tgui::TabsRenderer* (tgui::Tabs::*)() const>(
                &tgui::Tabs::getRenderer));
        bindTabs["setSize"]
            = sol::overload(static_cast<void (tgui::Tabs::*)(const tgui::Layout2d&)>(
                                &tgui::Tabs::setSize),
                static_cast<void (tgui::Tabs::*)(const tgui::Layout2d&)>(
                    &tgui::Tabs::setSize),
                static_cast<void (tgui::Tabs::*)(tgui::Layout, tgui::Layout)>(
                    &tgui::Tabs::setSize));
        bindTabs["setEnabled"] = &tgui::Tabs::setEnabled;
        bindTabs["setAutoSize"] = &tgui::Tabs::setAutoSize;
        bindTabs["getAutoSize"] = &tgui::Tabs::getAutoSize;
        bindTabs["add"] = sol::overload(
            [](tgui::Tabs* self, const tgui::String& text) -> std::size_t {
                return self->add(text);
            },
            [](tgui::Tabs* self, const tgui::String& text, bool select) -> std::size_t {
                return self->add(text, select);
            });
        bindTabs["insert"] = sol::overload(
            [](tgui::Tabs* self, std::size_t index, const tgui::String& text) -> void {
                return self->insert(index, text);
            },
            [](tgui::Tabs* self, std::size_t index, const tgui::String& text,
                bool select) -> void { return self->insert(index, text, select); });
        bindTabs["getText"] = &tgui::Tabs::getText;
        bindTabs["changeText"] = &tgui::Tabs::changeText;
        bindTabs["select"] = sol::overload(
            static_cast<bool (tgui::Tabs::*)(const tgui::String&)>(&tgui::Tabs::select),
            static_cast<bool (tgui::Tabs::*)(std::size_t)>(&tgui::Tabs::select));
        bindTabs["deselect"] = &tgui::Tabs::deselect;
        bindTabs["remove"] = sol::overload(
            static_cast<bool (tgui::Tabs::*)(const tgui::String&)>(&tgui::Tabs::remove),
            static_cast<bool (tgui::Tabs::*)(std::size_t)>(&tgui::Tabs::remove));
        bindTabs["removeAll"] = &tgui::Tabs::removeAll;
        bindTabs["getSelected"] = &tgui::Tabs::getSelected;
        bindTabs["getSelectedIndex"] = &tgui::Tabs::getSelectedIndex;
        bindTabs["setTabVisible"] = &tgui::Tabs::setTabVisible;
        bindTabs["getTabVisible"] = &tgui::Tabs::getTabVisible;
        bindTabs["setTabEnabled"] = &tgui::Tabs::setTabEnabled;
        bindTabs["getTabEnabled"] = &tgui::Tabs::getTabEnabled;
        bindTabs["setTextSize"] = &tgui::Tabs::setTextSize;
        bindTabs["setTabHeight"] = &tgui::Tabs::setTabHeight;
        bindTabs["setMaximumTabWidth"] = &tgui::Tabs::setMaximumTabWidth;
        bindTabs["getMaximumTabWidth"] = &tgui::Tabs::getMaximumTabWidth;
        bindTabs["setMinimumTabWidth"] = &tgui::Tabs::setMinimumTabWidth;
        bindTabs["getMinimumTabWidth"] = &tgui::Tabs::getMinimumTabWidth;
        bindTabs["getTabsCount"] = &tgui::Tabs::getTabsCount;
        bindTabs["isMouseOnWidget"] = &tgui::Tabs::isMouseOnWidget;
        bindTabs["leftMousePressed"] = &tgui::Tabs::leftMousePressed;
        bindTabs["mouseMoved"] = &tgui::Tabs::mouseMoved;
        bindTabs["mouseNoLongerOnWidget"] = &tgui::Tabs::mouseNoLongerOnWidget;
        bindTabs["draw"] =

            [](tgui::Tabs* self, tgui::BackendRenderTargetBase* target,
                tgui::RenderStates states) { self->draw(*target, states); }

        ;
        bindTabs["create"] = &tgui::Tabs::create;
        bindTabs["copy"] = &tgui::Tabs::copy;
        bindTabs["onTabSelect"] = &tgui::Tabs::onTabSelect;
    }
};