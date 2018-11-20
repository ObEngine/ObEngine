#pragma once

namespace kaguya { class State; }

/**
* \brief Bindings to Graphics related classes and functions
*/
namespace obe::Bindings::GraphicsBindings
{
    void LoadLevelSpriteHandlePoint(kaguya::State* lua);
    void LoadLevelSprite(kaguya::State* lua);
    void LoadResourceManager(kaguya::State* lua);
    void LoadCanvas(kaguya::State* lua);
    void LoadGraphicsUtils(kaguya::State* lua);
    void LoadShader(kaguya::State* lua);
    void LoadColor(kaguya::State* lua);
}