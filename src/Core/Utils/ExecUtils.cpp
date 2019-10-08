#include <algorithm>

#include "Utils/MathUtils.hpp"
#include <Utils/ExecUtils.hpp>

namespace obe::Utils::Exec
{
    RunArgsParser::RunArgsParser(int size, char** start)
    {
        this->size = size;
        this->start = start;
    }

    bool RunArgsParser::argumentExists(const std::string& arg) const
    {
        return std::find(start, start + size, arg) != (start + size);
    }

    std::string RunArgsParser::getArgumentValue(const std::string& arg) const
    {
        char** itr = std::find(start, start + size, arg);
        if (itr != (start + size) && ++itr != (start + size))
        {
            return std::string(*itr);
        }
        return "";
    }
} // namespace obe::Utils::Exec
