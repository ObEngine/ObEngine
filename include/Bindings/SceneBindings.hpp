#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Scene related classes and functions
        */
        namespace SceneBindings
        {
            void LoadCamera(kaguya::State* lua);
            void LoadScene(kaguya::State* lua);
        }
    }
}
