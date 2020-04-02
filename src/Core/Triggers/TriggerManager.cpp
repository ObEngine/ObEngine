#include <vili/ErrorHandler.hpp>

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
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerManager.UnknownCustomTriggerGroup",
                { { "function", "getTrigger" }, { "group", group },
                    { "namespace", space } });
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Trigger.TriggerManager.UnknownNamespace",
            { { "function", "getTrigger" }, { "namespace", space } });
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
                throw aube::ErrorHandler::Raise(
                    "ObEngine.Triggers.TriggerManager.NamespaceAlreadyExists",
                    { { "namespace", space } });
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
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerManager.TriggerGroupAlreadyExists",
                { { "group", group }, { "namespace", space } });
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Triggers.TriggerManager.UnknownNamespace",
            { { "function", "createTriggerGroup" }, { "namespace", space } });
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
                throw aube::ErrorHandler::Raise(
                    "ObEngine.Triggers.TriggerManager.TriggerGroupNotJoinable",
                    { { "group", group }, { "namespace", space } });
            }
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerManager.UnknownCustomTriggerGroup",
                { { "function", "joinTriggerGroup" }, { "group", group },
                    { "namespace", space } });
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Triggers.TriggerManager.UnknownNamespace",
            { { "function", "joinTriggerGroup" }, { "namespace", space } });
    }

    void TriggerManager::removeNamespace(const std::string& space)
    {
        Debug::Log->debug("<TriggerManager> Removing Trigger Namespace {0}", space);
        if (m_allTriggers.find(space) != m_allTriggers.end())
        {
            Debug::Log->trace(
                "<TriggerManager> Found Trigger Namespace {0}, removing it...", space);
            m_allTriggers.erase(m_allTriggers.find(space));
        }
        else
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerManager.UnknownNamespace",
                { { "function", "removeNamespace" }, { "namespace", space } });
    }

    std::vector<std::string> TriggerManager::getAllTriggersNameFromTriggerGroup(
        const std::string& space, const std::string& group)
    {
        if (m_allTriggers.find(space) != m_allTriggers.end())
        {
            if (m_allTriggers[space].find(group) != m_allTriggers[space].end())
                return m_allTriggers[space][group].lock()->getTriggersNames();
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerManager.UnknownCustomTriggerGroup",
                { { "function", "getAllTriggersNameFromTriggerGroup" },
                    { "group", group }, { "namespace", space } });
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.Triggers.TriggerManager.UnknownNamespace",
            { { "function", "getAllTriggersNameFromTriggerGroup" },
                { "namespace", space } });
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
        else
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerManager.UnknownNamespace",
                { { "function", "getAllTriggersGroupNames" }, { "namespace", space } });
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
        throw aube::ErrorHandler::Raise(
            "ObEngine.Triggers.TriggerManager.UnknownNamespace",
            { { "function", "doesTriggerGroupExists" }, { "namespace", space } });
    }

    void TriggerManager::update()
    {
        Debug::Log->trace("<TriggerManager> Updating TriggerManager");
    }

    void TriggerManager::clear()
    {
        Debug::Log->debug("<TriggerManager> Clearing TriggerManager");
        m_databaseChrono.stop();
        m_allTriggers.clear();
        m_databaseChrono.start();
        // Need to delete Map-only stuff !!
    }
} // namespace obe::Triggers