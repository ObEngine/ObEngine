#pragma once

#include <kaguya/kaguya.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace GraphicsBindings
        {
            void LoadLevelSpriteHandlePoint(kaguya::State* lua);
            void LoadLevelSprite(kaguya::State* lua);
            void LoadResourceManager(kaguya::State* lua);
        }
    }
}