#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace TimeBindings
        {
            void LoadChronometer(kaguya::State& lua);
            void LoadFPSCounter(kaguya::State& lua);
            void LoadFramerateManager(kaguya::State& lua);
        }
    }
}