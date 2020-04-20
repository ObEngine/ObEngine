#include <Bindings/System/Exceptions/Exceptions.hpp>

#include <System/Exceptions.hpp>

#include <sol/sol.hpp>

namespace obe::System::Exceptions::Bindings
{
    void LoadClassResourceNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["System"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::System::Exceptions::ResourceNotFound> bindResourceNotFound
            = ExceptionsNamespace.new_usertype<obe::System::Exceptions::ResourceNotFound>(
                "ResourceNotFound", sol::call_constructor,
                sol::constructors<obe::System::Exceptions::ResourceNotFound(
                    std::string_view, std::vector<std::string>, obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};