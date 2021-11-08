#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/FileDialogIconLoader.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassFileDialogIconLoader(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::FileDialogIconLoader> bindFileDialogIconLoader
            = tguiNamespace.new_usertype<tgui::FileDialogIconLoader>("FileDialogIconLoader");
        bindFileDialogIconLoader["update"] = &tgui::FileDialogIconLoader::update;
        bindFileDialogIconLoader["supportsSystemIcons"]
            = &tgui::FileDialogIconLoader::supportsSystemIcons;
        bindFileDialogIconLoader["hasGenericIcons"] = &tgui::FileDialogIconLoader::hasGenericIcons;
        bindFileDialogIconLoader["getGenericFileIcon"]
            = &tgui::FileDialogIconLoader::getGenericFileIcon;
        bindFileDialogIconLoader["requestFileIcons"]
            = &tgui::FileDialogIconLoader::requestFileIcons;
        bindFileDialogIconLoader["retrieveFileIcons"]
            = &tgui::FileDialogIconLoader::retrieveFileIcons;
        bindFileDialogIconLoader["createInstance"] = &tgui::FileDialogIconLoader::createInstance;
    }
};