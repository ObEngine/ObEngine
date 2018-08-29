#include <algorithm>

#include <Utils/ExecUtils.hpp>
#include "Utils/MathUtils.hpp"

namespace obe::Utils::Exec
{
    RunArgsParser::RunArgsParser(int size, char** start)
    {
        global_rand = (obe::Utils::Math::randfloat() * 10000.0);
        this->size = size;
        this->start = start;
    }

    bool RunArgsParser::argumentExists(const std::string& arg) const
    {
        return find(start, start + size, arg) != (start + size);
    }

    std::string RunArgsParser::getArgumentValue(const std::string& arg) const
    {
        char** itr = find(start, start + size, arg);
        if (itr != (start + size) && ++itr != (start + size))
        {
            return std::string(*itr);
        }
        return "";
    }
}
