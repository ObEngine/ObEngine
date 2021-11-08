#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Signal.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSignalAnimation(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SignalAnimation> bindSignalAnimation
            = tguiNamespace.new_usertype<tgui::SignalAnimation>(
                "SignalAnimation", sol::base_classes, sol::bases<tgui::Signal>());
        bindSignalAnimation["emit"] = &tgui::SignalAnimation::emit;
    }
};