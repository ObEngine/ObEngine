#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Time related classes and functions
        */
        namespace TimeBindings
        {
            void LoadChronometer(kaguya::State* lua);
            void LoadFPSCounter(kaguya::State* lua);
            void LoadFramerateManager(kaguya::State* lua);
            void LoadTimeUtils(kaguya::State* lua);
        }
    }
}