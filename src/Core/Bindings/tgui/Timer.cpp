#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Timer.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTimer(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Timer> bindTimer = tguiNamespace.new_usertype<tgui::Timer>("Timer");
        bindTimer["operator="] = &tgui::Timer::operator=;
        bindTimer["setInterval"] = &tgui::Timer::setInterval;
        bindTimer["getInterval"] = &tgui::Timer::getInterval;
        bindTimer["setEnabled"] = &tgui::Timer::setEnabled;
        bindTimer["isEnabled"] = &tgui::Timer::isEnabled;
        bindTimer["setCallback"]
            = sol::overload(static_cast<void (tgui::Timer::*)(const std::function<void()>&)>(
                                &tgui::Timer::setCallback),
                static_cast<void (tgui::Timer::*)(
                    const std::function<void(std::shared_ptr<tgui::Timer>)>&)>(
                    &tgui::Timer::setCallback));
        bindTimer["restart"] = &tgui::Timer::restart;
        bindTimer["create"] = sol::overload(
            [](const std::function<void()>& callback, tgui::Duration interval)
                -> std::shared_ptr<tgui::Timer> { return tgui::Timer::create(callback, interval); },
            [](const std::function<void()>& callback, tgui::Duration interval,
                bool enable) -> std::shared_ptr<tgui::Timer> {
                return tgui::Timer::create(callback, interval, enable);
            },
            [](const std::function<void(std::shared_ptr<tgui::Timer>)>& callback,
                tgui::Duration interval) -> std::shared_ptr<tgui::Timer> {
                return tgui::Timer::create(callback, interval);
            },
            [](const std::function<void(std::shared_ptr<tgui::Timer>)>& callback,
                tgui::Duration interval, bool enable) -> std::shared_ptr<tgui::Timer> {
                return tgui::Timer::create(callback, interval, enable);
            });
        bindTimer["scheduleCallback"] = sol::overload(
            [](std::function<void()> callback) -> void {
                return tgui::Timer::scheduleCallback(callback);
            },
            [](std::function<void()> callback, tgui::Duration interval) -> void {
                return tgui::Timer::scheduleCallback(callback, interval);
            });
        bindTimer["updateTime"] = &tgui::Timer::updateTime;
        bindTimer["getNextScheduledTime"] = &tgui::Timer::getNextScheduledTime;
        bindTimer["clearTimers"] = &tgui::Timer::clearTimers;
    }
};