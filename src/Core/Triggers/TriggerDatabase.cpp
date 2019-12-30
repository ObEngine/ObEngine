#include <vili/ErrorHandler.hpp>

#include <Triggers/TriggerDatabase.hpp>

namespace obe::Triggers
{
    TriggerDatabase::TriggerDatabase()
        : Registrable("TriggerDatabase")
    {
        Debug::Log->debug("<TriggerDatabase> Initialising TriggerDatabase");
        this->createNamespace("Global");
        m_databaseChrono.start();
    }

    std::weak_ptr<Trigger> TriggerDatabase::getTrigger(const std::string& groupNamespace,
        const std::string& triggerGroupName, const std::string& triggerName)
    {
        if (m_allTriggers.find(groupNamespace) != m_allTriggers.end())
        {
            if (m_allTriggers[groupNamespace].find(triggerGroupName)
                != m_allTriggers[groupNamespace].end())
                return m_allTriggers[groupNamespace][triggerGroupName]->getTrigger(triggerName);
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerDatabase.UnknownCustomTriggerGroup",
                { { "function", "getTrigger" }, { "group", triggerGroupName },
                    { "nsp", groupNamespace } });
        }
        throw aube::ErrorHandler::Raise("ObEngine.Trigger.TriggerDatabase.UnknownNamespace",
            { { "function", "getTrigger" }, { "nsp", groupNamespace } });
    }

    void TriggerDatabase::createNamespace(const std::string& groupNamespace)
    {
        Debug::Log->debug(
            "<TriggerDatabase> Creating Namespace {0} in TriggerDatabase", groupNamespace);
        if (m_allTriggers.size() == 0)
            m_allTriggers[groupNamespace] = std::map<std::string, std::unique_ptr<TriggerGroup>>();
        else
        {
            if (m_allTriggers.find(groupNamespace) == m_allTriggers.end())
                m_allTriggers[groupNamespace]
                    = std::map<std::string, std::unique_ptr<TriggerGroup>>();
            else
                throw aube::ErrorHandler::Raise(
                    "ObEngine.Triggers.TriggerDatabase.NamespaceAlreadyExists",
                    { { "nsp", groupNamespace } });
        }
    }

    TriggerGroup* TriggerDatabase::createTriggerGroup(
        const std::string& groupNamespace, const std::string& triggerGroupName)
    {
        Debug::Log->debug("<TriggerDatabase> Creating TriggerGroup {0} in Namespace {1}",
            triggerGroupName, groupNamespace);
        if (m_allTriggers.find(groupNamespace) != m_allTriggers.end())
        {
            if (m_allTriggers[groupNamespace].find(triggerGroupName)
                == m_allTriggers[groupNamespace].end())
            {
                m_allTriggers[groupNamespace][triggerGroupName]
                    = std::make_unique<TriggerGroup>(groupNamespace, triggerGroupName);
                return m_allTriggers[groupNamespace][triggerGroupName].get();
            }
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerDatabase.TriggerGroupAlreadyExists",
                { { "group", triggerGroupName }, { "nsp", groupNamespace } });
        }
        throw aube::ErrorHandler::Raise("ObEngine.Triggers.TriggerDatabase.UnknownNamespace",
            { { "function", "createTriggerGroup" }, { "nsp", groupNamespace } });
    }

    TriggerGroup* TriggerDatabase::joinTriggerGroup(
        const std::string& groupNamespace, const std::string& triggerGroupName)
    {
        Debug::Log->debug("<TriggerDatabase> Joining TriggerGroup {0} in Namespace {1}",
            triggerGroupName, groupNamespace);
        if (m_allTriggers.find(groupNamespace) != m_allTriggers.end())
        {
            if (m_allTriggers[groupNamespace].find(triggerGroupName)
                    != m_allTriggers[groupNamespace].end()
                && m_allTriggers[groupNamespace][triggerGroupName]->isJoinable())
                return m_allTriggers[groupNamespace][triggerGroupName].get();
            if (m_allTriggers[groupNamespace].find(triggerGroupName)
                != m_allTriggers[groupNamespace].end())
            {
                throw aube::ErrorHandler::Raise(
                    "ObEngine.Triggers.TriggerDatabase.TriggerGroupNotJoinable",
                    { { "group", triggerGroupName }, { "nsp", groupNamespace } });
            }
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerDatabase.UnknownCustomTriggerGroup",
                { { "function", "joinTriggerGroup" }, { "group", triggerGroupName },
                    { "nsp", groupNamespace } });
        }
        throw aube::ErrorHandler::Raise("ObEngine.Triggers.TriggerDatabase.UnknownNamespace",
            { { "function", "joinTriggerGroup" }, { "nsp", groupNamespace } });
    }

    void TriggerDatabase::removeNamespace(const std::string& namespaceId)
    {
        Debug::Log->debug("<TriggerDatabase> Removing Trigger Namespace {0}", namespaceId);
        if (m_allTriggers.find(namespaceId) != m_allTriggers.end())
        {
            Debug::Log->trace(
                "<TriggerDatabase> Found Trigger Namespace {0}, removing it...", namespaceId);
            m_allTriggers.erase(m_allTriggers.find(namespaceId));
        }
        else
            throw aube::ErrorHandler::Raise("ObEngine.Triggers.TriggerDatabase.UnknownNamespace",
                { { "function", "removeNamespace" }, { "nsp", namespaceId } });
    }

    std::vector<std::string> TriggerDatabase::getAllTriggersNameFromTriggerGroup(
        const std::string& groupNamespace, const std::string& triggerGroupName)
    {
        if (m_allTriggers.find(groupNamespace) != m_allTriggers.end())
        {
            if (m_allTriggers[groupNamespace].find(triggerGroupName)
                != m_allTriggers[groupNamespace].end())
                return m_allTriggers[groupNamespace][triggerGroupName]->getAllTriggersName();
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerDatabase.UnknownCustomTriggerGroup",
                { { "function", "getAllTriggersNameFromTriggerGroup" },
                    { "group", triggerGroupName }, { "nsp", groupNamespace } });
        }
        throw aube::ErrorHandler::Raise("ObEngine.Triggers.TriggerDatabase.UnknownNamespace",
            { { "function", "getAllTriggersNameFromTriggerGroup" }, { "nsp", groupNamespace } });
    }

    std::vector<std::string> TriggerDatabase::getAllTriggersGroupNames(
        const std::string& namespaceName)
    {
        if (m_allTriggers.find(namespaceName) != m_allTriggers.end())
        {
            std::vector<std::string> allNames;
            for (auto& nsp : m_allTriggers[namespaceName])
            {
                allNames.push_back(nsp.first);
            }
            return allNames;
        }
        else
            throw aube::ErrorHandler::Raise("ObEngine.Triggers.TriggerDatabase.UnknownNamespace",
                { { "function", "getAllTriggersGroupNames" }, { "nsp", namespaceName } });
    }

    void TriggerDatabase::removeTriggerGroup(TriggerGroup* trgGroup)
    {
        Debug::Log->debug("<TriggerDatabase> Removing TriggerGroup {0} from Namespace {1}",
            trgGroup->getName(), trgGroup->getNamespace());
        m_allTriggers[trgGroup->getNamespace()].erase(trgGroup->getName());
    }

    bool TriggerDatabase::doesTriggerGroupExists(
        const std::string& groupNamespace, const std::string& triggerGroupName)
    {
        if (m_allTriggers.find(groupNamespace) != m_allTriggers.end())
        {
            if (m_allTriggers[groupNamespace].find(triggerGroupName)
                == m_allTriggers[groupNamespace].end())
                return false;
            return true;
        }
        throw aube::ErrorHandler::Raise("ObEngine.Triggers.TriggerDatabase.UnknownNamespace",
            { { "function", "doesTriggerGroupExists" }, { "nsp", groupNamespace } });
    }

    void TriggerDatabase::update()
    {
        Debug::Log->trace("<TriggerDatabase> Updating TriggerDatabase");
        for (auto it = m_allTriggers.begin(); it != m_allTriggers.end(); ++it)
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                if (it2->second->m_delayedTriggers.size() != 0)
                {
                    for (int i = 0; i < it2->second->m_delayedTriggers.size(); i++)
                    {
                        it2->second->m_delayedTriggers[i]->m_delaytarget
                            = m_databaseChrono.getTime()
                            + it2->second->m_delayedTriggers[i]->m_delay;
                        m_delayedTriggers.push_back(move(it2->second->m_delayedTriggers[i]));
                    }
                    it2->second->m_delayedTriggers.clear();
                }
            }
        }
        std::vector<int> triggeredDelayedTriggers;
        for (int i = 0; i < m_delayedTriggers.size(); i++)
        {
            if (m_delayedTriggers[i]->m_delaytarget <= m_databaseChrono.getTime())
            {
                m_delayedTriggers[i]->m_trigger->m_enabled = true;
                triggeredDelayedTriggers.push_back(i);
            }
        }
        for (int i = 0; i < triggeredDelayedTriggers.size(); i++)
        {
            m_delayedTriggers.erase(m_delayedTriggers.begin() + triggeredDelayedTriggers[i]);
        }
    }

    void TriggerDatabase::clear()
    {
        Debug::Log->debug("<TriggerDatabase> Clearing TriggerDatabase");
        m_delayedTriggers.clear();
        m_databaseChrono.stop();
        m_allTriggers.clear();
        m_databaseChrono.start();
        // Need to delete Map-only stuff !!
    }
} // namespace obe::Triggers