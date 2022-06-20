#include <algorithm>

#include <Utils/ExecUtils.hpp>

namespace obe::utils::exec
{
    RunArgsParser::RunArgsParser(int size, char** start)
    {
        this->size = size;
        this->start = start;
    }

    bool RunArgsParser::argument_exists(const std::string& arg) const
    {
        return std::find(start, start + size, arg) != (start + size);
    }

    std::string RunArgsParser::get_argument_value(const std::string& arg) const
    {
        char** itr = std::find(start, start + size, arg);
        if (itr != (start + size) && ++itr != (start + size))
        {
            return std::string(*itr);
        }
        return "";
    }
} // namespace obe::utils::exec
