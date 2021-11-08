#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/MenuBar.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassMenuBar(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::MenuBar> bindMenuBar
            = tguiNamespace.new_usertype<tgui::MenuBar>("MenuBar", sol::call_constructor,
                sol::constructors<tgui::MenuBar(), tgui::MenuBar(const char*),
                    tgui::MenuBar(const char*, bool), tgui::MenuBar(const tgui::MenuBar&)>(),
                sol::base_classes, sol::bases<tgui::Widget>());
        bindMenuBar["operator="]
            = sol::overload(static_cast<tgui::MenuBar& (tgui::MenuBar::*)(const tgui::MenuBar&)>(
                                &tgui::MenuBar::operator=),
                static_cast<tgui::MenuBar& (tgui::MenuBar::*)(tgui::MenuBar &&)>(
                    &tgui::MenuBar::operator=));
        bindMenuBar["getSharedRenderer"]
            = sol::overload(static_cast<tgui::MenuBarRenderer* (tgui::MenuBar::*)()>(
                                &tgui::MenuBar::getSharedRenderer),
                static_cast<const tgui::MenuBarRenderer* (tgui::MenuBar::*)() const>(
                    &tgui::MenuBar::getSharedRenderer));
        bindMenuBar["getRenderer"] = sol::overload(
            static_cast<tgui::MenuBarRenderer* (tgui::MenuBar::*)()>(&tgui::MenuBar::getRenderer),
            static_cast<const tgui::MenuBarRenderer* (tgui::MenuBar::*)() const>(
                &tgui::MenuBar::getRenderer));
        bindMenuBar["setSize"] = sol::overload(
            static_cast<void (tgui::MenuBar::*)(const tgui::Layout2d&)>(&tgui::MenuBar::setSize),
            static_cast<void (tgui::MenuBar::*)(const tgui::Layout2d&)>(&tgui::MenuBar::setSize),
            static_cast<void (tgui::MenuBar::*)(tgui::Layout, tgui::Layout)>(
                &tgui::MenuBar::setSize));
        bindMenuBar["setEnabled"] = &tgui::MenuBar::setEnabled;
        bindMenuBar["addMenu"] = &tgui::MenuBar::addMenu;
        bindMenuBar["addMenuItem"] = sol::overload(
            static_cast<bool (tgui::MenuBar::*)(const tgui::String&)>(&tgui::MenuBar::addMenuItem),
            static_cast<bool (tgui::MenuBar::*)(const tgui::String&, const tgui::String&)>(
                &tgui::MenuBar::addMenuItem),
            [](tgui::MenuBar* self, const std::vector<tgui::String>& hierarchy) -> bool {
                return self->addMenuItem(hierarchy);
            },
            [](tgui::MenuBar* self, const std::vector<tgui::String>& hierarchy, bool createParents)
                -> bool { return self->addMenuItem(hierarchy, createParents); });
        bindMenuBar["removeAllMenus"] = &tgui::MenuBar::removeAllMenus;
        bindMenuBar["removeMenu"] = &tgui::MenuBar::removeMenu;
        bindMenuBar["removeMenuItem"] = sol::overload(
            static_cast<bool (tgui::MenuBar::*)(const tgui::String&, const tgui::String&)>(
                &tgui::MenuBar::removeMenuItem),
            [](tgui::MenuBar* self, const std::vector<tgui::String>& hierarchy) -> bool {
                return self->removeMenuItem(hierarchy);
            },
            [](tgui::MenuBar* self, const std::vector<tgui::String>& hierarchy,
                bool removeParentsWhenEmpty) -> bool {
                return self->removeMenuItem(hierarchy, removeParentsWhenEmpty);
            });
        bindMenuBar["removeMenuItems"] = &tgui::MenuBar::removeMenuItems;
        bindMenuBar["removeSubMenuItems"] = &tgui::MenuBar::removeSubMenuItems;
        bindMenuBar["setMenuEnabled"] = &tgui::MenuBar::setMenuEnabled;
        bindMenuBar["getMenuEnabled"] = &tgui::MenuBar::getMenuEnabled;
        bindMenuBar["setMenuItemEnabled"] = sol::overload(
            static_cast<bool (tgui::MenuBar::*)(const tgui::String&, const tgui::String&, bool)>(
                &tgui::MenuBar::setMenuItemEnabled),
            static_cast<bool (tgui::MenuBar::*)(const std::vector<tgui::String>&, bool)>(
                &tgui::MenuBar::setMenuItemEnabled));
        bindMenuBar["getMenuItemEnabled"] = sol::overload(
            static_cast<bool (tgui::MenuBar::*)(const tgui::String&, const tgui::String&) const>(
                &tgui::MenuBar::getMenuItemEnabled),
            static_cast<bool (tgui::MenuBar::*)(const std::vector<tgui::String>&) const>(
                &tgui::MenuBar::getMenuItemEnabled));
        bindMenuBar["setTextSize"] = &tgui::MenuBar::setTextSize;
        bindMenuBar["setMinimumSubMenuWidth"] = &tgui::MenuBar::setMinimumSubMenuWidth;
        bindMenuBar["getMinimumSubMenuWidth"] = &tgui::MenuBar::getMinimumSubMenuWidth;
        bindMenuBar["setInvertedMenuDirection"] = &tgui::MenuBar::setInvertedMenuDirection;
        bindMenuBar["getInvertedMenuDirection"] = &tgui::MenuBar::getInvertedMenuDirection;
        bindMenuBar["getMenus"] = &tgui::MenuBar::getMenus;
        bindMenuBar["closeMenu"] = &tgui::MenuBar::closeMenu;
        bindMenuBar["isMouseOnWidget"] = &tgui::MenuBar::isMouseOnWidget;
        bindMenuBar["leftMousePressed"] = &tgui::MenuBar::leftMousePressed;
        bindMenuBar["leftMouseReleased"] = &tgui::MenuBar::leftMouseReleased;
        bindMenuBar["mouseMoved"] = &tgui::MenuBar::mouseMoved;
        bindMenuBar["draw"] = &tgui::MenuBar::draw;
        bindMenuBar["create"] = &tgui::MenuBar::create;
        bindMenuBar["copy"] = &tgui::MenuBar::copy;
        bindMenuBar["onMenuItemClick"] = &tgui::MenuBar::onMenuItemClick;
    }
};