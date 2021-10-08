#include <Bindings/obe/Event/Event.hpp>

#include <Event/CallbackScheduler.hpp>
#include <Event/Event.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventListener.hpp>
#include <Event/EventManager.hpp>
#include <Event/EventNamespace.hpp>

#include <Bindings/Config.hpp>

namespace obe::Event::Bindings
{
    void LoadEnumCallbackSchedulerState(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        EventNamespace.new_enum<obe::Event::CallbackSchedulerState>("CallbackSchedulerState",
            { { "Standby", obe::Event::CallbackSchedulerState::Standby },
                { "Ready", obe::Event::CallbackSchedulerState::Ready },
                { "Done", obe::Event::CallbackSchedulerState::Done } });
    }
    void LoadEnumListenerChangeState(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        EventNamespace.new_enum<obe::Event::ListenerChangeState>("ListenerChangeState",
            { { "Added", obe::Event::ListenerChangeState::Added },
                { "Removed", obe::Event::ListenerChangeState::Removed } });
    }
    void LoadClassCallbackProfiler(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::CallbackProfiler> bindCallbackProfiler
            = EventNamespace.new_usertype<obe::Event::CallbackProfiler>(
                "CallbackProfiler", sol::call_constructor, sol::default_constructor);
        bindCallbackProfiler["hits"] = &obe::Event::CallbackProfiler::hits;
        bindCallbackProfiler["time"] = &obe::Event::CallbackProfiler::time;
        bindCallbackProfiler["min"] = &obe::Event::CallbackProfiler::min;
        bindCallbackProfiler["max"] = &obe::Event::CallbackProfiler::max;
    }
    void LoadClassCallbackScheduler(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::CallbackScheduler> bindCallbackScheduler
            = EventNamespace.new_usertype<obe::Event::CallbackScheduler>("CallbackScheduler",
                sol::call_constructor, sol::constructors<obe::Event::CallbackScheduler()>());
        bindCallbackScheduler["after"] = &obe::Event::CallbackScheduler::after;
        bindCallbackScheduler["every"] = &obe::Event::CallbackScheduler::every;
        bindCallbackScheduler["loop"] = &obe::Event::CallbackScheduler::repeat;
        bindCallbackScheduler["run"] = &obe::Event::CallbackScheduler::run;
        bindCallbackScheduler["stop"] = &obe::Event::CallbackScheduler::stop;
    }
    void LoadClassEventBase(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::EventBase> bindEventBase
            = EventNamespace.new_usertype<obe::Event::EventBase>("EventBase", sol::call_constructor,
                sol::constructors<obe::Event::EventBase(const std::string&, const std::string&),
                    obe::Event::EventBase(const std::string&, const std::string&, bool)>());
        bindEventBase["getState"] = &obe::Event::EventBase::getState;
        bindEventBase["getName"] = &obe::Event::EventBase::getName;
        bindEventBase["getIdentifier"] = &obe::Event::EventBase::getIdentifier;
        bindEventBase["addExternalListener"] = &obe::Event::EventBase::addExternalListener;
        bindEventBase["removeExternalListener"] = &obe::Event::EventBase::removeExternalListener;
        bindEventBase["getProfiler"] = &obe::Event::EventBase::getProfiler;
    }
    void LoadClassEventGroup(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::EventGroup> bindEventGroup = EventNamespace.new_usertype<
            obe::Event::EventGroup>("EventGroup", sol::call_constructor,
            sol::constructors<obe::Event::EventGroup(const std::string&, const std::string&)>());
        bindEventGroup["getView"] = &obe::Event::EventGroup::getView;
        bindEventGroup["setJoinable"] = &obe::Event::EventGroup::setJoinable;
        bindEventGroup["isJoinable"] = &obe::Event::EventGroup::isJoinable;
        bindEventGroup["get"] = sol::overload(
            static_cast<obe::Event::EventBase& (obe::Event::EventGroup::*)(const std::string&)
                    const>(&obe::Event::EventGroup::get));
        bindEventGroup["remove"] = &obe::Event::EventGroup::remove;
        bindEventGroup["getEventsNames"] = &obe::Event::EventGroup::getEventsNames;
        bindEventGroup["getEvents"] = &obe::Event::EventGroup::getEvents;
        bindEventGroup["getIdentifier"] = &obe::Event::EventGroup::getIdentifier;
        bindEventGroup["getName"] = &obe::Event::EventGroup::getName;
        bindEventGroup["onAddListener"] = &obe::Event::EventGroup::onAddListener;
        bindEventGroup["onRemoveListener"] = &obe::Event::EventGroup::onRemoveListener;
        bindEventGroup["getProfilerResults"] = &obe::Event::EventGroup::getProfilerResults;
    }
    void LoadClassEventGroupView(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::EventGroupView> bindEventGroupView
            = EventNamespace.new_usertype<obe::Event::EventGroupView>("EventGroupView",
                sol::call_constructor,
                sol::constructors<obe::Event::EventGroupView(const obe::Event::EventGroup&)>());
        bindEventGroupView["getEventsNames"] = &obe::Event::EventGroupView::getEventsNames;
        bindEventGroupView["getEvents"] = &obe::Event::EventGroupView::getEvents;
        bindEventGroupView["getIdentifier"] = &obe::Event::EventGroupView::getIdentifier;
        bindEventGroupView["getName"] = &obe::Event::EventGroupView::getName;
        bindEventGroupView["isJoinable"] = &obe::Event::EventGroupView::isJoinable;
        bindEventGroupView["get"] = sol::overload(
            static_cast<obe::Event::EventBase& (obe::Event::EventGroupView::*)(const std::string&)
                    const>(&obe::Event::EventGroupView::get));
        bindEventGroupView["getProfilerResults"] = &obe::Event::EventGroupView::getProfilerResults;
    }
    void LoadClassEventManager(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::EventManager> bindEventManager
            = EventNamespace.new_usertype<obe::Event::EventManager>("EventManager",
                sol::call_constructor, sol::constructors<obe::Event::EventManager()>());
        bindEventManager["update"] = &obe::Event::EventManager::update;
        bindEventManager["clear"] = &obe::Event::EventManager::clear;
        bindEventManager["createNamespace"] = &obe::Event::EventManager::createNamespace;
        bindEventManager["getNamespace"] = &obe::Event::EventManager::getNamespace;
        bindEventManager["schedule"] = &obe::Event::EventManager::schedule;
        bindEventManager["dumpProfilerResults"] = &obe::Event::EventManager::dumpProfilerResults;
    }
    void LoadClassEventNamespace(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::EventNamespace> bindEventNamespace
            = EventNamespace.new_usertype<obe::Event::EventNamespace>("EventNamespace",
                sol::call_constructor,
                sol::constructors<obe::Event::EventNamespace(const std::string&)>());
        bindEventNamespace["createGroup"] = &obe::Event::EventNamespace::createGroup;
        bindEventNamespace["joinGroup"] = &obe::Event::EventNamespace::joinGroup;
        bindEventNamespace["getGroup"] = &obe::Event::EventNamespace::getGroup;
        bindEventNamespace["getAllGroupsNames"] = &obe::Event::EventNamespace::getAllGroupsNames;
        bindEventNamespace["removeGroup"] = &obe::Event::EventNamespace::removeGroup;
        bindEventNamespace["doesGroupExists"] = &obe::Event::EventNamespace::doesGroupExists;
        bindEventNamespace["getView"] = &obe::Event::EventNamespace::getView;
    }
    void LoadClassEventNamespaceView(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::EventNamespaceView> bindEventNamespaceView
            = EventNamespace.new_usertype<obe::Event::EventNamespaceView>("EventNamespaceView",
                sol::call_constructor,
                sol::constructors<obe::Event::EventNamespaceView(
                    const obe::Event::EventNamespace&)>());
        bindEventNamespaceView["getGroup"] = &obe::Event::EventNamespaceView::getGroup;
        bindEventNamespaceView["getAllGroupsNames"]
            = &obe::Event::EventNamespaceView::getAllGroupsNames;
        bindEventNamespaceView["doesGroupExists"]
            = &obe::Event::EventNamespaceView::doesGroupExists;
    }
    void LoadClassLuaEventListener(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::LuaEventListener> bindLuaEventListener
            = EventNamespace.new_usertype<obe::Event::LuaEventListener>("LuaEventListener",
                sol::call_constructor,
                sol::constructors<obe::Event::LuaEventListener(sol::protected_function)>());
    }
    void LoadClassScopeProfiler(sol::state_view state)
    {
        sol::table EventNamespace = state["obe"]["Event"].get<sol::table>();
        sol::usertype<obe::Event::ScopeProfiler> bindScopeProfiler
            = EventNamespace.new_usertype<obe::Event::ScopeProfiler>("ScopeProfiler",
                sol::call_constructor,
                sol::constructors<obe::Event::ScopeProfiler(obe::Event::CallbackProfiler&)>());
    }
};
