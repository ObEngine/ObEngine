#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Filesystem.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassFileInfo(sol::state_view state)
    {
        sol::table FilesystemNamespace = state["tgui"]["Filesystem"].get<sol::table>();
        sol::usertype<tgui::Filesystem::FileInfo> bindFileInfo
            = FilesystemNamespace.new_usertype<tgui::Filesystem::FileInfo>(
                "FileInfo", sol::call_constructor, sol::default_constructor);
        bindFileInfo["filename"] = &tgui::Filesystem::FileInfo::filename;
        bindFileInfo["path"] = &tgui::Filesystem::FileInfo::path;
        bindFileInfo["directory"] = &tgui::Filesystem::FileInfo::directory;
        bindFileInfo["fileSize"] = &tgui::Filesystem::FileInfo::fileSize;
        bindFileInfo["modificationTime"] = &tgui::Filesystem::FileInfo::modificationTime;
    }
};