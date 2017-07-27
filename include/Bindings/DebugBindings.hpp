#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Debug related classes and functions
        */
        namespace DebugBindings
        {
            void LoadConsoleMessage(kaguya::State* lua);
            void LoadConsoleStream(kaguya::State* lua);
            void LoadConsole(kaguya::State* lua);
        }
    }
}