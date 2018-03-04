#pragma once

#include <kaguya/kaguya.hpp>

/**
* \brief Bindings to Scene related classes and functions
*/
namespace obe::Bindings::SceneBindings
{
    void LoadCamera(kaguya::State* lua);
    void LoadScene(kaguya::State* lua);
}
