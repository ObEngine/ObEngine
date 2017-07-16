#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Utils/TypeUtils.hpp>


#define StartCheck if (false) {}
#define AffectIfCorrectType(...) else if(affectIfCorrectType<__VA_ARGS__>(lua,parameter)){}
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
                    AffectIfCorrectType(std::map<int, int>)
                    AffectIfCorrectType(std::map<int, std::string>)
                    AffectIfCorrectType(std::map<int, double>)
                    AffectIfCorrectType(std::map<int, bool>)
                    AffectIfCorrectType(std::map<std::string, int>)
                    AffectIfCorrectType(std::map<std::string, std::string>)
                    AffectIfCorrectType(std::map<std::string, double>)
                    AffectIfCorrectType(std::map<std::string, bool>)
                    AffectIfCorrectType(std::map<double, int>)
                    AffectIfCorrectType(std::map<double, std::string>)
                    AffectIfCorrectType(std::map<double, double>)
                    AffectIfCorrectType(std::map<double, bool>)
                    AffectIfCorrectType(std::map<bool, int>)
                    AffectIfCorrectType(std::map<bool, std::string>)
                    AffectIfCorrectType(std::map<bool, double>)
                    AffectIfCorrectType(std::map<bool, bool>)
                EndCheck
            }
            return "";
        }

        Trigger::Trigger(TriggerGroup* parent, const std::string& name, bool startState, bool permanent)
        {
            m_parent = parent;
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
            return m_parent->getName();
        }

        std::string Trigger::getName() const
        {
            return m_name;
        }

        std::string Trigger::getNamespace() const
        {
            return m_parent->getNamespace();
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