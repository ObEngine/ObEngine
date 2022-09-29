#pragma once

#include <vili/exceptions.hpp>

namespace vili::msgpack::exceptions
{
    template <class exception_type>
    class validator_exception : public vili::exceptions::exception<exception_type>
    {
    public:
        validator_exception(std::string_view exception_name, std::string_view location,
            vili::exceptions::debug_info info)
            : vili::exceptions::exception<exception_type>(exception_name, info)
        {
            // this is necessary because of odd inheritance rules with template classes
            this->m_message += fmt::format("  - node: '{}'\n", location);
        }
    };
}
