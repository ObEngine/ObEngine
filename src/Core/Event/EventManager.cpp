#include <Event/EventManager.hpp>

namespace obe::event
{
    EventManager::EventManager()
    {
        debug::Log->debug("<EventManager> Initializing EventManager");
        m_chrono.start();
    }

    void EventManager::update()
    {
        debug::Log->trace("<EventManager> Updating EventManager");
        for (const auto& scheduler : m_schedulers)
        {
            if (scheduler->m_state == CallbackSchedulerState::Ready)
            {
                const time::TimeUnit elapsed = time::epoch() - scheduler->m_start;
                if ((scheduler->m_wait && elapsed >= scheduler->m_after)
                    || (scheduler->m_repeat && elapsed >= scheduler->m_every))
                {
                    scheduler->execute();
                }
            }
        }
        m_schedulers.erase(
            std::ranges::remove_if(m_schedulers,
                [](auto& scheduler) { return scheduler->m_state == CallbackSchedulerState::Done; }).begin(),
            m_schedulers.end());
    }

    void EventManager::clear()
    {
        debug::Log->debug("<EventManager> Clearing EventManager");
        m_chrono.stop();
        m_namespaces.clear(); // TODO: Clean EventNamespaces
        m_chrono.reset();
        m_chrono.start();
        m_schedulers.clear();
    }

    EventNamespace& EventManager::create_namespace(const std::string& event_namespace)
    {
        debug::Log->debug("<EventNamespace> Creating EventNamespace '{}'", event_namespace);
        if (!m_namespaces.contains(event_namespace))
        {
            const auto insertion_result = m_namespaces.emplace(
                event_namespace, std::make_unique<EventNamespace>(event_namespace));
            return *insertion_result.first->second;
        }
        throw Exceptions::EventNamespaceAlreadyExists(event_namespace, EXC_INFO);
    }

    EventNamespace& EventManager::join_namespace(const std::string& event_namespace)
    {
        debug::Log->debug("<EventNamespace> Joining EventNamespace '{}'", event_namespace);
        if (const auto namespace_ptr = m_namespaces.find(event_namespace);
            namespace_ptr != m_namespaces.end())
        {
            if (namespace_ptr->second->is_joinable())
            {
                return *namespace_ptr->second;
            }
            throw Exceptions::EventNamespaceNotJoinable(event_namespace, EXC_INFO);
        }

        throw Exceptions::UnknownEventNamespace(event_namespace, this->get_all_namespaces_names(), EXC_INFO);
    }

    EventNamespaceView EventManager::get_namespace(const std::string& event_namespace)
    {
        if (const auto namespace_ptr = m_namespaces.find(event_namespace);
            namespace_ptr != m_namespaces.end())
        {
            return namespace_ptr->second->get_view();
        }
        throw Exceptions::UnknownEventNamespace(
            event_namespace, this->get_all_namespaces_names(), EXC_INFO);
    }

    std::vector<std::string> EventManager::get_all_namespaces_names() const
    {
        std::vector<std::string> all_names;
        all_names.reserve(m_namespaces.size());
        for (const auto& event_namespace : m_namespaces)
        {
            all_names.push_back(event_namespace.first);
        }
        return all_names;
    }

    CallbackScheduler& EventManager::schedule()
    {
        m_schedulers.push_back(std::make_unique<CallbackScheduler>());
        return *m_schedulers.back();
    }

    vili::node EventManager::dump_profiler_results() const
    {
        vili::node result = vili::object {};
        for (const auto& namespace_itr : m_namespaces)
        {
            debug::Log->debug("Profiling EventNamespace '{}'", namespace_itr.first);
            result.emplace(namespace_itr.first, vili::object {});
            for (const auto& group_name : namespace_itr.second->get_all_groups_names())
            {
                debug::Log->debug("Namespace group {}", group_name);
                result.at(namespace_itr.first)
                    .emplace(
                        group_name, namespace_itr.second->get_group(group_name).get_profiler_results());
            }
        }
        return result;
    }
} // namespace obe::event
