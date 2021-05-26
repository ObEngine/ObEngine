#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Renderers/FileDialogRenderer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassFileDialogRenderer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::FileDialogRenderer> bindFileDialogRenderer
            = tguiNamespace.new_usertype<tgui::FileDialogRenderer>("FileDialogRenderer",
                sol::call_constructor, sol::default_constructor, sol::base_classes,
                sol::bases<tgui::ChildWindowRenderer, tgui::WidgetRenderer>());
        bindFileDialogRenderer["setListView"] = &tgui::FileDialogRenderer::setListView;
        bindFileDialogRenderer["getListView"] = &tgui::FileDialogRenderer::getListView;
        bindFileDialogRenderer["setEditBox"] = &tgui::FileDialogRenderer::setEditBox;
        bindFileDialogRenderer["getEditBox"] = &tgui::FileDialogRenderer::getEditBox;
        bindFileDialogRenderer["setFilenameLabel"]
            = &tgui::FileDialogRenderer::setFilenameLabel;
        bindFileDialogRenderer["getFilenameLabel"]
            = &tgui::FileDialogRenderer::getFilenameLabel;
        bindFileDialogRenderer["setFileTypeComboBox"]
            = &tgui::FileDialogRenderer::setFileTypeComboBox;
        bindFileDialogRenderer["getFileTypeComboBox"]
            = &tgui::FileDialogRenderer::getFileTypeComboBox;
        bindFileDialogRenderer["setButton"] = &tgui::FileDialogRenderer::setButton;
        bindFileDialogRenderer["getButton"] = &tgui::FileDialogRenderer::getButton;
        bindFileDialogRenderer["setBackButton"]
            = &tgui::FileDialogRenderer::setBackButton;
        bindFileDialogRenderer["getBackButton"]
            = &tgui::FileDialogRenderer::getBackButton;
        bindFileDialogRenderer["setForwardButton"]
            = &tgui::FileDialogRenderer::setForwardButton;
        bindFileDialogRenderer["getForwardButton"]
            = &tgui::FileDialogRenderer::getForwardButton;
        bindFileDialogRenderer["setUpButton"] = &tgui::FileDialogRenderer::setUpButton;
        bindFileDialogRenderer["getUpButton"] = &tgui::FileDialogRenderer::getUpButton;
        bindFileDialogRenderer["setArrowsOnNavigationButtonsVisible"]
            = &tgui::FileDialogRenderer::setArrowsOnNavigationButtonsVisible;
        bindFileDialogRenderer["getArrowsOnNavigationButtonsVisible"]
            = &tgui::FileDialogRenderer::getArrowsOnNavigationButtonsVisible;
    }
};