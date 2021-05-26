#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Timer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTimer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Timer> bindTimer
            = tguiNamespace.new_usertype<tgui::Timer>("Timer");
        bindTimer["setInterval"] = &tgui::Timer::setInterval;
        bindTimer["getInterval"] = &tgui::Timer::getInterval;
        bindTimer["setEnabled"] = &tgui::Timer::setEnabled;
        bindTimer["isEnabled"] = &tgui::Timer::isEnabled;
        bindTimer["setCallback"] = sol::overload(
            static_cast<void (tgui::Timer::*)(const std::function<void()>&)>(
                &tgui::Timer::setCallback),
            static_cast<void (tgui::Timer::*)(
                const std::function<void(std::shared_ptr<tgui::Timer>)>&)>(
                &tgui::Timer::setCallback));
        bindTimer["restart"] = &tgui::Timer::restart;
        bindTimer["create"] = sol::overload(
            static_cast<std::shared_ptr<tgui::Timer> (*)(const std::function<void()>&,
                tgui::Duration, bool)>(&tgui::Timer::create),
            static_cast<std::shared_ptr<tgui::Timer> (*)(
                const std::function<void(std::shared_ptr<tgui::Timer>)>&, tgui::Duration,
                bool)>(&tgui::Timer::create));
        bindTimer["scheduleCallback"] = sol::overload(
            [](tgui::Timer* self, std::function<void()> callback) -> void {
                return self->scheduleCallback(callback);
            },
            [](tgui::Timer* self, std::function<void()> callback, tgui::Duration interval)
                -> void { return self->scheduleCallback(callback, interval); });
        bindTimer["updateTime"] = &tgui::Timer::updateTime;
        bindTimer["getNextScheduledTime"] = &tgui::Timer::getNextScheduledTime;
        bindTimer["clearTimers"] = &tgui::Timer::clearTimers;
    }
};