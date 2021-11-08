#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Exception.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassException(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Exception> bindException
            = tguiNamespace.new_usertype<tgui::Exception>("Exception", sol::call_constructor,
                sol::constructors<tgui::Exception(const tgui::String&)>());
    }
};