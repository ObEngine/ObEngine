#include <Bindings/obe/obe.hpp>

#include <Exception.hpp>
#include <ObEngineCore.hpp>

#include <Bindings/Config.hpp>
#include <Config/Flags.hpp>

namespace obe::Bindings
{
    void LoadClassBaseException(sol::state_view state)
    {
        sol::table obeNamespace = state["obe"].get<sol::table>();
        sol::usertype<obe::BaseException> bindBaseException
            = obeNamespace.new_usertype<obe::BaseException>(
                "BaseException", sol::call_constructor, sol::constructors<obe::BaseException()>());
        bindBaseException["what"] = &obe::BaseException::what;
        bindBaseException["traceback"] = &obe::BaseException::traceback;
    }
    void LoadClassDebugInfo(sol::state_view state)
    {
        sol::table obeNamespace = state["obe"].get<sol::table>();
        sol::usertype<obe::DebugInfo> bindDebugInfo
            = obeNamespace.new_usertype<obe::DebugInfo>("DebugInfo", sol::call_constructor,
                sol::constructors<obe::DebugInfo(std::string_view, int, std::string_view)>());
        bindDebugInfo["file"] = &obe::DebugInfo::file;
        bindDebugInfo["line"] = &obe::DebugInfo::line;
        bindDebugInfo["function"] = &obe::DebugInfo::function;
    }
    void LoadFunctionGetTypeName(sol::state_view state)
    {
        sol::table obeNamespace = state["obe"].get<sol::table>();
    }
    void LoadFunctionInitEngine(sol::state_view state)
    {
        sol::table obeNamespace = state["obe"].get<sol::table>();
        obeNamespace.set_function("InitEngine", &obe::InitEngine);
    }
    void LoadGlobalObengineProduction(sol::state_view state)
    {
        sol::table obeNamespace = state["obe"].get<sol::table>();
        obeNamespace["OBENGINE_PRODUCTION"] = obe::Config::OBENGINE_PRODUCTION;
    }
};