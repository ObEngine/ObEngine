#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Filesystem.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassFilesystem(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Filesystem> bindFilesystem
            = tguiNamespace.new_usertype<tgui::Filesystem>(
                "Filesystem", sol::call_constructor, sol::default_constructor);
        bindFilesystem["directoryExists"]
            = sol::overload(static_cast<bool (*)(const tgui::Filesystem::Path&)>(
                                &tgui::Filesystem::directoryExists),
                static_cast<bool (*)(const tgui::String&)>(
                    &tgui::Filesystem::directoryExists));
        bindFilesystem["fileExists"] = sol::overload(
            static_cast<bool (*)(const tgui::Filesystem::Path&)>(
                &tgui::Filesystem::fileExists),
            static_cast<bool (*)(const tgui::String&)>(&tgui::Filesystem::fileExists));
        bindFilesystem["createDirectory"]
            = sol::overload(static_cast<bool (*)(const tgui::Filesystem::Path&)>(
                                &tgui::Filesystem::createDirectory),
                static_cast<bool (*)(const tgui::String&)>(
                    &tgui::Filesystem::createDirectory));
        bindFilesystem["getHomeDirectory"] = &tgui::Filesystem::getHomeDirectory;
        bindFilesystem["getCurrentWorkingDirectory"]
            = &tgui::Filesystem::getCurrentWorkingDirectory;
        bindFilesystem["getLocalDataDirectory"]
            = &tgui::Filesystem::getLocalDataDirectory;
        bindFilesystem["listFilesInDirectory"] = &tgui::Filesystem::listFilesInDirectory;
    }
};