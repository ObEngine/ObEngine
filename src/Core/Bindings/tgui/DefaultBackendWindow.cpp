#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/DefaultBackendWindow.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassDefaultBackendWindow(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::DefaultBackendWindow> bindDefaultBackendWindow
            = tguiNamespace.new_usertype<tgui::DefaultBackendWindow>("DefaultBackendWindow");
        bindDefaultBackendWindow["getGui"] = &tgui::DefaultBackendWindow::getGui;
        bindDefaultBackendWindow["isOpen"] = &tgui::DefaultBackendWindow::isOpen;
        bindDefaultBackendWindow["close"] = &tgui::DefaultBackendWindow::close;
        bindDefaultBackendWindow["pollEvent"] = &tgui::DefaultBackendWindow::pollEvent;
        bindDefaultBackendWindow["draw"] = &tgui::DefaultBackendWindow::draw;
        bindDefaultBackendWindow["mainLoop"] = &tgui::DefaultBackendWindow::mainLoop;
        bindDefaultBackendWindow["setIcon"] = &tgui::DefaultBackendWindow::setIcon;
        bindDefaultBackendWindow["create"] = &tgui::DefaultBackendWindow::create;
    }
};