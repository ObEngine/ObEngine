#pragma once

#include <kaguya/kaguya.hpp>

/**
* \brief Bindings to Sound related classes and functions
*/
namespace obe::Bindings::SoundBindings
{
    void LoadMusic(kaguya::State* lua);
    void LoadSound(kaguya::State* lua);
}