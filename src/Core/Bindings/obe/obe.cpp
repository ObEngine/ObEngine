#include <Bindings/obe/obe.hpp>

#include <Exception.hpp>
#include <ObEngineCore.hpp>

#include <Bindings/Config.hpp>

namespace obe::Bindings
{
    void LoadClassDebugInfo(sol::state_view state)
    {
        sol::table obeNamespace = state["obe"].get<sol::table>();
        sol::usertype<obe::DebugInfo> bindDebugInfo = obeNamespace.new_usertype<
            obe::DebugInfo>("DebugInfo", sol::call_constructor,
            sol::constructors<obe::DebugInfo(std::string_view, int, std::string_view)>());
        bindDebugInfo["file"] = &obe::DebugInfo::file;
        bindDebugInfo["line"] = &obe::DebugInfo::line;
        bindDebugInfo["function"] = &obe::DebugInfo::function;
    }
    void LoadClassException(sol::state_view state)
    {
        sol::table obeNamespace = state["obe"].get<sol::table>();
        sol::usertype<obe::Exception> bindException
            = obeNamespace.new_usertype<obe::Exception>("Exception",
                sol::call_constructor,
                sol::constructors<obe::Exception(std::string, obe::DebugInfo)>());
        bindException["what"] = &obe::Exception::what;
        bindException["nest"] = &obe::Exception::nest;
    }
    void LoadFunctionInitEngine(sol::state_view state)
    {
        sol::table obeNamespace = state["obe"].get<sol::table>();
        obeNamespace.set_function("InitEngine", obe::InitEngine);
    }
};