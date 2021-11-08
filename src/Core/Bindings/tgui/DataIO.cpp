#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Loading/DataIO.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassDataIO(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::DataIO> bindDataIO = tguiNamespace.new_usertype<tgui::DataIO>(
            "DataIO", sol::call_constructor, sol::default_constructor);
        bindDataIO["parse"] = &tgui::DataIO::parse;
        bindDataIO["emit"] = &tgui::DataIO::emit;
    }
};