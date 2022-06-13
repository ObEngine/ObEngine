#include <Bindings/obe/Time/Time.hpp>

#include <Time/Chronometer.hpp>
#include <Time/FramerateCounter.hpp>
#include <Time/FramerateManager.hpp>
#include <Time/TimeUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::time::Bindings
{
    void LoadClassChronometer(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        sol::usertype<obe::time::Chronometer> bindChronometer
            = TimeNamespace.new_usertype<obe::time::Chronometer>(
                "Chronometer", sol::call_constructor, sol::default_constructor);
        bindChronometer["start"] = &obe::time::Chronometer::start;
        bindChronometer["stop"] = &obe::time::Chronometer::stop;
        bindChronometer["reset"] = &obe::time::Chronometer::reset;
        bindChronometer["get_elapsed_time"] = &obe::time::Chronometer::get_elapsed_time;
        bindChronometer["set_limit"] = &obe::time::Chronometer::set_limit;
        bindChronometer["get_limit"] = &obe::time::Chronometer::get_limit;
        bindChronometer["is_over"] = &obe::time::Chronometer::is_over;
    }
    void LoadClassFramerateCounter(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        sol::usertype<obe::time::FramerateCounter> bindFramerateCounter
            = TimeNamespace.new_usertype<obe::time::FramerateCounter>(
                "FramerateCounter", sol::call_constructor, sol::default_constructor);
        bindFramerateCounter["render_tick"] = &obe::time::FramerateCounter::render_tick;
        bindFramerateCounter["update_tick"] = &obe::time::FramerateCounter::update_tick;
        bindFramerateCounter["load_font"] = &obe::time::FramerateCounter::load_font;
        bindFramerateCounter["draw"] = &obe::time::FramerateCounter::draw;
    }
    void LoadClassFramerateManager(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        sol::usertype<obe::time::FramerateManager> bindFramerateManager
            = TimeNamespace.new_usertype<obe::time::FramerateManager>("FramerateManager",
                sol::call_constructor,
                sol::constructors<obe::time::FramerateManager(obe::system::Window&)>());
        bindFramerateManager["configure"] = &obe::time::FramerateManager::configure;
        bindFramerateManager["update"] = &obe::time::FramerateManager::update;
        bindFramerateManager["should_render"] = &obe::time::FramerateManager::should_render;
        bindFramerateManager["should_update"] = &obe::time::FramerateManager::should_update;
        bindFramerateManager["start"] = &obe::time::FramerateManager::start;
        bindFramerateManager["reset"] = &obe::time::FramerateManager::reset;
        bindFramerateManager["get_delta_time"] = &obe::time::FramerateManager::get_delta_time;
        bindFramerateManager["get_game_speed"] = &obe::time::FramerateManager::get_game_speed;
        bindFramerateManager["get_speed_coefficient"]
            = &obe::time::FramerateManager::get_speed_coefficient;
        bindFramerateManager["is_framerate_limited"]
            = &obe::time::FramerateManager::is_framerate_limited;
        bindFramerateManager["get_framerate_target"]
            = &obe::time::FramerateManager::get_framerate_target;
        bindFramerateManager["is_vsync_enabled"] = &obe::time::FramerateManager::is_vsync_enabled;
        bindFramerateManager["set_speed_coefficient"]
            = &obe::time::FramerateManager::set_speed_coefficient;
        bindFramerateManager["set_framerate_target"]
            = &obe::time::FramerateManager::set_framerate_target;
        bindFramerateManager["set_vsync_enabled"] = &obe::time::FramerateManager::set_vsync_enabled;
    }
    void LoadFunctionEpoch(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        TimeNamespace.set_function("epoch", &obe::time::epoch);
    }
    void LoadGlobalSeconds(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        TimeNamespace["seconds"] = obe::time::seconds;
    }
    void LoadGlobalMilliseconds(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        TimeNamespace["milliseconds"] = obe::time::milliseconds;
    }
    void LoadGlobalMicroseconds(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        TimeNamespace["microseconds"] = obe::time::microseconds;
    }
    void LoadGlobalMinutes(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        TimeNamespace["minutes"] = obe::time::minutes;
    }
    void LoadGlobalHours(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        TimeNamespace["hours"] = obe::time::hours;
    }
    void LoadGlobalDays(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        TimeNamespace["days"] = obe::time::days;
    }
    void LoadGlobalWeeks(sol::state_view state)
    {
        sol::table TimeNamespace = state["obe"]["time"].get<sol::table>();
        TimeNamespace["weeks"] = obe::time::weeks;
    }
};