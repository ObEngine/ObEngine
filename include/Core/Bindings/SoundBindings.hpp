#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Sound related classes and functions
        */
        namespace SoundBindings
        {
            void LoadMusic(kaguya::State* lua);
            void LoadSound(kaguya::State* lua);
        }
    }
}