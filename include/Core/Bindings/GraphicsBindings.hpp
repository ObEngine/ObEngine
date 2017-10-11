#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        /**
        * \brief Bindings to Graphics related classes and functions
        */
        namespace GraphicsBindings
        {
            void LoadLevelSpriteHandlePoint(kaguya::State* lua);
            void LoadLevelSprite(kaguya::State* lua);
            void LoadResourceManager(kaguya::State* lua);
            void LoadCanvas(kaguya::State* lua);
            void LoadGraphicsUtils(kaguya::State* lua);
        }
    }
}