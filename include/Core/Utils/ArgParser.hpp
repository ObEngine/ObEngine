#pragma once

#include <string>
#include <vector>

#include <vili/node.hpp>

#include <Exception.hpp>

namespace obe::utils::argparser
{
    namespace exceptions
    {
        class InvalidArgumentFormat : public Exception<InvalidArgumentFormat>
        {
        public:
            using Exception::Exception;
            InvalidArgumentFormat(const std::string& argument, DebugInfo info)
                : Exception(info)
            {
                this->error("Invalid argument format '{}', expects all arguments to be '--argument-name argument-value'",
                    argument);
            }
        };
    }

    vili::node parse_args(const std::vector<std::string>& argv);
}