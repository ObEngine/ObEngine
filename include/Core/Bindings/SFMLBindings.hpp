#pragma once

namespace kaguya { class State; }

/**
* \brief Bindings to SFML related classes and functions
*/
namespace obe::Bindings::SFMLBindings
{
    void LoadSfColor(kaguya::State* lua);
    void LoadSfDrawable(kaguya::State* lua);
    void LoadSfFont(kaguya::State* lua);
    void LoadSfGlsl(kaguya::State* lua);
    void LoadSfRect(kaguya::State* lua);
    void LoadSfShape(kaguya::State* lua);
    void LoadSfSprite(kaguya::State* lua);
    void LoadSfTcpSocket(kaguya::State* lua);
    void LoadSfText(kaguya::State* lua);
    void LoadSfTexture(kaguya::State* lua);
    void LoadSfTime(kaguya::State* lua);
    void LoadSfTransformable(kaguya::State* lua);
    void LoadSfVector(kaguya::State* lua);
}