#include <Bindings/obe/collision/Exceptions/Exceptions.hpp>

#include <Collision/Exceptions.hpp>

#include <Bindings/Config.hpp>

namespace obe::collision::Exceptions::bindings
{
    void load_class_invalid_tag_format(sol::state_view state)
    {
        sol::table Exceptions_namespace = state["obe"]["collision"]["Exceptions"].get<sol::table>();
        sol::usertype<obe::collision::Exceptions::InvalidTagFormat> bind_invalid_tag_format
            = Exceptions_namespace.new_usertype<obe::collision::Exceptions::InvalidTagFormat>(
                "InvalidTagFormat", sol::call_constructor,
                sol::constructors<obe::collision::Exceptions::InvalidTagFormat(
                    std::string_view, std::string_view, std::string_view, obe::DebugInfo)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::collision::Exceptions::InvalidTagFormat>,
                    obe::BaseException>());
    }
};