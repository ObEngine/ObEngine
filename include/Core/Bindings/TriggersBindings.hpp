#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Triggers related classes and functions
        */
        namespace TriggersBindings
        {
            void LoadTrigger(kaguya::State* lua);
            void LoadTriggerDatabase(kaguya::State* lua);
            void LoadTriggerDelay(kaguya::State* lua);
            void LoadTriggerGroup(kaguya::State* lua);
        }
    }
}