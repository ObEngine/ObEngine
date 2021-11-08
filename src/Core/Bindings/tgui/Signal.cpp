#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Signal.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSignal(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Signal> bindSignal = tguiNamespace.new_usertype<tgui::Signal>("Signal",
            sol::call_constructor, sol::constructors<tgui::Signal(const tgui::Signal&)>());
        bindSignal["operator="]
            = sol::overload(static_cast<tgui::Signal& (tgui::Signal::*)(const tgui::Signal&)>(
                                &tgui::Signal::operator=),
                static_cast<tgui::Signal& (tgui::Signal::*)(tgui::Signal &&)>(
                    &tgui::Signal::operator=));
        bindSignal["disconnect"] = &tgui::Signal::disconnect;
        bindSignal["disconnectAll"] = &tgui::Signal::disconnectAll;
        bindSignal["emit"] = &tgui::Signal::emit;
        bindSignal["getName"] = &tgui::Signal::getName;
        bindSignal["setEnabled"] = &tgui::Signal::setEnabled;
        bindSignal["isEnabled"] = &tgui::Signal::isEnabled;
    }
};