#include <Bindings/obe/Collision/Exceptions/Exceptions.hpp>

#include <Collision/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::Collision::Exceptions::Bindings
{
    void LoadClassInvalidTagFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["Collision"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::Collision::Exceptions::InvalidTagFormat> bindInvalidTagFormat
            = ExceptionsNamespace.new_usertype<obe::Collision::Exceptions::InvalidTagFormat>(
                "InvalidTagFormat", sol::call_constructor,
                sol::constructors<obe::Collision::Exceptions::InvalidTagFormat(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<InvalidTagFormat>, obe::BaseException>());
    }
};