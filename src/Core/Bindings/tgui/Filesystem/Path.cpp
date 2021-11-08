#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Filesystem.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassPath(sol::state_view state)
    {
        sol::table FilesystemNamespace = state["tgui"]["Filesystem"].get<sol::table>();
        sol::usertype<tgui::Filesystem::Path> bindPath
            = FilesystemNamespace.new_usertype<tgui::Filesystem::Path>("Path",
                sol::call_constructor,
                sol::constructors<tgui::Filesystem::Path(),
                    tgui::Filesystem::Path(const tgui::String&)>());
        bindPath["isEmpty"] = &tgui::Filesystem::Path::isEmpty;
        bindPath["asString"] = &tgui::Filesystem::Path::asString;
        bindPath["getParentPath"] = &tgui::Filesystem::Path::getParentPath;
        bindPath["getFilename"] = &tgui::Filesystem::Path::getFilename;
        bindPath["getNormalForm"] = &tgui::Filesystem::Path::getNormalForm;
        bindPath["asNativeString"] = &tgui::Filesystem::Path::asNativeString;
        bindPath[sol::meta_function::division] = sol::overload(
            static_cast<tgui::Filesystem::Path (tgui::Filesystem::Path::*)(
                const tgui::Filesystem::Path&) const>(&tgui::Filesystem::Path::operator/),
            static_cast<tgui::Filesystem::Path (tgui::Filesystem::Path::*)(const tgui::String&)
                    const>(&tgui::Filesystem::Path::operator/));
        bindPath[sol::meta_function::equal_to] = &tgui::Filesystem::Path::operator==;
    }
};