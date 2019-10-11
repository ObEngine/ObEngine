#pragma once

namespace kaguya
{
    class State;
}

/**
 * \brief Bindings to Scene related classes and functions
 */
namespace obe::Bindings::SceneBindings
{
    void LoadCamera(kaguya::State* lua);
    void LoadScene(kaguya::State* lua);
    void LoadSceneNode(kaguya::State* lua);
    void LoadTXScene(kaguya::State* lua);
} // namespace obe::Bindings::SceneBindings
