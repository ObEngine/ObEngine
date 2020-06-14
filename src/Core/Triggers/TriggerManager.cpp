#include <Triggers/Exceptions.hpp>
#include <Triggers/TriggerManager.hpp>

namespace obe::Triggers
{
    TriggerManager::TriggerManager(sol::state_view lua)
        : m_lua(lua)
    {
        Debug::Log->debug("<TriggerManager> Initializing TriggerManager");
        m_databaseChrono.start();
    }

    std::weak_ptr<Trigger> TriggerManager::getTrigger(
        const std::string& space, const std::string& group, const std::string& trigger)
    {
        if (m_allTriggers.find(space) != m_allTriggers.end())
        {
            if (m_allTriggers[space].find(group) != m_allTriggers[space].end())
                return m_allTriggers[space][group].lock()->get(trigger);
            auto& selectedNamespace = m_allTriggers[space];
            std::vector<std::string> triggerGroupNames(selectedNamespace.size());
            std::transform(selectedNamespace.begin(), selectedNamespace.end(),
                triggerGroupNames.begin(), [](const auto& pair) { return pair.first; });
            throw Exceptions::UnknownTriggerGroup(
                space, group, triggerGroupNames, EXC_INFO);
        }
        std::vector<std::string> namespaces(m_allTriggers.size());
        std::transform(m_allTriggers.begin(), m_allTriggers.end(), namespaces.begin(),
            [](const auto& pair) { return pair.first; });
        throw Exceptions::UnknownTriggerNamespace(space, namespaces, EXC_INFO);
    }

    void TriggerManager::createNamespace(const std::string& space)
    {
        Debug::Log->debug(
            "<TriggerManager> Creating Namespace {0} in TriggerManager", space);
        if (m_allTriggers.size() == 0)
            m_allTriggers[space] = std::map<std::string, std::weak_ptr<TriggerGroup>>();
        else
        {
            if (m_allTriggers.find(space) == m_allTriggers.end())
                m_allTriggers[space]
                    = std::map<std::string, std::weak_ptr<TriggerGroup>>();
            else
            {
                throw Exceptions::TriggerNamespaceAlreadyExists(space, EXC_INFO);
            }
        }
    }

    TriggerGroupPtr TriggerManager::createTriggerGroup(
        const std::string& space, const std::string& group)
    {
        Debug::Log->debug(
            "<TriggerManager> Creating TriggerGroup {0} in Namespace {1}", group, space);
        if (m_allTriggers.find(space) != m_allTriggers.end())
        {
            if (m_allTriggers[space].find(group) == m_allTriggers[space].end())
            {
                TriggerGroupPtr newGroup(new TriggerGroup(m_lua, space, group),
                    [this](TriggerGroup* ptr) { this->removeTriggerGroup(ptr); });
                m_allTriggers[space][group] = newGroup;
                return newGroup;
            }
            throw Exceptions::TriggerGroupAlreadyExists(space, group, EXC_INFO);
        }
        std::vector<std::string> namespaces(m_allTriggers.size());
        std::transform(m_allTriggers.begin(), m_allTriggers.end(), namespaces.begin(),
            [](const auto& pair) { return pair.first; });
        throw Exceptions::UnknownTriggerNamespace(space, namespaces, EXC_INFO);
    }

    TriggerGroupPtr TriggerManager::joinTriggerGroup(
        const std::string& space, const std::string& group)
    {
        Debug::Log->debug(
            "<TriggerManager> Joining TriggerGroup {0} in Namespace {1}", group, space);
        if (m_allTriggers.find(space) != m_allTriggers.end())
        {
            if (m_allTriggers[space].find(group) != m_allTriggers[space].end()
                && m_allTriggers[space][group].lock()->isJoinable())
                return TriggerGroupPtr(m_allTriggers[space][group].lock());
            if (m_allTriggers[space].find(group) != m_allTriggers[space].end())
            {
                throw Exceptions::TriggerGroupNotJoinable(space, group, EXC_INFO);
            }
            auto& selectedNamespace = m_allTriggers[space];
            std::vector<std::string> triggerGroupNames(selectedNamespace.size());
            std::transform(selectedNamespace.begin(), selectedNamespace.end(),
                triggerGroupNames.begin(), [](const auto& pair) { return pair.first; });
            throw Exceptions::UnknownTriggerGroup(
                space, group, triggerGroupNames, EXC_INFO);
        }
        std::vector<std::string> namespaces(m_allTriggers.size());
        std::transform(m_allTriggers.begin(), m_allTriggers.end(), namespaces.begin(),
            [](const auto& pair) { return pair.first; });
        throw Exceptions::UnknownTriggerNamespace(space, namespaces, EXC_INFO);
    }

    void TriggerManager::removeNamespace(const std::string& space)
    {
        Debug::Log->debug("<TriggerManager> Removing Trigger Namespace {0}", space);
        if (const auto spaceItr = m_allTriggers.find(space);
            spaceItr != m_allTriggers.end())
        {
            Debug::Log->trace(
                "<TriggerManager> Found Trigger Namespace {0}, removing it...", space);
            m_allTriggers.erase(spaceItr);
            return;
        }
        std::vector<std::string> namespaces(m_allTriggers.size());
        std::transform(m_allTriggers.begin(), m_allTriggers.end(), namespaces.begin(),
            [](const auto& pair) { return pair.first; });
        throw Exceptions::UnknownTriggerNamespace(space, namespaces, EXC_INFO);
    }

    std::vector<std::string> TriggerManager::getAllTriggersNameFromTriggerGroup(
        const std::string& space, const std::string& group)
    {
        if (m_allTriggers.find(space) != m_allTriggers.end())
        {
            if (m_allTriggers[space].find(group) != m_allTriggers[space].end())
                return m_allTriggers[space][group].lock()->getTriggersNames();
            auto& selectedNamespace = m_allTriggers[space];
            std::vector<std::string> triggerGroupNames(selectedNamespace.size());
            std::transform(selectedNamespace.begin(), selectedNamespace.end(),
                triggerGroupNames.begin(), [](const auto& pair) { return pair.first; });
            throw Exceptions::UnknownTriggerGroup(
                space, group, triggerGroupNames, EXC_INFO);
        }
        std::vector<std::string> namespaces(m_allTriggers.size());
        std::transform(m_allTriggers.begin(), m_allTriggers.end(), namespaces.begin(),
            [](const auto& pair) { return pair.first; });
        throw Exceptions::UnknownTriggerNamespace(space, namespaces, EXC_INFO);
    }

    std::vector<std::string> TriggerManager::getAllTriggersGroupNames(
        const std::string& space)
    {
        if (m_allTriggers.find(space) != m_allTriggers.end())
        {
            std::vector<std::string> allNames;
            for (auto& spaceIt : m_allTriggers[space])
            {
                allNames.push_back(spaceIt.first);
            }
            return allNames;
        }
        std::vector<std::string> namespaces(m_allTriggers.size());
        std::transform(m_allTriggers.begin(), m_allTriggers.end(), namespaces.begin(),
            [](const auto& pair) { return pair.first; });
        throw Exceptions::UnknownTriggerNamespace(space, namespaces, EXC_INFO);
    }

    void TriggerManager::removeTriggerGroup(TriggerGroup* trgGroup)
    {
        Debug::Log->debug("<TriggerManager> Removing TriggerGroup {0} from Namespace {1}",
            trgGroup->getName(), trgGroup->getNamespace());
        m_allTriggers[trgGroup->getNamespace()].erase(trgGroup->getName());
    }

    bool TriggerManager::doesTriggerGroupExists(
        const std::string& space, const std::string& group)
    {
        if (m_allTriggers.find(space) != m_allTriggers.end())
        {
            if (m_allTriggers[space].find(group) == m_allTriggers[space].end())
                return false;
            return true;
        }
        std::vector<std::string> namespaces(m_allTriggers.size());
        std::transform(m_allTriggers.begin(), m_allTriggers.end(), namespaces.begin(),
            [](const auto& pair) { return pair.first; });
        throw Exceptions::UnknownTriggerNamespace(space, namespaces, EXC_INFO);
    }

    void TriggerManager::update()
    {
        Debug::Log->trace("<TriggerManager> Updating TriggerManager");
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

    void TriggerManager::clear()
    {
        Debug::Log->debug("<TriggerManager> Clearing TriggerManager");
        m_databaseChrono.stop();
        m_allTriggers.clear();
        m_databaseChrono.start();
        // Need to delete Map-only stuff !!
    }

    CallbackScheduler& TriggerManager::schedule()
    {
        m_schedulers.push_back(std::make_unique<CallbackScheduler>(*this));
        return *m_schedulers.back().get();
    }
} // namespace obe::Triggers