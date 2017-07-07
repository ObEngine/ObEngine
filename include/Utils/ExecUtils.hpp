#pragma once

#include <string>

namespace obe
{
    namespace Utils
    {
        namespace Exec
        {
            class RunArgsParser
            {
            private:
                char** start;
                int size;
            public:
                RunArgsParser(char** start, int size);
                bool argumentExists(const std::string& arg) const;
                std::string getArgumentValue(const std::string& arg) const;
            };
        }
    }
}