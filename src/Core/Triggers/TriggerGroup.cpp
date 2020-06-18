#include <Debug/Logger.hpp>
#include <Triggers/Exceptions.hpp>
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

    TriggerGroup::~TriggerGroup()
    {
    }

    std::weak_ptr<Trigger> TriggerGroup::get(const std::string& triggerName)
    {
        if (m_triggerMap.find(triggerName) != m_triggerMap.end())
        {
            return m_triggerMap[triggerName];
        }
        throw Exceptions::UnknownTrigger(
            m_fromNsp, m_name, triggerName, this->getTriggersNames(), EXC_INFO);
    }

    TriggerGroup& TriggerGroup::add(const std::string& triggerName)
    {
        Debug::Log->debug("<TriggerGroup> Add Trigger {0} to TriggerGroup {1}.{2}",
            triggerName, m_fromNsp, m_name);
        m_triggerMap.emplace(triggerName, std::make_unique<Trigger>(*this, triggerName));
        return *this;
    }

    TriggerGroup& TriggerGroup::remove(const std::string& triggerName)
    {
        Debug::Log->debug("<TriggerGroup> Remove Trigger {0} from TriggerGroup {1}.{2}",
            triggerName, m_fromNsp, m_name);
        if (m_triggerMap.find(triggerName) != m_triggerMap.end())
            m_triggerMap.erase(triggerName);
        else
        {
            throw Exceptions::UnknownTrigger(
                m_fromNsp, m_name, triggerName, this->getTriggersNames(), EXC_INFO);
        }
        return *this;
    }

    TriggerGroup& TriggerGroup::trigger(const std::string& triggerName)
    {
        Debug::Log->trace("<TriggerGroup> Trigger {0} from TriggerGroup {1}.{2}",
            triggerName, m_fromNsp, m_name);
        this->get(triggerName).lock()->execute();
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
        const std::string& parameterName, sol::object parameter)
    {
        this->get(triggerName).lock()->pushParameterFromLua(parameterName, parameter);
    }

    std::vector<std::string> TriggerGroup::getTriggersNames()
    {
        std::vector<std::string> returnVec(m_triggerMap.size());
        std::transform(m_triggerMap.begin(), m_triggerMap.end(), returnVec.begin(),
            [](const auto& pair) { return pair.first; });
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

    void TriggerGroup::onRegister(
        const std::string& triggerName, std::function<void(const TriggerEnv&)> callback)
    {
        this->get(triggerName).lock()->onRegister(callback);
    }

    void TriggerGroup::onUnregister(
        const std::string& triggerName, std::function<void(const TriggerEnv&)> callback)
    {
        this->get(triggerName).lock()->onUnregister(callback);
    }

    vili::node TriggerGroup::getProfilerResults()
    {
        vili::node result = vili::object {};
        for (auto& [triggerName, trigger] : m_triggerMap)
        {
            const std::string fullName = m_name + "." + triggerName;
            Debug::Log->debug("Dumping {}", fullName);
            result[fullName] = vili::object {};
            Time::TimeUnit totalTime = 0;
            long long int totalHits = 0;
            result.at(fullName).emplace("callbacks", vili::object {});
            vili::node& callbacks = result.at(fullName).at("callbacks");
            for (const auto itr : trigger->m_profiler)
            {
                callbacks.emplace(itr.first, vili::object {});
                vili::node& callback = callbacks.at(itr.first);
                callback.emplace("time", itr.second.time);
                callback.emplace("hits", vili::integer(itr.second.hits));
                callback.emplace("min", itr.second.min);
                callback.emplace("max", itr.second.max);
                totalTime += itr.second.time;
                totalHits += itr.second.hits;
            }
            result.at(fullName).emplace("time", totalTime);
            result.at(fullName).emplace("hits", totalHits);
        }
        return result;
    }
} // namespace obe::Triggers