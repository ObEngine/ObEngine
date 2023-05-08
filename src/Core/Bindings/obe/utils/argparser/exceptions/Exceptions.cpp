#include <Bindings/obe/utils/argparser/exceptions/Exceptions.hpp>

#include <Utils/ArgParser.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::argparser::exceptions::bindings
{
    void load_class_invalid_argument_format(sol::state_view state)
    {
        sol::table exceptions_namespace
            = state["obe"]["utils"]["argparser"]["exceptions"].get<sol::table>();
        sol::usertype<obe::utils::argparser::exceptions::InvalidArgumentFormat>
            bind_invalid_argument_format = exceptions_namespace.new_usertype<
                obe::utils::argparser::exceptions::InvalidArgumentFormat>("InvalidArgumentFormat",
                sol::call_constructor,
                sol::constructors<obe::utils::argparser::exceptions::InvalidArgumentFormat(
                                      const std::string&),
                    obe::utils::argparser::exceptions::InvalidArgumentFormat(
                        const std::string&, std::source_location)>(),
                sol::base_classes,
                sol::bases<obe::Exception<obe::utils::argparser::exceptions::InvalidArgumentFormat>,
                    obe::BaseException>());
    }
};