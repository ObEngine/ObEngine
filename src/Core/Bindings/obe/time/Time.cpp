#include <Bindings/obe/time/Time.hpp>

#include <Time/Chronometer.hpp>
#include <Time/FramerateCounter.hpp>
#include <Time/FramerateManager.hpp>
#include <Time/TimeUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::time::bindings
{
    void load_class_chronometer(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        sol::usertype<obe::time::Chronometer> bind_chronometer
            = time_namespace.new_usertype<obe::time::Chronometer>(
                "Chronometer", sol::call_constructor, sol::default_constructor);
        bind_chronometer["start"] = &obe::time::Chronometer::start;
        bind_chronometer["stop"] = &obe::time::Chronometer::stop;
        bind_chronometer["reset"] = &obe::time::Chronometer::reset;
        bind_chronometer["get_elapsed_time"] = &obe::time::Chronometer::get_elapsed_time;
        bind_chronometer["set_limit"] = &obe::time::Chronometer::set_limit;
        bind_chronometer["get_limit"] = &obe::time::Chronometer::get_limit;
        bind_chronometer["is_over"] = &obe::time::Chronometer::is_over;
    }
    void load_class_framerate_counter(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        sol::usertype<obe::time::FramerateCounter> bind_framerate_counter
            = time_namespace.new_usertype<obe::time::FramerateCounter>(
                "FramerateCounter", sol::call_constructor, sol::default_constructor);
        bind_framerate_counter["render_tick"] = &obe::time::FramerateCounter::render_tick;
        bind_framerate_counter["update_tick"] = &obe::time::FramerateCounter::update_tick;
        bind_framerate_counter["load_font"] = &obe::time::FramerateCounter::load_font;
        bind_framerate_counter["draw"] = &obe::time::FramerateCounter::draw;
    }
    void load_class_framerate_manager(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        sol::usertype<obe::time::FramerateManager> bind_framerate_manager
            = time_namespace.new_usertype<obe::time::FramerateManager>("FramerateManager",
                sol::call_constructor,
                sol::constructors<obe::time::FramerateManager(obe::system::Window&)>());
        bind_framerate_manager["configure"] = &obe::time::FramerateManager::configure;
        bind_framerate_manager["update"] = &obe::time::FramerateManager::update;
        bind_framerate_manager["should_render"] = &obe::time::FramerateManager::should_render;
        bind_framerate_manager["should_update"] = &obe::time::FramerateManager::should_update;
        bind_framerate_manager["start"] = &obe::time::FramerateManager::start;
        bind_framerate_manager["reset"] = &obe::time::FramerateManager::reset;
        bind_framerate_manager["get_raw_delta_time"]
            = &obe::time::FramerateManager::get_raw_delta_time;
        bind_framerate_manager["get_delta_time"] = &obe::time::FramerateManager::get_delta_time;
        bind_framerate_manager["get_speed_coefficient"]
            = &obe::time::FramerateManager::get_speed_coefficient;
        bind_framerate_manager["is_framerate_limited"]
            = &obe::time::FramerateManager::is_framerate_limited;
        bind_framerate_manager["get_framerate_target"]
            = &obe::time::FramerateManager::get_framerate_target;
        bind_framerate_manager["is_vsync_enabled"] = &obe::time::FramerateManager::is_vsync_enabled;
        bind_framerate_manager["set_speed_coefficient"]
            = &obe::time::FramerateManager::set_speed_coefficient;
        bind_framerate_manager["set_framerate_target"]
            = &obe::time::FramerateManager::set_framerate_target;
        bind_framerate_manager["set_vsync_enabled"]
            = &obe::time::FramerateManager::set_vsync_enabled;
        bind_framerate_manager["set_max_delta_time"]
            = &obe::time::FramerateManager::set_max_delta_time;
    }
    void load_function_epoch(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        time_namespace.set_function("epoch", &obe::time::epoch);
    }
    void load_global_seconds(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        time_namespace["seconds"] = obe::time::seconds;
    }
    void load_global_milliseconds(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        time_namespace["milliseconds"] = obe::time::milliseconds;
    }
    void load_global_microseconds(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        time_namespace["microseconds"] = obe::time::microseconds;
    }
    void load_global_minutes(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        time_namespace["minutes"] = obe::time::minutes;
    }
    void load_global_hours(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        time_namespace["hours"] = obe::time::hours;
    }
    void load_global_days(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        time_namespace["days"] = obe::time::days;
    }
    void load_global_weeks(sol::state_view state)
    {
        sol::table time_namespace = state["obe"]["time"].get<sol::table>();
        time_namespace["weeks"] = obe::time::weeks;
    }
};