#include <Bindings/obe/Collision/Exceptions/Exceptions.hpp>

#include <Collision/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::collision::Exceptions::Bindings
{
    void LoadClassInvalidTagFormat(sol::state_view state)
    {
        sol::table ExceptionsNamespace = state["obe"]["collision"]["exceptions"].get<sol::table>();
        sol::usertype<obe::collision::Exceptions::InvalidTagFormat> bindInvalidTagFormat
            = ExceptionsNamespace.new_usertype<obe::collision::Exceptions::InvalidTagFormat>(
                "InvalidTagFormat", sol::call_constructor,
                sol::constructors<obe::collision::Exceptions::InvalidTagFormat(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::collision::Exceptions::InvalidTagFormat>,
                    obe::BaseException>());
    }
};