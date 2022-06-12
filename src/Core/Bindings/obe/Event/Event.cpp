#include <Bindings/obe/Event/Event.hpp>

#include <Event/CallbackScheduler.hpp>
#include <Event/Event.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventListener.hpp>
#include <Event/EventManager.hpp>
#include <Event/EventNamespace.hpp>
#include <Event/LuaEvent.hpp>

#include <Bindings/Config.hpp>

namespace obe::event::Bindings
{
    void LoadEnumCallbackSchedulerState(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        EventNamespace.new_enum<obe::event::CallbackSchedulerState>("CallbackSchedulerState",
            { { "Standby", obe::event::CallbackSchedulerState::Standby },
                { "Ready", obe::event::CallbackSchedulerState::Ready },
                { "Done", obe::event::CallbackSchedulerState::Done } });
    }
    void LoadEnumListenerChangeState(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        EventNamespace.new_enum<obe::event::ListenerChangeState>("ListenerChangeState",
            { { "Added", obe::event::ListenerChangeState::Added },
                { "Removed", obe::event::ListenerChangeState::Removed } });
    }
    void LoadClassCallbackProfiler(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::CallbackProfiler> bindCallbackProfiler
            = EventNamespace.new_usertype<obe::event::CallbackProfiler>(
                "CallbackProfiler", sol::call_constructor, sol::default_constructor);
        bindCallbackProfiler["hits"] = &obe::event::CallbackProfiler::hits;
        bindCallbackProfiler["time"] = &obe::event::CallbackProfiler::time;
        bindCallbackProfiler["min"] = &obe::event::CallbackProfiler::min;
        bindCallbackProfiler["max"] = &obe::event::CallbackProfiler::max;
    }
    void LoadClassCallbackScheduler(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::CallbackScheduler> bindCallbackScheduler
            = EventNamespace.new_usertype<obe::event::CallbackScheduler>("CallbackScheduler",
                sol::call_constructor, sol::constructors<obe::event::CallbackScheduler()>());
        bindCallbackScheduler["after"] = &obe::event::CallbackScheduler::after;
        bindCallbackScheduler["every"] = &obe::event::CallbackScheduler::every;
        bindCallbackScheduler["repeat"] = &obe::event::CallbackScheduler::repeat;
        bindCallbackScheduler["run"] = &obe::event::CallbackScheduler::run;
        bindCallbackScheduler["stop"] = &obe::event::CallbackScheduler::stop;
    }
    void LoadClassEventBase(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventBase> bindEventBase
            = EventNamespace.new_usertype<obe::event::EventBase>("EventBase", sol::call_constructor,
                sol::constructors<obe::event::EventBase(const std::string&, const std::string&),
                    obe::event::EventBase(const std::string&, const std::string&, bool)>());
        bindEventBase["get_state"] = &obe::event::EventBase::get_state;
        bindEventBase["get_name"] = &obe::event::EventBase::get_name;
        bindEventBase["get_identifier"] = &obe::event::EventBase::get_identifier;
        bindEventBase["add_external_listener"] = &obe::event::EventBase::add_external_listener;
        bindEventBase["remove_external_listener"] = &obe::event::EventBase::remove_external_listener;
        bindEventBase["get_profiler"] = &obe::event::EventBase::get_profiler;
    }
    void LoadClassEventGroup(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventGroup> bindEventGroup = EventNamespace.new_usertype<
            obe::event::EventGroup>("EventGroup", sol::call_constructor,
            sol::constructors<obe::event::EventGroup(const std::string&, const std::string&)>());
        bindEventGroup["get_view"] = &obe::event::EventGroup::get_view;
        bindEventGroup["set_joinable"] = &obe::event::EventGroup::set_joinable;
        bindEventGroup["is_joinable"] = &obe::event::EventGroup::is_joinable;
        bindEventGroup["get"] = static_cast<obe::event::EventBase& (
            obe::event::EventGroup::*)(const std::string&) const>(&obe::event::EventGroup::get);
        bindEventGroup["contains"] = &obe::event::EventGroup::contains;
        bindEventGroup["add"] = &obe::event::add_lua_event;
        bindEventGroup["remove"] = &obe::event::EventGroup::remove;
        bindEventGroup["trigger"] = sol::overload(
            [](obe::event::EventGroup* self, const std::string& name) -> void {
                return obe::event::trigger_lua_event(self, name);
            },
            [](obe::event::EventGroup* self, const std::string& name, sol::table data) -> void {
                return obe::event::trigger_lua_event(self, name, data);
            });
        bindEventGroup["get_events_names"] = &obe::event::EventGroup::get_events_names;
        bindEventGroup["get_events"] = &obe::event::EventGroup::get_events;
        bindEventGroup["get_identifier"] = &obe::event::EventGroup::get_identifier;
        bindEventGroup["get_name"] = &obe::event::EventGroup::get_name;
        bindEventGroup["on_add_listener"] = &obe::event::EventGroup::on_add_listener;
        bindEventGroup["on_remove_listener"] = &obe::event::EventGroup::on_remove_listener;
        bindEventGroup["get_profiler_results"] = &obe::event::EventGroup::get_profiler_results;
    }
    void LoadClassEventGroupView(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventGroupView> bindEventGroupView
            = EventNamespace.new_usertype<obe::event::EventGroupView>("EventGroupView",
                sol::call_constructor,
                sol::constructors<obe::event::EventGroupView(const obe::event::EventGroup&)>());
        bindEventGroupView["get_events_names"] = &obe::event::EventGroupView::get_events_names;
        bindEventGroupView["get_events"] = &obe::event::EventGroupView::get_events;
        bindEventGroupView["get_identifier"] = &obe::event::EventGroupView::get_identifier;
        bindEventGroupView["get_name"] = &obe::event::EventGroupView::get_name;
        bindEventGroupView["is_joinable"] = &obe::event::EventGroupView::is_joinable;
        bindEventGroupView["get"]
            = static_cast<obe::event::EventBase& (obe::event::EventGroupView::*)(const std::string&)
                    const>(&obe::event::EventGroupView::get);
        bindEventGroupView["contains"] = &obe::event::EventGroupView::contains;
        bindEventGroupView["get_profiler_results"] = &obe::event::EventGroupView::get_profiler_results;
    }
    void LoadClassEventManager(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventManager> bindEventManager
            = EventNamespace.new_usertype<obe::event::EventManager>("EventManager",
                sol::call_constructor, sol::constructors<obe::event::EventManager()>());
        bindEventManager["update"] = &obe::event::EventManager::update;
        bindEventManager["clear"] = &obe::event::EventManager::clear;
        bindEventManager["create_namespace"] = &obe::event::EventManager::create_namespace;
        bindEventManager["join_namespace"] = &obe::event::EventManager::join_namespace;
        bindEventManager["get_namespace"] = &obe::event::EventManager::get_namespace;
        bindEventManager["get_all_namespaces_names"]
            = &obe::event::EventManager::get_all_namespaces_names;
        bindEventManager["schedule"] = &obe::event::EventManager::schedule;
        bindEventManager["dump_profiler_results"] = &obe::event::EventManager::dump_profiler_results;
    }
    void LoadClassEventNamespace(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventNamespace> bindEventNamespace
            = EventNamespace.new_usertype<obe::event::EventNamespace>("EventNamespace",
                sol::call_constructor,
                sol::constructors<obe::event::EventNamespace(const std::string&)>());
        bindEventNamespace["create_group"] = &obe::event::EventNamespace::create_group;
        bindEventNamespace["join_group"] = &obe::event::EventNamespace::join_group;
        bindEventNamespace["get_group"] = &obe::event::EventNamespace::get_group;
        bindEventNamespace["get_all_groups_names"] = &obe::event::EventNamespace::get_all_groups_names;
        bindEventNamespace["remove_group"] = &obe::event::EventNamespace::remove_group;
        bindEventNamespace["does_group_exists"] = &obe::event::EventNamespace::does_group_exists;
        bindEventNamespace["get_view"] = &obe::event::EventNamespace::get_view;
        bindEventNamespace["set_joinable"] = &obe::event::EventNamespace::set_joinable;
        bindEventNamespace["is_joinable"] = &obe::event::EventNamespace::is_joinable;
    }
    void LoadClassEventNamespaceView(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventNamespaceView> bindEventNamespaceView
            = EventNamespace.new_usertype<obe::event::EventNamespaceView>("EventNamespaceView",
                sol::call_constructor,
                sol::constructors<obe::event::EventNamespaceView(
                    const obe::event::EventNamespace&)>());
        bindEventNamespaceView["join_group"] = &obe::event::EventNamespaceView::join_group;
        bindEventNamespaceView["get_group"] = &obe::event::EventNamespaceView::get_group;
        bindEventNamespaceView["get_all_groups_names"]
            = &obe::event::EventNamespaceView::get_all_groups_names;
        bindEventNamespaceView["does_group_exists"]
            = &obe::event::EventNamespaceView::does_group_exists;
    }
    void LoadClassLuaEventListener(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::LuaEventListener> bindLuaEventListener
            = EventNamespace.new_usertype<obe::event::LuaEventListener>("LuaEventListener",
                sol::call_constructor,
                sol::constructors<obe::event::LuaEventListener(sol::protected_function)>());
    }
    void LoadClassScopeProfiler(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::ScopeProfiler> bindScopeProfiler
            = EventNamespace.new_usertype<obe::event::ScopeProfiler>("ScopeProfiler",
                sol::call_constructor,
                sol::constructors<obe::event::ScopeProfiler(obe::event::CallbackProfiler&)>());
    }
};