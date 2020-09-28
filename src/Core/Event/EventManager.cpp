#include <Event/EventManager.hpp>
#include <Event/Exceptions.hpp>

namespace obe::Event
{
    EventManager::EventManager()
    {
        Debug::Log->debug("<EventManager> Initializing EventManager");
        m_chrono.start();
    }

    void EventManager::update()
    {
        Debug::Log->trace("<EventManager> Updating EventManager");
        for (auto& scheduler : m_schedulers)
        {
            if (scheduler->m_state == CallbackSchedulerState::Ready)
            {
                const Time::TimeUnit elapsed = Time::epoch() - scheduler->m_start;
                if ((scheduler->m_wait && elapsed >= scheduler->m_after)
                    || (scheduler->m_repeat && elapsed >= scheduler->m_every))
                {
                    scheduler->execute();
                }
            }
        }
        m_schedulers.erase(std::remove_if(m_schedulers.begin(), m_schedulers.end(),
                               [](auto& scheduler) {
                                   return scheduler->m_state
                                       == CallbackSchedulerState::Done;
                               }),
            m_schedulers.end());
    }

    void EventManager::clear()
    {
        Debug::Log->debug("<EventManager> Clearing EventManager");
        m_chrono.stop();
        m_namespaces.clear(); // TODO: Clean EventNamespaces
        m_chrono.reset();
        m_chrono.start();
    }

    EventNamespace& EventManager::createNamespace(const std::string& eventNamespace)
    {
        if (!m_namespaces.count(eventNamespace))
        {
            const auto insertionResult = m_namespaces.emplace(
                eventNamespace, std::make_unique<EventNamespace>(eventNamespace));
            return *insertionResult.first->second;
        }
        throw Exceptions::EventNamespaceAlreadyExists(eventNamespace, EXC_INFO);
    }

    CallbackScheduler& EventManager::schedule()
    {
        m_schedulers.push_back(std::make_unique<CallbackScheduler>());
        return *m_schedulers.back();
    }

    vili::node EventManager::dumpProfilerResults() const
    {
        vili::node result = vili::object {};
        /*for (auto itr : m_root->getEvents())
        {
            Debug::Log->debug("Profiling EventNamespace '{}'", itr.first);
            result.emplace(itr.first, vili::object {});
            for (auto itr2 : itr.second)
            {
                Debug::Log->debug("Namespace group {}", itr2.first);
                result.at(itr.first).emplace(
                    itr2.first, itr2.second.lock()->getProfilerResults());
            }
        }*/
        return result;
    }
} // namespace obe::Event