#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Utils/TypeUtils.hpp>


#define StartCheck if (false) {}
#define AffectIfCorrectType(...) else if (affectIfCorrectType<__VA_ARGS__>(lua,parameter)){}
#define EndCheck else { throw aube::ErrorHandler::Raise("ObEngine.Triggers.Trigger.BadInjection", { { "triggerName", triggerName }, { "parameterName", parameter.first} }); }

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

        void injectParameters(const std::string& triggerName, ParameterTable& parameters, kaguya::State& lua)
        {
            for (auto& parameter : parameters)
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
        }

        void Trigger::pushParameterFromLua(const std::string& name, kaguya::LuaRef parameter)
        {
            m_triggerParameters.back()[name] = std::pair<std::string, Types::Any>(Utils::Type::getObjectType(parameter), Types::Any(parameter));
        }

        Trigger::Trigger(TriggerGroup* parent, const std::string& name, bool startState, bool permanent)
        {
            m_parent = parent;
            m_enabled = startState;
        }

        bool Trigger::getState() const
        {
            return m_enabled;
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

        void Trigger::clear()
        {
            m_triggerParameters.clear();
        }
    }
}
