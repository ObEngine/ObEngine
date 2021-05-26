#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Layout.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassLayout2d(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Layout2d> bindLayout2d
            = tguiNamespace.new_usertype<tgui::Layout2d>("Layout2d",
                sol::call_constructor,
                sol::constructors<tgui::Layout2d(), tgui::Layout2d(tgui::Vector2f),
                    tgui::Layout2d(tgui::Layout, tgui::Layout),
                    tgui::Layout2d(const char*), tgui::Layout2d(const tgui::String&)>());
        bindLayout2d["getValue"] = &tgui::Layout2d::getValue;
        bindLayout2d["toString"] = &tgui::Layout2d::toString;
        bindLayout2d["x"] = &tgui::Layout2d::x;
        bindLayout2d["y"] = &tgui::Layout2d::y;
    }
};