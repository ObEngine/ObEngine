#include <Bindings/obe/event/Event.hpp>

#include <Event/CallbackScheduler.hpp>
#include <Event/Event.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventListener.hpp>
#include <Event/EventManager.hpp>
#include <Event/EventNamespace.hpp>
#include <Event/LuaEvent.hpp>

#include <Bindings/Config.hpp>

namespace obe::event::bindings
{
    void load_enum_callback_scheduler_state(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        event_namespace.new_enum<obe::event::CallbackSchedulerState>("CallbackSchedulerState",
            { { "Standby", obe::event::CallbackSchedulerState::Standby },
                { "Ready", obe::event::CallbackSchedulerState::Ready },
                { "Done", obe::event::CallbackSchedulerState::Done } });
    }
    void load_enum_listener_change_state(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        event_namespace.new_enum<obe::event::ListenerChangeState>("ListenerChangeState",
            { { "Added", obe::event::ListenerChangeState::Added },
                { "Removed", obe::event::ListenerChangeState::Removed } });
    }
    void load_class_callback_scheduler(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::CallbackScheduler> bind_callback_scheduler
            = event_namespace.new_usertype<obe::event::CallbackScheduler>("CallbackScheduler",
                sol::call_constructor, sol::constructors<obe::event::CallbackScheduler()>());
        bind_callback_scheduler["after"] = &obe::event::CallbackScheduler::after;
        bind_callback_scheduler["every"] = &obe::event::CallbackScheduler::every;
        bind_callback_scheduler["replay"] = &obe::event::CallbackScheduler::repeat;
        bind_callback_scheduler["run"] = &obe::event::CallbackScheduler::run;
        bind_callback_scheduler["stop"] = &obe::event::CallbackScheduler::stop;
    }
    void load_class_event_base(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventBase> bind_event_base
            = event_namespace.new_usertype<obe::event::EventBase>("EventBase",
                sol::call_constructor,
                sol::constructors<obe::event::EventBase(const std::string&, const std::string&),
                    obe::event::EventBase(const std::string&, const std::string&, bool)>());
        bind_event_base["get_state"] = &obe::event::EventBase::get_state;
        bind_event_base["get_name"] = &obe::event::EventBase::get_name;
        bind_event_base["get_identifier"] = &obe::event::EventBase::get_identifier;
        bind_event_base["add_external_listener"] = &obe::event::EventBase::add_external_listener;
        bind_event_base["remove_external_listener"]
            = &obe::event::EventBase::remove_external_listener;
    }
    void load_class_event_group(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventGroup> bind_event_group
            = event_namespace.new_usertype<obe::event::EventGroup>("EventGroup");
        bind_event_group["get_view"] = &obe::event::EventGroup::get_view;
        bind_event_group["set_joinable"] = &obe::event::EventGroup::set_joinable;
        bind_event_group["is_joinable"] = &obe::event::EventGroup::is_joinable;
        bind_event_group["get"] = static_cast<obe::event::EventBase& (
            obe::event::EventGroup::*)(const std::string&) const>(&obe::event::EventGroup::get);
        bind_event_group["contains"] = &obe::event::EventGroup::contains;
        bind_event_group["add"] = &obe::event::add_lua_event;
        bind_event_group["remove"] = &obe::event::EventGroup::remove;
        bind_event_group["trigger"] = sol::overload(
            [](obe::event::EventGroup* self, const std::string& name) -> void {
                return obe::event::trigger_lua_event(self, name);
            },
            [](obe::event::EventGroup* self, const std::string& name, sol::table data) -> void {
                return obe::event::trigger_lua_event(self, name, data);
            });
        bind_event_group["get_events_names"] = &obe::event::EventGroup::get_events_names;
        bind_event_group["get_events"] = &obe::event::EventGroup::get_events;
        bind_event_group["get_identifier"] = &obe::event::EventGroup::get_identifier;
        bind_event_group["get_name"] = &obe::event::EventGroup::get_name;
        bind_event_group["on_add_listener"] = &obe::event::EventGroup::on_add_listener;
        bind_event_group["on_remove_listener"] = &obe::event::EventGroup::on_remove_listener;
    }
    void load_class_event_group_view(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventGroupView> bind_event_group_view
            = event_namespace.new_usertype<obe::event::EventGroupView>("EventGroupView",
                sol::call_constructor,
                sol::constructors<obe::event::EventGroupView(const obe::event::EventGroup&)>());
        bind_event_group_view["get_events_names"] = &obe::event::EventGroupView::get_events_names;
        bind_event_group_view["get_events"] = &obe::event::EventGroupView::get_events;
        bind_event_group_view["get_identifier"] = &obe::event::EventGroupView::get_identifier;
        bind_event_group_view["get_name"] = &obe::event::EventGroupView::get_name;
        bind_event_group_view["is_joinable"] = &obe::event::EventGroupView::is_joinable;
        bind_event_group_view["get"]
            = static_cast<obe::event::EventBase& (obe::event::EventGroupView::*)(const std::string&)
                    const>(&obe::event::EventGroupView::get);
        bind_event_group_view["contains"] = &obe::event::EventGroupView::contains;
    }
    void load_class_event_manager(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventManager> bind_event_manager
            = event_namespace.new_usertype<obe::event::EventManager>("EventManager",
                sol::call_constructor, sol::constructors<obe::event::EventManager()>());
        bind_event_manager["update"] = &obe::event::EventManager::update;
        bind_event_manager["clear"] = &obe::event::EventManager::clear;
        bind_event_manager["create_namespace"] = &obe::event::EventManager::create_namespace;
        bind_event_manager["join_namespace"] = &obe::event::EventManager::join_namespace;
        bind_event_manager["get_namespace"] = &obe::event::EventManager::get_namespace;
        bind_event_manager["get_all_namespaces_names"]
            = &obe::event::EventManager::get_all_namespaces_names;
        bind_event_manager["schedule"] = &obe::event::EventManager::schedule;
    }
    void load_class_event_namespace(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventNamespace> bind_event_namespace
            = event_namespace.new_usertype<obe::event::EventNamespace>("EventNamespace",
                sol::call_constructor,
                sol::constructors<obe::event::EventNamespace(
                    const std::string&, obe::event::EventNamespace::ConstructorKey)>());
        bind_event_namespace["create_group"] = &obe::event::EventNamespace::create_group;
        bind_event_namespace["join_group"] = &obe::event::EventNamespace::join_group;
        bind_event_namespace["get_group"] = &obe::event::EventNamespace::get_group;
        bind_event_namespace["get_all_groups_names"]
            = &obe::event::EventNamespace::get_all_groups_names;
        bind_event_namespace["remove_group"] = &obe::event::EventNamespace::remove_group;
        bind_event_namespace["does_group_exists"] = &obe::event::EventNamespace::does_group_exists;
        bind_event_namespace["get_view"] = &obe::event::EventNamespace::get_view;
        bind_event_namespace["set_joinable"] = &obe::event::EventNamespace::set_joinable;
        bind_event_namespace["is_joinable"] = &obe::event::EventNamespace::is_joinable;
        bind_event_namespace["get_name"] = &obe::event::EventNamespace::get_name;
    }
    void load_class_event_namespace_view(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::EventNamespaceView> bind_event_namespace_view
            = event_namespace.new_usertype<obe::event::EventNamespaceView>("EventNamespaceView",
                sol::call_constructor,
                sol::constructors<obe::event::EventNamespaceView(
                    const obe::event::EventNamespace&)>());
        bind_event_namespace_view["join_group"] = &obe::event::EventNamespaceView::join_group;
        bind_event_namespace_view["get_group"] = &obe::event::EventNamespaceView::get_group;
        bind_event_namespace_view["get_all_groups_names"]
            = &obe::event::EventNamespaceView::get_all_groups_names;
        bind_event_namespace_view["does_group_exists"]
            = &obe::event::EventNamespaceView::does_group_exists;
        bind_event_namespace_view["get_name"] = &obe::event::EventNamespaceView::get_name;
    }
    void load_class_lua_event_listener(sol::state_view state)
    {
        sol::table event_namespace = state["obe"]["event"].get<sol::table>();
        sol::usertype<obe::event::LuaEventListener> bind_lua_event_listener
            = event_namespace.new_usertype<obe::event::LuaEventListener>("LuaEventListener",
                sol::call_constructor,
                sol::constructors<obe::event::LuaEventListener(sol::protected_function)>());
    }
};