#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Utils/TypeUtils.hpp>


#define StartCheck if (false) {}
#define AffectIfCorrectType(type) else if(affectIfCorrectType<type>(lua,parameter)){}
#define _AffectIfCorrectType(type, ntype) else if(affectIfCorrectType<type, ntype>(lua,parameter)){}
#define EndCheck else { return parameter.first; }

namespace obe
{
    namespace Triggers
    {
        template <typename T>
        bool affectIfCorrectType(kaguya::State& lua, const std::pair<std::string, std::pair<std::string, Types::Any>>& parameter)
        {
            if (parameter.second.first == Utils::Type::getClassType<T>())
            {
                lua["cpp_param"][parameter.first] = parameter.second.second.as<T>();
                return true;
            }
            return false;
        }

        std::string injectParameters(Trigger& trigger, kaguya::State& lua)
        {
            for (auto& parameter : *trigger.getParameters())
            {
                StartCheck
                    AffectIfCorrectType(int)
                    AffectIfCorrectType(std::string)
                    AffectIfCorrectType(double)
                    AffectIfCorrectType(bool)
                    AffectIfCorrectType(std::vector<int>)
                    AffectIfCorrectType(std::vector<std::string>)
                    AffectIfCorrectType(std::vector<double>)
                    AffectIfCorrectType(std::vector<bool>)
                    _AffectIfCorrectType(std::map<int, int>)
                    _AffectIfCorrectType(std::map<int, std::string>)
                    _AffectIfCorrectType(std::map<int, double>)
                    _AffectIfCorrectType(std::map<int, bool>)
                    _AffectIfCorrectType(std::map<std::string, int>)
                    _AffectIfCorrectType(std::map<std::string, std::string>)
                    _AffectIfCorrectType(std::map<std::string, double>)
                    _AffectIfCorrectType(std::map<std::string, bool>)
                    _AffectIfCorrectType(std::map<double, int>)
                    _AffectIfCorrectType(std::map<double, std::string>)
                    _AffectIfCorrectType(std::map<double, double>)
                    _AffectIfCorrectType(std::map<double, bool>)
                    _AffectIfCorrectType(std::map<bool, int>)
                    _AffectIfCorrectType(std::map<bool, std::string>)
                    _AffectIfCorrectType(std::map<bool, double>)
                    _AffectIfCorrectType(std::map<bool, bool>)
                EndCheck
            }
            return "";
        }

        Trigger::Trigger(const TriggerGroup& parent, const std::string& name, bool startState, bool permanent)
        {
            m_triggerNamespace = parent.getNamespace();
            m_group = parent.getName();
            m_triggerName = name;
            m_permanent = permanent;
            m_enabled = startState;
        }

        bool Trigger::getState() const
        {
            return m_enabled;
        }

        bool Trigger::isPermanent() const
        {
            return m_permanent;
        }

        std::string Trigger::getGroup() const
        {
            return m_group;
        }

        std::string Trigger::getName() const
        {
            return m_triggerName;
        }

        std::string Trigger::getNamespace() const
        {
            return m_triggerNamespace;
        }

        std::map<std::string, std::pair<std::string, Types::Any>>* Trigger::getParameters()
        {
            return &m_triggerParameters;
        }

        void Trigger::clearParameters()
        {
            m_triggerParameters.clear();
        }
    }
}