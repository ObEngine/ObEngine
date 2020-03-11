#include <vili/ErrorHandler.hpp>

#include <Debug/Logger.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Triggers/TriggerManager.hpp>

namespace obe::Triggers
{
    TriggerGroup::TriggerGroup(sol::state_view lua,
        const std::string& triggerGroupNamespace, const std::string& triggerGroupName)
        : m_lua(lua)
    {
        m_fromNsp = triggerGroupNamespace;
        m_name = triggerGroupName;
    }

    std::weak_ptr<Trigger> TriggerGroup::get(const std::string& triggerName)
    {
        if (m_triggerMap.find(triggerName) != m_triggerMap.end())
        {
            return m_triggerMap[triggerName];
        }
        throw aube::ErrorHandler::Raise("ObEngine.Triggers.TriggerGroup.UnknownTrigger",
            { { "function", "get" }, { "trigger", triggerName }, { "group", m_name } });
    }

    TriggerGroup& TriggerGroup::add(const std::string& triggerName)
    {
        Debug::Log->debug("<TriggerGroup> Add Trigger {0} to TriggerGroup {1}.{2}",
            triggerName, m_fromNsp, m_name);
        m_triggerMap[triggerName] = std::make_unique<Trigger>(*this, triggerName);
        return *this;
    }

    TriggerGroup& TriggerGroup::remove(const std::string& triggerName)
    {
        Debug::Log->debug("<TriggerGroup> Remove Trigger {0} from TriggerGroup {1}.{2}",
            triggerName, m_fromNsp, m_name);
        if (m_triggerMap.find(triggerName) != m_triggerMap.end())
            m_triggerMap.erase(triggerName);
        else
            throw aube::ErrorHandler::Raise(
                "ObEngine.Triggers.TriggerGroup.UnknownTrigger",
                { { "function", "remove" }, { "trigger", triggerName },
                    { "group", m_name } });
        return *this;
    }

    TriggerGroup& TriggerGroup::delay(
        const std::string& triggerName, Time::TimeUnit delay)
    {
        m_delayedTriggers.push_back(
            std::make_unique<TriggerDelay>(*m_triggerMap[triggerName].get(), delay));
        return *this;
    }

    TriggerGroup& TriggerGroup::trigger(const std::string& triggerName)
    {
        Debug::Log->trace("<TriggerGroup> Trigger {0} from TriggerGroup {1}.{2}",
            triggerName, m_fromNsp, m_name);
        m_triggerMap[triggerName]->execute();
        return *this;
    }

    void TriggerGroup::setJoinable(bool joinable)
    {
        m_joinable = joinable;
    }

    bool TriggerGroup::isJoinable() const
    {
        return m_joinable;
    }

    void TriggerGroup::pushParameterFromLua(const std::string& triggerName,
        const std::string& parameterName, const kaguya::LuaRef& parameter)
    {
        m_triggerMap[triggerName]->pushParameterFromLua(parameterName, parameter);
    }

    std::vector<std::string> TriggerGroup::getTriggersNames()
    {
        std::vector<std::string> returnVec;
        for (auto it = m_triggerMap.begin(); it != m_triggerMap.end(); ++it)
        {
            returnVec.push_back(it->first);
        }
        return returnVec;
    }

    std::vector<Trigger*> TriggerGroup::getTriggers()
    {
        std::vector<Trigger*> returnVec;
        for (auto it = m_triggerMap.begin(); it != m_triggerMap.end(); ++it)
        {
            returnVec.push_back(it->second.get());
        }
        return returnVec;
    }

    std::string TriggerGroup::getNamespace() const
    {
        return m_fromNsp;
    }

    std::string TriggerGroup::getName() const
    {
        return m_name;
    }
} // namespace obe::Triggers