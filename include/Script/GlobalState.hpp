#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Script
    {
        extern kaguya::State ScriptEngine;
        void InitScriptEngine();
        unsigned int createNewEnvironment();
        void executeFile(unsigned int envIndex, const std::string& file);

        void executeString(unsigned int envIndex, const std::string& string);
    }
}
