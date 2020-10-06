#include <Bindings/obe/Bindings/Exceptions/Exceptions.hpp>

#include <Bindings/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Bindings::Exceptions::Bindings
{
    void LoadClassBindingTreeNodeNotFound(sol::state_view state)
    {
        sol::table ExceptionsNamespace
            = state["obe"]["Bindings"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Bindings::Exceptions::BindingTreeNodeNotFound>
            bindBindingTreeNodeNotFound = ExceptionsNamespace.new_usertype<
                obe::Bindings::Exceptions::BindingTreeNodeNotFound>(
                "BindingTreeNodeNotFound", sol::call_constructor,
                sol::constructors<obe::Bindings::Exceptions::BindingTreeNodeNotFound(
                    std::string_view, std::string_view, std::vector<std::string>,
                    obe::DebugInfo)>(),
                sol::base_classes, sol::bases<obe::Exception>());
    }
};