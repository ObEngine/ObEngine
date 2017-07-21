#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace TriggersBindings
        {
            void LoadTrigger(kaguya::State& lua);
            void LoadTriggerDatabase(kaguya::State& lua);
            void LoadTriggerDelay(kaguya::State& lua);
            void LoadTriggerGroup(kaguya::State& lua);
        }
    }
}